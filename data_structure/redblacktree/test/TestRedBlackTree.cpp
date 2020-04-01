#include <gtest/gtest.h>
#include <redblack.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <ctime>

using namespace std;
TEST(RBMap, insert){
	RBMap m;
	set<int> s;
	int n = 10000;
	vector<int> ans;
	for(int i=0;i<n;i++){
		int r = rand();
		if(!s.count(r)){
			s.insert(r);
			m[r] = 0;
		}
	}	

	for(int n : s){
		ans.push_back(n);
	}
	vector<int> ret;
	m.keytovector(ret);
	EXPECT_EQ(ans,ret);
}
TEST(RBMap, RBsearch){
	RBMap m;
	set<int> s;
	int n = 10000;
	vector<int> ans;
	for(int i=0;i<n;i++){
		int r = rand();
		if(!s.count(r)){
			s.insert(r);
			m[r] = 0;
		}
	}

	for(int n : s){
		EXPECT_EQ(m.count(n),1);
	}
}

TEST(RBMap, RBdelete){
	RBMap m;
	set<int> s;
	int n = 5000;
	vector<int> ans;
	for(int i=0;i<n;i++){
		int r = rand();
		if(!s.count(r)){
			s.insert(r);
			m[r] = 0;
		}
	}

	for(int n : s){
		ans.push_back(n);
	}
	while(!ans.empty()){
		int s = ans.size();
		int pos = rand() %  s;
		m.remove(ans[pos]);
		ans.erase(ans.begin() + pos);
		vector<int> ret;
		m.keytovector(ret);
		EXPECT_EQ(ret,ans);
	}

}
int main(int argc, char **argv) {
	srand(time(0));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
