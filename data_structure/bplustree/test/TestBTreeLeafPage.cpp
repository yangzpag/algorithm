#include <gtest/gtest.h>
#include <BTreeInternalPage.h>
#include <BTreePageId.h>
#include <DataOutputStream.h>
#include <TupleDesc.h>
#include <BTreeLeafPage.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <ctime>
#include <stdint.h>
#include <algorithm>
#include <memory>
using namespace std;
int exampleValues[][2] = {
	{ 31933, 862 },
	{ 29402, 56883 },
	{ 1468, 5825 },
	{ 17876, 52278 },
	{ 6350, 36090 },
	{ 34784, 43771 },
	{ 28617, 56874 },
	{ 19209, 23253 },
	{ 56462, 24979 },
	{ 51440, 56685 },
	{ 3596, 62307 },
	{ 45569, 2719 },
	{ 22064, 43575 },
	{ 42812, 44947 },
	{ 22189, 19724 },
	{ 33549, 36554 },
	{ 9086, 53184 },
	{ 42878, 33394 },
	{ 62778, 21122 },
	{ 17197, 16388 }
};

extern int dataLen[1];
vector<uint8_t> convertToLeafPage(int ev[][2],int m,
		int npagebytes,int numFields,std::vector<Type> typeAr,int keyField){

	int nrecbytes = 0;
	for(int i=0;i<numFields;i++){
		nrecbytes += dataLen[typeAr[i]];
	}
	int pointerbytes = 3 * BTreeLeafPage::INDEX_SIZE;

	int nrecords =  (npagebytes * 8 - pointerbytes * 8) / (nrecbytes * 8 + 1);
	
	int nheaderbytes = (nrecords+7) / 8;
	int nheaderbits = nheaderbytes * 8;
	DataOutputStream dos;

	int recordcount = min(nrecords,m);
	dos << 0;    //parent pointer
	dos << 0;    //left sibling pointer
	dos << 0;    //right sibling pointer
	
	int i = 0;
	uint8_t headerbyte = 0;

	for(i=0;i<nheaderbits;i++){
		if(i < recordcount){
			headerbyte |= (1 << (i % 8));
		}
		if((i+1) % 8 == 0){
			dos << headerbyte;
			headerbyte = 0;
		}
	}
	if(i % 8){
		dos << headerbyte;
	}

	vector<vector<int>> evt(20,vector<int>(2));
	for(int j=0;j<20;j++){
		for(int k=0;k<2;k++){
			evt[j][k] = ev[j][k];
		}
	}	

	std::sort(evt.begin(),evt.end(),[](vector<int> &a,vector<int> &b){return a[0] < b[0];});
	for(int t = 0;t < recordcount;t++){
		dos << evt[t][0] << evt[t][1];
	}



	for (i=0; i<(npagebytes - (recordcount * nrecbytes + nheaderbytes + pointerbytes)); i++){
		dos << uint8_t(0);
	}
	return vector<uint8_t>(dos.begin(),dos.end());
}

vector<uint8_t> data;
BTreePageId pid(-1,INTERNAL);
std::vector<Type> typeAr = {INT_TYPE,INT_TYPE};
std::vector<std::string> nameAr = {"",""};
std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);

TEST(BTreeInternal, getId){
	BTreeLeafPage page(pid,data,0,td);
	EXPECT_EQ(pid,*page.getId());
}

TEST(BTreeInternal, getParentId){
	BTreeLeafPage page(pid,data,0,td);
	BTreePageId parent_pid(0,ROOT_PTR);
	EXPECT_EQ(parent_pid,page.getParentId());

}
TEST(BTreeInternal, getLeftSibling){

	BTreeLeafPage page(pid,data,0,td);
	EXPECT_EQ(0,page.getLeftSibling());

}

TEST(BTreeInternal, getRightSibling){

	BTreeLeafPage page(pid,data,0,td);
	EXPECT_EQ(0,page.getRightSibling());

}
TEST(BTreeInternal, getNumEmptySlots){

	BTreeLeafPage page(pid,data,0,td);
	EXPECT_EQ(482,page.getNumEmptySlots());
}

TEST(BTreeInternal, getSlot){

	BTreeLeafPage page(pid,data,0,td);

	for(int i=0;i<20;i++){
		EXPECT_EQ(page.isSlotUsed(i),true);
	}
	for(int i=20;i<502;i++){
		EXPECT_EQ(page.isSlotUsed(i),false);
	}

}
TEST(BTreeInternal, insertTuple){

	vector<uint8_t> data2(BufferPool::pageSize,0);
	BTreeLeafPage page(pid,data2,0,td);
	for(int i=0;i<20;i++){
		Tuple tup(td);
		for(int j=0;j<td->numFields();j++){
			tup[j] = std::make_shared<IntField>(exampleValues[i][j]);
		}
		page.insertTuple(tup);
	}
	
	EXPECT_EQ(482,page.getNumEmptySlots());
}

int main(int argc, char **argv) {
	data = convertToLeafPage(exampleValues,20,BufferPool::pageSize,2,std::vector<Type>{INT_TYPE,INT_TYPE},0);
	cout << data.size() << endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
