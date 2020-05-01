#pragma once

#include "PageId.h"

enum PageCategory{
	ROOT_PTR,
	INTERNAL,
	LEAF,
	HEADER

};
class BTreePageId : public PageId{

public:
	BTreePageId(){
		pgNo = 0;
		pgcateg = INTERNAL;
	}
	BTreePageId(int _pgNo,PageCategory _pgcateg):pgNo(_pgNo),pgcateg(_pgcateg){}
	
	BTreePageId & operator = (const BTreePageId &o){
		this->pgNo = o.pgNo;
		this->pgcateg = o.pgcateg;
	}
	bool operator == (const BTreePageId &o)const
	{
		return this->pgNo == o.pgNo && this->pgcateg == o.pgcateg;
	}
	bool operator != (const BTreePageId &o)const{
		return !(*this == o);
	}
	virtual int getPageNumber() override{
		return pgNo;
	}
	PageCategory getpgCateg(){
		return pgcateg;
	}

private:
	int pgNo;
	PageCategory pgcateg;

};

