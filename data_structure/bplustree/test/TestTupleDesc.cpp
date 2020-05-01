#include <gtest/gtest.h>
#include <TupleDesc.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <ctime>
#include <stdint.h>
#include <memory>
using namespace std;

TEST(TupleDesc, numFields){

	std::vector<Type> typeAr = {INT_TYPE,INT_TYPE};
	std::vector<std::string> nameAr = {"",""};	
	std::shared_ptr<TupleDesc> td = std::make_shared<TupleDesc>(typeAr,nameAr);

	EXPECT_EQ(td->numFields(),2);
}
TEST(TupleDesc,getByteSize){

	TupleDesc td({INT_TYPE,INT_TYPE},{"",""});
	EXPECT_EQ(td.getByteSize(),8);
}

TEST(TupleDesc,field){

	TupleDesc td({INT_TYPE,INT_TYPE},{"field1","field2"});

	EXPECT_EQ(td[0].fieldType,INT_TYPE);
	EXPECT_EQ(td[1].fieldType,INT_TYPE);
	EXPECT_EQ(td[0].fieldName,"field1");
	EXPECT_EQ(td[1].fieldName,"field2");

}


TEST(TupleDesc,move){
	int a = 1;
	int b = std::move(a);

	EXPECT_EQ(a,b);
	EXPECT_NE(&a,&b);

	vector<int> va{1,2,3,4};
	vector<int> vb(std::move(va));
	EXPECT_EQ(va.begin(),va.end());
	EXPECT_EQ(vb.size(),4);
}
TEST(Field,create){
	std::shared_ptr<Field> f = createFromType(INT_TYPE);
	//EXPECT_EQ(f.get(),nullptr);	
	EXPECT_EQ(((IntField*)f.get())->getValue(),0);

}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
