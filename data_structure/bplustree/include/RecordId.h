#pragma once
#include <memory>
#include "PageId.h"
struct RecordId {
	
	PageId* pid;
	int tupleNumber;

	RecordId(PageId* pid = nullptr,int tn = -1):
		pid(pid),tupleNumber(tn){}

	void markUseless(){
		pid = nullptr;
		tupleNumber = -1;
	}	

	bool isUseless(){
		return pid == nullptr && tupleNumber == -1;
	}

};
