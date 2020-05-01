#include "TupleDesc.h"
#include <string>
#include <cassert>


extern int dataLen[1];
TupleDesc::TupleDesc(std::initializer_list<Type> typeAr){
	std::initializer_list<Type>::iterator it;
	for(it = typeAr.begin();it != typeAr.end();it++){
		tdItems.push_back(TDItem(*it,""));
	}
	
}

TupleDesc::TupleDesc(std::initializer_list<Type> typeAr,
					 std::initializer_list<std::string> nameAr){
	assert(typeAr.size() == nameAr.size());
	std::initializer_list<Type>::iterator tit;
	std::initializer_list<std::string>::iterator nit;
	for(tit = typeAr.begin(),nit = nameAr.begin();tit != typeAr.end();tit++,nit++){
		tdItems.push_back(TDItem(*tit,*nit));	
	}	
}
TupleDesc::TupleDesc(std::vector<Type>& typeAr,std::vector<std::string>& nameAr){
	assert(typeAr.size() == nameAr.size());
	
	for(int i=0;i<typeAr.size();i++){
		tdItems.push_back(TDItem(typeAr[i],nameAr[i]));	
	}
}

int TupleDesc::getByteSize(){
	int ret = 0;
	for(int i=0;i<tdItems.size();i++){
		ret += dataLen[tdItems[i].fieldType];
	}
	return ret;

}


TDItem& TupleDesc::operator[](int i){
	if(i >= tdItems.size())
		throw std::out_of_range("Tupledesc out of range!");
	return tdItems[i];
}
bool TupleDesc::operator == (const TupleDesc &other){
	if(tdItems.size() != other.tdItems.size()) return false;
	for(int i=0;i<tdItems.size();i++){
		if(tdItems[i].fieldType != other.tdItems[i].fieldType) 
			return false;
	}
	return true;
}












