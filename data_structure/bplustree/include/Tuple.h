#pragma once
#include "Field.h"
#include "TupleDesc.h"
#include "RecordId.h"
#include <vector>
#include <memory>

class Tuple{
	
public:
	
	Tuple(std::shared_ptr<TupleDesc> td){
		tupleDesc = td;
		fields = std::vector<std::shared_ptr<Field>>(tupleDesc->numFields());
	}
	std::shared_ptr<Field> &operator[](int i){
		return fields[i];
	}
	std::shared_ptr<TupleDesc> getTupleDesc(){
		return tupleDesc;
	}
	void setRecordId(RecordId &rid){
		this->rid = rid;
	}
	RecordId &getRecordId(){
		return this->rid;
	}
	void clear(){
		for(int i=0;i<fields.size();i++){
			fields[i] = nullptr;
		}
	}
private:
	std::vector<std::shared_ptr<Field>> fields;
	std::shared_ptr<TupleDesc> tupleDesc;
	RecordId rid;
};
