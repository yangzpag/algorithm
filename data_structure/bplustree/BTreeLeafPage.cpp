#include "BTreeLeafPage.h"
#include "DataInputStream.h"
#include <vector>
#include <memory>
#include "BufferPool.h"
BTreeLeafPage::BTreeLeafPage(BTreePageId id,std::vector<uint8_t>& data,int key,std::shared_ptr<TupleDesc> td)
	:BTreePage(id,key,td){

	this->numSlots = getMaxTuples();
	DataInputStream dis(data);

	dis >> this->parent;
	dis >> this->leftSibling;
	dis >> this->rightSibling;
	
	header = std::vector<uint8_t>(getHeaderSize());
	for(int i=0;i<header.size();i++){
		dis >> header[i];
	}


	tuples = std::vector<Tuple>(numSlots,td);

	for(int i=0;i<tuples.size();i++){
		tuples[i] = readTuple(dis,i);
	}

}
int BTreeLeafPage::searchTuple(std::shared_ptr<Field> key){
	int ret = -1;
	for(int i=0;i<numSlots;i++){
		if(!isSlotUsed(i))continue;
		if(*tuples[i][keyField] == key.get()){
			ret = i;
			break;
		}
	}
	return ret;

}
void BTreeLeafPage::deleteTuple(std::shared_ptr<Field> key){
	int pos = searchTuple(key);
	if(pos == -1)
		throw "not exist this tuple";
	RecordId &rid = tuples[pos].getRecordId();
	if(rid.isUseless())
		throw "BTreeLeafPage::deleteTuple,tried to delete with useless rid";
	if(rid.pid->getPageNumber() != pid.getPageNumber())
		throw "BTreeLeafPage::deleteTuple,tried to delete tuple on invalid page";
	
	if(!isSlotUsed(rid.tupleNumber))
		throw "BTreeLeafPage::deleteTuple,tried to delete null tuple";
	
	markSlotUsed(rid.tupleNumber,false);
	tuples[pos].clear();
	rid.markUseless();
}

void BTreeLeafPage::moveRecord(int from,int to){
	if(!isSlotUsed(to) && isSlotUsed(from)) {
		markSlotUsed(to, true);
		RecordId rid(&pid, to);
		tuples[to] = tuples[from];
		tuples[to].setRecordId(rid);
		markSlotUsed(from, false);
	}
}
void BTreeLeafPage::insertTuple(Tuple &t){
	if(*t.getTupleDesc() != *td)
		throw "insertTuple : type mismatch";

	int emptySlot = -1;
	for(int i=0;i<numSlots;i++){
		if(!isSlotUsed(i)){
			emptySlot = i;
			break;
		}
	}
	if(emptySlot == -1)
		throw "inserTuple:without empty slots";

	int lessOrEqKey = -1;
	std::shared_ptr<Field> key = t[keyField];
	for(int i=0;i<numSlots;i++){
		if(!isSlotUsed(i)){
			if(*tuples[i][keyField] <= key.get())
				lessOrEqKey = i;
			else
				break;
		}
	}
	int goodSlot = -1;

	if(emptySlot < lessOrEqKey){
		for(int i=emptySlot;i<lessOrEqKey;i++){
			moveRecord(i+1,i);
		}	
		goodSlot = lessOrEqKey;
	}else{
		for(int i=emptySlot;i>lessOrEqKey;i--){
			moveRecord(i-1,i);
		}
		goodSlot = lessOrEqKey + 1;
	}
	markSlotUsed(goodSlot,true);
	RecordId rid(&pid,goodSlot);
	t.setRecordId(rid);
	tuples[goodSlot] = t;


}
    
void BTreeLeafPage::markSlotUsed(int i,bool value){

	int headerbit = i % 8;
	int headerbyte = i / 8;
	if(value){
		header[headerbyte] |= 1 << headerbit;
	}else{
		header[headerbyte] &= (0xFF ^ (1 << headerbit));
	}
}

int BTreeLeafPage::getNumTuples(){
	return numSlots - getNumEmptySlots();
}

int BTreeLeafPage::getNumEmptySlots(){
	int cnt = 0;
	for(int i=0;i<numSlots;i++){
		if(!isSlotUsed(i)){
			cnt ++;
		}
	}
	return cnt;
}


bool BTreeLeafPage::isSlotUsed(int i){

	int headerbit = i % 8;
	int headerbyte = i / 8;
	return (header[headerbyte] & (1 << headerbit)) != 0;

}
Tuple BTreeLeafPage::readTuple(DataInputStream &dis,int slotId){

	Tuple tuple(td);

	for(int i=0;i<td->numFields();i++){
		tuple[i] = createField(dis,(*td)[i].fieldType);
	}
	RecordId rid(&pid,slotId);
	tuple.setRecordId(rid);
	return tuple;	

}

int BTreeLeafPage::getMaxTuples(){
	int bitsPerTupleIncludingHeader = td->getByteSize() * 8 + 1;
	int extraBits = 3 * INDEX_SIZE * 8;
	int tuplesPerPage = (BufferPool::pageSize * 8 - extraBits) / bitsPerTupleIncludingHeader;
	return tuplesPerPage;
}

int BTreeLeafPage::getHeaderSize(){
	int tuplesPerPage = getMaxTuples();
	return (tuplesPerPage + 7)/8;
}
