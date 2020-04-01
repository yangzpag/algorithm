#pragma once
 
struct ListNode{
	int key,value;
	ListNode *left,*right,*up,*down;
	ListNode(int k,int v):key(k),value(v),
		left(nullptr),right(nullptr),up(nullptr),down(nullptr){}
};
typedef ListNode* ListNodePtr;

void deleteListNode(ListNodePtr node);
void addListNodeAfter(ListNodePtr node,ListNodePtr addnode);

class SkipList{
public:
	SkipList(){
		srand( (unsigned)time(0) );
		init();
	}
	~SkipList(){
		destory();
	}
	
private:
	ListNodePtr tophead;
	int level;
	const static int MAX_LEVEL = 64;
	const static double prob = 0.5;
	void init();
	void destory();
	void add_new_level(){
		ListNodePtr new_top_head = new ListNode(INT_MIN,INT_MIN);
		ListNodePtr tail = new ListNode(INT_MAX,INT_MAX);
		addListNodeAfter(new_top_head,tail);
		new_top_head->down = tophead;
		tophead->up = new_top_head;
		tophead = new_top_head;
		level++;
	} 
	ListNodePtr SLsearch(int key);
	void SLinsert(int key,int value);
	void SLdelete(int key);	
};
