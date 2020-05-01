#include <gtest/gtest.h>
#include <DataInputStream.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <ctime>
#include <stdint.h>
using namespace std;

TEST(DataInputStream, input){
	
	DataInputStream dis({uint8_t(0x78),uint8_t(0x56),uint8_t(0x34),uint8_t(0x12),uint8_t(0x13)});
	EXPECT_EQ(dis.size(),5);
	int a = 0x12345678,ta;
	uint8_t b = 0x13,tb;
	dis >> ta >> tb;
	EXPECT_EQ(a,ta);
	EXPECT_EQ(b,tb);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
