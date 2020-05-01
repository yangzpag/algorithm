#pragma once
#include "BTreePage.h"
#include "Tuple.h"
#include <vector>
#include <memory>

class BTreeLeafPage:public BTreePage{


public:
	BTreeLeafPage(BTreePageId id,std::vector<uint8_t>& data,int key,std::shared_ptr<TupleDesc> td);
	virtual int getNumEmptySlots() override;
	virtual bool isSlotUsed(int i) override;
	int getNumTuples();
	void moveRecord(int from,int to);	
	Tuple readTuple(DataInputStream &dis,int slotId);
	int getMaxTuples();

	void deleteTuple(std::shared_ptr<Field> key);
	int searchTuple(std::shared_ptr<Field> key);
	void insertTuple(Tuple &t);

	void setLeftSibling(int l){
		leftSibling = l;
	}
	void setRightSibling(int r){
		rightSibling = r;
	}
	int getLeftSibling(){
		return leftSibling;
	}
	int getRightSibling(){
		return rightSibling;
	}
	const static int INDEX_SIZE = sizeof(int);	
private:
	std::vector<uint8_t> header;
	std::vector<Tuple> tuples;
	int numSlots;
	int leftSibling;
	int rightSibling;
	int getHeaderSize();
	void markSlotUsed(int ,bool );
};
