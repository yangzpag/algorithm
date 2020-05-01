#include <gtest/gtest.h>
#include <RecordId.h>
#include <BTreePageId.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <ctime>
#include <stdint.h>
using namespace std;

TEST(RecordId, create){
	
	BTreePageId pid(1,INTERNAL);
	RecordId rid(&pid,0);
	//EXPECT_EQ(td.numFields(),2);

}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
