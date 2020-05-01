#include "BTreeInternalPage.h"
#include "Field.h"
extern int dataLen[1];
BTreeInternalPage::BTreeInternalPage(BTreePageId id,std::vector<uint8_t> &data,int key,
		std::shared_ptr<TupleDesc> td):BTreePage(id,key,td){

	this->numSlots = getMaxEntries() + 1;

	DataInputStream dis(data);

	dis >> parent;
	uint8_t c;
	dis >> c;
	this->childCategory = (PageCategory)c;
	header = std::vector<uint8_t>(getHeaderSize());
	for(int i=0;i<header.size();i++){
		dis >> header[i];
	}
	keys = std::vector<std::shared_ptr<Field>>(numSlots);

	for(int i=1;i<keys.size();i++){
		keys[i] = readKey(dis,i);
	}

	children = std::vector<int>(numSlots);

	for(int i=0;i<children.size();i++){
		dis >> children[i];
	}

}
std::shared_ptr<Field> 
BTreeInternalPage::readKey(DataInputStream &dis,int slotId){
	uint8_t temp;
	std::shared_ptr<Field> f;
	if(!isSlotUsed(slotId)){
		for(int i=0;i<dataLen[(*td)[keyField].fieldType];i++){
			dis >> temp;
		}
	}else{
		f = createField(dis,(*td)[keyField].fieldType);
	}
	return f;
}
bool BTreeInternalPage::isSlotUsed(int i){
	int headerbit = i % 8;
	int headerbyte = i / 8;
	return (header[headerbyte] & (1 << headerbit)) != 0;
}

void BTreeInternalPage::markSlotUsed(int i,bool value){
	int headerbit = i % 8;
	int headerbyte = i/8;
	if(value){
		header[headerbyte] |= 1 << headerbit;
	}else{
		header[headerbyte] &= (0xFF ^ (1 << headerbit));
	}

}

int BTreeInternalPage::getNumEmptySlots(){
	int cnt = 0;
	for(int i=1;i<numSlots;i++){
		if(!isSlotUsed(i)){
			cnt++;
		}
	}
	return cnt;
}

int BTreeInternalPage::getMaxEntries() {
	int keySize = dataLen[(*td)[keyField].fieldType];
	int bitsPerEntryIncludingHeader = keySize * 8 + INDEX_SIZE * 8 + 1;
	int extraBits = 2 * INDEX_SIZE * 8 + 8 + 1;
	int entriesPerPage = ( BufferPool::pageSize * 8 - extraBits ) / bitsPerEntryIncludingHeader;
	return entriesPerPage;
}

void BTreeInternalPage::insertKey(std::shared_ptr<Field> key,BTreePageId leftchild,BTreePageId rightchild){
	if(key->getType() != (*td)[keyField].fieldType)
		throw "key field type mismatch,in insertKey";
	
	if(leftchild.getpgCateg() !=  rightchild.getpgCateg()){
		throw "child page category mismatch";
	}
	if(childCategory == ROOT_PTR){
		childCategory = leftchild.getpgCateg();
	}else if(childCategory != leftchild.getpgCateg()){
		throw "child page category mismatch";
	}

	if(getNumEmptySlots() == getMaxEntries()){
		children[0] = leftchild.getPageNumber();
		children[1] = rightchild.getPageNumber();
		keys[1] = key;
		markSlotUsed(0,true);
		markSlotUsed(1,true);
		return;
	}
	int emptySlot = -1;
	for(int i=1;i<numSlots;i++){
		if(!isSlotUsed(i)){
			emptySlot = i;
			break;
		}
	}

	if(emptySlot == -1)
		throw "called insertKey on page with no empty slots";
	
	int lessOrEqKey = -1;
	for(int i=0;i<numSlots;i++){
		if(!isSlotUsed(i)) continue;
		if(children[i] == leftchild.getPageNumber() || children[i] == rightchild.getPageNumber()){
			if(i > 0 && *keys[i] > key.get()){
				throw "attempt to insert invaild entry";
			}
			lessOrEqKey = i;

			if(children[i] == rightchild.getPageNumber()){
				children[i] = leftchild.getPageNumber();
			}
		}else if(lessOrEqKey != -1){
			if(*keys[i] < key.get()){
				throw "attempt to insert invaild entry";
			}
			break;
		}
	}
	if(lessOrEqKey == -1){
		throw "attempt to insert invaild entry";
	}
	
	int goodSlot = -1;
	if(emptySlot < lessOrEqKey){
		for(int i = emptySlot;i < lessOrEqKey;i++){
			moveKey(i+1,i);
		}
		goodSlot = lessOrEqKey;
	}else{
		for(int i = emptySlot;i > lessOrEqKey + 1;i--){
			moveKey(i-1,i);
		}
		goodSlot = lessOrEqKey + 1;
	}
	markSlotUsed(goodSlot,true);

	keys[goodSlot] = key;
	children[goodSlot] = rightchild.getPageNumber();
}

int BTreeInternalPage::searchKey(std::shared_ptr<Field> key){
	int ret = -1;
	for(int i = 1;i < numSlots;i++){
		if(!isSlotUsed(i))continue;
		if(*keys[i] == key.get()){
			ret = i;
			break;
		}
	
	}	
	return ret;
}
void BTreeInternalPage::deleteKey(int pos,bool deleteRightChild){
	keys[pos] = nullptr;
	if(!deleteRightChild){
		for(int i = pos - 1; i >= 0;i--){
			if(!isSlotUsed(i)) continue;
			children[i] = children[pos];
			break;

		}
	}
	markSlotUsed(pos,false);

}

void BTreeInternalPage::deleteKeyAndRightChild(std::shared_ptr<Field> key){
	int pos = searchKey(key);
//	if(pos == -1)
//		throw "not exists this key";
	deleteKey(pos,true);
}
void BTreeInternalPage::moveKey(int from,int to){
	if(!isSlotUsed(to) && isSlotUsed(from)){
		markSlotUsed(to,true);
		keys[to] = keys[from];
		children[to] = children[from];
		markSlotUsed(from,false);
	
	}

}
