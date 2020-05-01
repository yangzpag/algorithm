#pragma once

#include "BTreePageId.h"
#include "DataInputStream.h"
#include <vector>
#include <stdint.h>
class BTreeRootPtrPage : public Page{

public:

	BTreeRootPtrPage()=default;
	BTreeRootPtrPage(BTreePageId id,std::vector<uint8_t> &data){
		pid = id;
		DataInputStream dis(data);
		dis >> root;
		uint8_t c;
		dis >> c;
		rootCategory = c;
	}
	static BTreePageId getRootPtrId(){
		return BTreePageId(0,ROOT_PTR);
	}

private:

	BTreePageId pid;
	int root;
	int rootCategory;
	int header;

};
