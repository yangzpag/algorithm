#pragma once
#include "Field.h"
#include <string>
#include <vector>

struct TDItem{
	const Type fieldType;
	const std::string fieldName;	
	TDItem(Type ft,std::string fn):fieldType(ft),fieldName(fn){}

};

class TupleDesc{
	
public:

	int numFields(){ return tdItems.size();}
	int getByteSize();
	TupleDesc(std::initializer_list<Type> typeAr);
	TupleDesc(std::initializer_list<Type> typeAr,std::initializer_list<std::string> nameAr);
	TupleDesc(std::vector<Type>& typeAr,std::vector<std::string>& nameAr);

	TDItem& operator[](int i);

	bool operator == (const TupleDesc &other);
	bool operator != (const TupleDesc &other){
		return !(*this == other);
	}
private:
	std::vector<TDItem> tdItems;
};
