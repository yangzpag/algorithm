#include <climits>
#include <cstdlib>
#include <ctime>
#include <SkipList.h>


void deleteListNode(ListNodePtr node){
	ListNodePtr pre = node->left;
	ListNodePtr next = node->right;
	pre->right = next;
	if(next != nullptr) next->left = pre; 
	delete node;
} 
void addListNodeAfter(ListNodePtr node,ListNodePtr addnode){
	ListNodePtr next = node->right;
	node->right = addnode;
	addnode->left = node;
	addnode->right = next;
	if(next != nullptr) next->left = addnode;	
}


void SkipList::init(){
	tophead = new ListNode(INT_MIN,INT_MIN);
	ListNodePtr tail = new ListNode(INT_MAX,INT_MAX);
	addListNodeAfter(tophead,tail);
	level = 0;
}
void SkipList::destory(){
	while(tophead){	
		ListNodePtr p1 = tophead->right,p2,h2;	
		while(p1){	 	
			p2 = p1->right;
			delete p1;
			p1 = p2;	
		}
		h2 = tophead->down;
		delete tophead;
		tophead = h2;			
	}
}
ListNodePtr SkipList::SLsearch(int key){
	ListNodePtr p = tophead;
	int cur_level = level; 
	while(cur_level >= 0){
		if(key >= p->key) p = p->right;
		else {
			p = p->left;
			if(cur_level){
				p = p->down;
			} 
			cur_level--;
		}
	}
	return p;
}
void SkipList::SLinsert(int key,int value){
	ListNodePtr p = SLsearch(key);
	ListNodePtr newnode = new ListNode(key,value);
	ListNodePtr newnodeup = nullptr;
	addListNodeAfter(p,newnode);
	int cur_level = 0; 
	while(cur_level < MAX_LEVEL && ((double)std::rand() / RAND_MAX ) > 0.5){
		if(cur_level >= level){
			add_new_level();
		}
		cur_level ++;
		p = newnode;
		while(p->up == nullptr){
			p = p->left;
		}
		p = p->up;
		newnodeup = new ListNode(key,value);
		addListNodeAfter(p,newnodeup);
		newnodeup->down = newnode;
		newnode->up = newnodeup;
		newnode = newnodeup;
	}
}
void SkipList::SLdelete(int key){
	ListNodePtr p = SLsearch(key);
	if(p->key != key) return;
	while(p){
		ListNodePtr p2 = p;
		p = p->up;
		deleteListNode(p2);
	}
}	

