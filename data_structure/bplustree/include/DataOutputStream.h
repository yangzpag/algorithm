#pragma once

#include <vector>
#include <memory>
#include <stdint.h>
class DataOutputStream{
	
public:
	DataOutputStream():
		elements(nullptr),first_free(nullptr),cap(nullptr){}
	
	DataOutputStream(const DataOutputStream&);
	DataOutputStream &operator=(const DataOutputStream&);
	~DataOutputStream();

	size_t size()const { return first_free - elements;}
	size_t capacity()const {return cap - elements;}
	uint8_t *begin()const{return elements;}
	uint8_t *end()const{return first_free;}

	void push_back(const uint8_t &t);
	
	DataOutputStream &operator<<(const uint8_t &t);
	DataOutputStream &operator<<(const int &t);
	

	void check(int i,const std::string& msg)const{
		if(i >= size())
			throw std::out_of_range(msg);
	}
private:
	static std::allocator<uint8_t> alloc;
	void chk_n_alloc(){
		if(size() == capacity()) reallocate();
	}
	std::pair<uint8_t*,uint8_t*> alloc_n_copy(const uint8_t*,const uint8_t*);
	void free();
	void reallocate();
	uint8_t *elements;
	uint8_t *first_free;
	uint8_t *cap;
};
