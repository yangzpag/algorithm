#pragma once

#include "DataInputStream.h"
#include <memory>


enum Type{
	INT_TYPE
};

class Field{

	public:
		virtual Type getType() = 0;
		virtual bool operator <= (Field *other) = 0;
		virtual bool operator <  (Field *other) = 0;
		virtual bool operator >= (Field *other) = 0;
		virtual bool operator >  (Field *other) = 0;
		virtual bool operator == (Field *other) = 0;
		virtual bool operator != (Field *other) = 0;

};


class IntField:public Field{

	public:
		virtual Type getType() override{
			return INT_TYPE;
		}
		IntField():value(0){}
		IntField(int i){value = i;}
		int getValue(){return value;}

		virtual bool operator <= (Field *other) override;
		virtual bool operator <  (Field *other) override;
		virtual bool operator >= (Field *other) override;
		virtual bool operator >  (Field *other) override;
		virtual bool operator == (Field *other) override;
		virtual bool operator != (Field *other) override;
		static std::shared_ptr<IntField> createFrom(DataInputStream &dis);

	private:
		int value;

};

std::shared_ptr<Field> createFromType(Type t);
std::shared_ptr<Field> createField(DataInputStream &dis,Type t);
