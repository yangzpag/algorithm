#pragma once

#include "BTreePage.h"
#include "BufferPool.h"
#include "DataInputStream.h"
#include "Field.h"
#include <vector>
#include <cstring>
#include <memory>

class BTreeInternalPage : public BTreePage{
public:
	BTreeInternalPage(BTreePageId id,std::vector<uint8_t> &data,int k,std::shared_ptr<TupleDesc> td);	
	int getMaxEntries();

	virtual bool isSlotUsed(int i)override;	
	virtual int getNumEmptySlots()override;

	void insertKey(std::shared_ptr<Field> key,BTreePageId leftchild,BTreePageId rightchild);
	void deleteKeyAndRightChild(std::shared_ptr<Field> key);
	int searchKey(std::shared_ptr<Field> key);
private:
	std::vector<uint8_t> 				header;
	std::vector<std::shared_ptr<Field>>	   	keys;
	std::vector<int>	   				children;
   	int			  	 					numSlots;
   	PageCategory   						childCategory;   

	int getHeaderSize(){
		int slotsPerPage = getMaxEntries() + 1;
		int hb = (slotsPerPage + 7)/ 8;
		return hb;
	}
	void markSlotUsed(int i,bool value) ;
	std::shared_ptr<Field> readKey(DataInputStream &dis,int slotId);
	void moveKey(int from,int to);
	//int searchKey(std::shared_ptr<Field> key);
	void deleteKey(int pos,bool deleteRightChild);

};
