#pragma once

#include <vector>
#include <deque>
#include <memory>
#include <stdint.h>
class DataInputStream{
	
public:
	DataInputStream();	
	DataInputStream(std::initializer_list<uint8_t> il);
	DataInputStream(std::vector<uint8_t> &d);

	size_t size()const { return data->size();}
	bool empty() const { return data->empty();}
	
	void push_back(const uint8_t &t);
	void pop_front();

	uint8_t& front();	
	DataInputStream &operator>>(uint8_t &t);
	DataInputStream &operator>>(int &t);
private:
	std::shared_ptr<std::deque<uint8_t>> data;
	void check(size_t i,const std::string& msg)const;

};
