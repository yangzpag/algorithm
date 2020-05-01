#include <gtest/gtest.h>
#include <BTreeInternalPage.h>
#include <BTreePageId.h>
#include <DataOutputStream.h>
#include <TupleDesc.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <ctime>
#include <stdint.h>
#include <memory>
using namespace std;

int exampleValues[] = {1468,3596,6350,9086,17197,17876,19209,
	22064,22189,28617,29402,31933, 33549, 
	34784,42812,42878, 45569,51440, 56462, 
	62778,
	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};

int EXAMPLE_VALUES[][3] =  {
	{ 3, 6350, 4 },
	{ 4, 9086, 5 },
	{ 5, 17197, 7 },
	{ 7, 22064, 9 },
	{ 9, 22189, 10 },
	{ 10, 28617, 11 },
	{ 11, 31933, 13 },
	{ 13, 33549, 14 },
	{ 14, 34784, 15 },
	{ 15, 42878, 17 },
	{ 17, 45569, 19 },
	{ 19, 56462, 20 },
	{ 20, 62778, 21 },
	{ 15, 42812, 16 },
	{ 2, 3596, 3 },
	{ 6, 17876, 7 },
	{ 1, 1468, 2 },
	{ 11, 29402, 12 },
	{ 18, 51440, 19 },
	{ 7, 19209, 8 }
};

extern int dataLen[1];
vector<uint8_t> convertToInternalPage(int ev[],int m,
		int npagebytes,Type keyType,PageCategory childpc){


	int nentrybytes = dataLen[keyType] + BTreeInternalPage::INDEX_SIZE;
	int pointerbytes = 2 * BTreeInternalPage::INDEX_SIZE + 1;

	int nentries = (npagebytes * 8 - pointerbytes * 8 - 1) /  (nentrybytes * 8 + 1); 

	int nheaderbytes = nentries/8 + 1;
	int nheaderbits = nheaderbytes * 8;

	DataOutputStream dos;
	int entrycount = min(m,nentries);

	dos << 0;   //parent point
	dos << (uint8_t)(childpc);

	int i = 0;
	uint8_t headerbyte = 0;
	for(i = 0;i<nheaderbits;i++){
		if(i < entrycount + 1)
			headerbyte |= (1 << (i % 8));
		if((i+1) % 8 == 0){
			dos << headerbyte;
			headerbyte = 0;
		}
	}

	if(i % 8 > 0)
		dos << headerbyte;
	for(int e = 0;e < entrycount;e++){
		dos << ev[e];
	}
	for(int e = entrycount;e < nentries;e++){
		dos << 0;
	}
	for(int e = 0;e <= entrycount;e++){
		dos << ev[e];
	}

	for(int e=entrycount;e < nentries;e++){
		for(int j=0;j<BTreeInternalPage::INDEX_SIZE;j++){
			dos << uint8_t(0);
		}
	}	
	for (i=0; i<(npagebytes - (nentries * nentrybytes + nheaderbytes + pointerbytes)); i++){
		dos << uint8_t(0);
	}
	return vector<uint8_t>(dos.begin(),dos.end());
}

vector<uint8_t> data;
TEST(BTreeInternal, getId){

	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data,0,td);

	for(int i=0;i<20;i++){
		int ret = page.searchKey(std::make_shared<IntField>(EXAMPLE_VALUES[i][1]));
		EXPECT_NE(ret,-1);
	}
	EXPECT_EQ(pid,*page.getId());
}

TEST(BTreeInternal, getNumEmptySlots){

	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data,0,td);

	EXPECT_EQ(483,page.getNumEmptySlots());
}

TEST(BTreeInternal, getSlot){

	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data,0,td);

	for(int i=0;i<21;i++){
		EXPECT_EQ(page.isSlotUsed(i),true);
	}
	for(int i=21;i<504;i++){
		EXPECT_EQ(page.isSlotUsed(i),false);
	}

}
TEST(BTreeInternal, getParentId){

	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data,0,td);

	EXPECT_EQ(BTreePageId(0,ROOT_PTR),page.getParentId());
}
TEST(BTreeInternal, setParentId){

	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data,0,td);
	BTreePageId npid(1,INTERNAL);
	page.setParentId(npid);
	EXPECT_EQ(npid,page.getParentId());
}

TEST(BTreeInternal,insertKey){
	vector<uint8_t> data2(BufferPool::pageSize,0);
	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data2,0,td);
	for(int i=0;i<20;i++){
		BTreePageId leftchild(EXAMPLE_VALUES[i][0],LEAF);
		BTreePageId rightchild(EXAMPLE_VALUES[i][2],LEAF);
		page.insertKey(std::make_shared<IntField>(EXAMPLE_VALUES[i][1]),leftchild,rightchild);
	}

	for(int i=0;i<20;i++){
		int ret = page.searchKey(std::make_shared<IntField>(EXAMPLE_VALUES[i][1]));
		EXPECT_NE(ret,-1);
	}
	EXPECT_EQ(483,page.getNumEmptySlots());

}
TEST(BTreeInternal,deleteKey){
	
	BTreePageId pid(-1,INTERNAL);
	std::vector<Type> typeAr = {INT_TYPE};
	std::vector<std::string> nameAr = {""};
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);
	BTreeInternalPage page(pid,data,0,td);
	for(int i=0;i<20;i++){
		page.deleteKeyAndRightChild(std::make_shared<IntField>(EXAMPLE_VALUES[i][1]));
		EXPECT_EQ(483+i+1,page.getNumEmptySlots());
	}
}
int main(int argc, char **argv) {
	data = convertToInternalPage(exampleValues,20,BufferPool::pageSize,INT_TYPE,LEAF);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
