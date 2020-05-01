#pragma once

#include "Page.h"
#include "BTreePageId.h"
#include "BTreeRootPtrPage.h"
#include "TupleDesc.h"
#include <memory>
class BTreePage : public Page{


public:
	BTreePage(BTreePageId id,int key):pid(id),keyField(key){}
	BTreePage(BTreePageId id,int key,std::shared_ptr<TupleDesc> td):
		BTreePage(id,key){

		this->td = td;

	}
	virtual BTreePageId* getId() override{ return &pid;}

	virtual int getNumEmptySlots() = 0;
	virtual bool isSlotUsed(int i) = 0;

	BTreePageId getParentId(){
		if(parent == 0){
			return BTreeRootPtrPage::getRootPtrId();
		}	
		return BTreePageId(parent,INTERNAL);
	}

	void setParentId(BTreePageId id){
		if(id.getpgCateg() == ROOT_PTR){
			parent = 0;
		}else{
			parent = id.getPageNumber();
		}	

	}
	const static int INDEX_SIZE = sizeof(int);
protected:

	BTreePageId pid;
	int keyField;

	int parent;
	
	std::shared_ptr<TupleDesc> td;
	

};

