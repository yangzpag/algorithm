#include <vector>
#include <memory>
#include <deque>
#include "DataInputStream.h"

DataInputStream::DataInputStream():data(std::make_shared<std::deque<uint8_t>>()){}

DataInputStream::DataInputStream(std::initializer_list<uint8_t> il):
				data(std::make_shared<std::deque<uint8_t>>(il)){}

DataInputStream::DataInputStream(std::vector<uint8_t> &d):
				data(std::make_shared<std::deque<uint8_t>>(d.begin(),d.end())){}

void DataInputStream::check(size_t i,const std::string &msg) const{
	if(i >= data->size())
		throw std::out_of_range(msg);
}

void DataInputStream::pop_front(){
	check(size_t(0),"front on empty DataInputStream");
	data->pop_front();
}

uint8_t &DataInputStream::front(){
	
	check(size_t(0),"front on empty DataInputStream");
	return data->front();
}


DataInputStream & DataInputStream::operator>>(uint8_t &t){
	t = this->front();
	this->pop_front();
	return *this;
}
DataInputStream & DataInputStream::operator>>(int &t){
	uint8_t *p = (uint8_t*)&t;
	for(int i=0;i<4;i++){
		*(p+i) = this->front();
		this->pop_front();
	
	}
	return *this;
}







