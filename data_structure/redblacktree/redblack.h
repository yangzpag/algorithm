#pragma once

#include <vector>

enum Color{
	RED,
	BLACK
};

struct RBNode{
	int key;
	int value;
	RBNode *left,*right,*parent;
	Color color;
	RBNode(int k,int v,RBNode *l,RBNode *r,RBNode *p,Color c=RED)
		:key(k),value(v),left(l),right(r),parent(p),color(c){}
};

typedef RBNode* RBNodePtr;

class RBMap{
public:
	RBMap(){
		init();
	}
	~RBMap(){
		destory(root);
		delete NIL;
	}
	int count(int key){
		
		return RBsearch(key) != NIL;
	}
	void remove(int key){
		RBdelete(key);
	}

	int& operator[](int key){
		RBNodePtr rt = RBsearch(key);
		if(rt == NIL || key != rt->key){
			rt = RBinsert(key,0);
		}
		return rt->value;
	}

	void keytovector(std::vector<int> &ret){
	
		tovector_aux(root,ret);
	
	}
	
	void tovector_aux(RBNodePtr rt,std::vector<int> &arr){
		if(rt != NIL){
			tovector_aux(rt->left,arr);
			arr.push_back(rt->key);
			tovector_aux(rt->right,arr);
		}
	
	}

	RBNodePtr NIL;
	RBNodePtr root;
	
	
	void init(){
		NIL = new RBNode(0,0,nullptr,nullptr,nullptr,BLACK);
		NIL->left = NIL;
		NIL->right = NIL;
		NIL->parent = NIL;
		root = NIL;
	}
	
	void left_rotate(RBNodePtr x){
		if(x == NIL) return;
		RBNodePtr y = x->right;
		if(y == NIL) return;
		x->right = y->left;
		if(y->left != NIL) y->left->parent = x;
		y->parent = x->parent;
		if(x->parent == NIL) root = y;
		else if(x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;
		y->left = x;
		x->parent = y;
	
	}
	void right_rotate(RBNodePtr x){
		if(x == NIL) return;
		RBNodePtr y = x->left;
		if(y == NIL) return;
		x->left = y->right;
		if(y->right != NIL) y->right->parent = x;
		y->parent = x->parent;
		if(x->parent == NIL) root = y;
		else if(x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;
		y->right = x;
		x->parent = y;

	}
	RBNodePtr RBsearch(int key);
	RBNodePtr RBinsert(int key,int value);

	//u != NIL 
	void RBtransplant(RBNodePtr u,RBNodePtr v){
		if(u == root){
			root = v;
		}else if(u == u->parent->left){
			u->parent->left = v;
		}else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}
	
	RBNodePtr RBmin(RBNodePtr rt);
	void RBdelete(int key);
	void destory(RBNodePtr rt);

};

