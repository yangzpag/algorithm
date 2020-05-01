#pragma once

#include "PageId.h"



class Page{
	
public:
	virtual PageId* getId() = 0;
	//virtual int hashCode() = 0;

};
