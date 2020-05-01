
#include "Field.h"
#include <memory>


std::shared_ptr<IntField> 
IntField::createFrom(DataInputStream &dis){
	int value;
	dis >> value;
	std::shared_ptr<IntField> field = std::make_shared<IntField>(value);
	return field;
}
bool IntField::operator <= (Field * other){
	IntField *o = dynamic_cast<IntField*>(other);
	return this->value <= o->value;

}
bool IntField::operator < (Field * other){
	IntField *o = dynamic_cast<IntField*>(other);
	return this->value < o->value;

}
bool IntField::operator >= (Field * other){
	IntField *o = dynamic_cast<IntField*>(other);
	return this->value >= o->value;

}
bool IntField::operator > (Field * other){
	IntField *o = dynamic_cast<IntField*>(other);
	return this->value > o->value;

}
bool IntField::operator == (Field * other){
	IntField *o = dynamic_cast<IntField*>(other);
	return this->value == o->value;

}
bool IntField::operator != (Field * other){
	IntField *o = dynamic_cast<IntField*>(other);
	return this->value != o->value;

}
std::shared_ptr<Field> 
createFromType(Type t){
	
	std::shared_ptr<Field> rt;
	switch(t){
	case INT_TYPE:
		rt = std::make_shared<IntField>();
		break;
	default:
		break;
	}

	return rt;
}

std::shared_ptr<Field>
createField(DataInputStream &dis,Type t){

	std::shared_ptr<Field> rt;
	switch(t){
		case INT_TYPE:
			rt = IntField::createFrom(dis);
			break;
		default:
			break;
	}
	return rt;
}

//INT_TYPE
int dataLen[] = {4};
