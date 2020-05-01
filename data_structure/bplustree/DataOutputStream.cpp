#include <vector>
#include <memory>
#include "DataOutputStream.h"

std::allocator<uint8_t> DataOutputStream::alloc;
void DataOutputStream::push_back(const uint8_t &t){

	chk_n_alloc();
	alloc.construct(first_free++,t);
}

std::pair<uint8_t*,uint8_t*>
DataOutputStream::alloc_n_copy(const uint8_t *b,const uint8_t *e){
	auto data = alloc.allocate(e - b);
	return {data,std::uninitialized_copy(b,e,data)};
}

void DataOutputStream::free(){
	if(elements){
		for(auto p = first_free; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements,cap - elements);
	}
}

DataOutputStream::DataOutputStream(const DataOutputStream &ds){
	auto newdata = alloc_n_copy(ds.begin(),ds.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

DataOutputStream::~DataOutputStream(){free();}


DataOutputStream &DataOutputStream::operator=(const DataOutputStream &rhs){

	auto data = alloc_n_copy(rhs.begin(),rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void DataOutputStream::reallocate(){

	auto newcapacity = size() ? 2 * size() : 1;

	auto newdata = alloc.allocate(newcapacity);

	auto dest = newdata;
	auto elem = elements;

	for(size_t i=0;i != size();i++){
		alloc.construct(dest++,std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}





DataOutputStream &DataOutputStream::operator<<(const uint8_t &t){
	push_back(t);
	return *this;
}
DataOutputStream &DataOutputStream::operator<<(const int &t){
	uint8_t *p = (uint8_t*)&t;
	push_back(*(p));
	push_back(*(p+1));
	push_back(*(p+2));
	push_back(*(p+3));
	return *this;
}







