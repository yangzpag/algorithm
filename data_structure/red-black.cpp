#include <iostream>

using namespace std;

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
	
//private:
	RBNodePtr NIL;
	RBNodePtr root;
	
	
	void init(){
		NIL = new RBNode(0,0,NULL,NULL,NULL,BLACK);
		NIL->left = NIL;
		NIL->right = NIL;
		NIL->parent = NIL;
		root = NIL;
	}
	
	void left_rotate(RBNodePtr x){
		if(x == NIL) return;
		RBNodePtr y = x->right;
		if(y == NIL) return;
		// 将y的左孩子给x的右孩子 
		x->right = y->left;
		if(y->left != NIL) y->left->parent = x;
		// 将x的祖先变成y的祖先，与最后一句一起发挥作用 
		y->parent = x->parent;
		if(x->parent == NIL) root = y;
		else if(x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;
		
		//将x设置为y的左孩子 
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
	RBNodePtr RBsearch(int key){
		RBNodePtr ret = NIL,rt = root;
		while(rt != NIL){
			ret = rt;
			if(key > rt->key) rt = rt->right;
			else rt = rt->left; 
		} 
		return ret;
	}
	void RBinsert(int key,int value){
		RBNodePtr x = new RBNode(key,value,NIL,NIL,NIL);
		RBNodePtr y = RBsearch(key);
		x->parent = y;
		if(y == NIL) root = x;
		else if(y->key < x->key) y->right = x;
		else y->left = x;

		while(x->parent->color == RED){
			
			if(x->parent == x->parent->parent->left){
				y = x->parent->parent->right;
				if(y->color == RED){
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
					continue; 
				}
				else if(x == x->parent->right){
					x = x->parent;
					left_rotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				right_rotate(x->parent->parent);
			}else{
				y = x->parent->parent->left;
				if(y->color == RED){
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
					continue;
				}
				else if(x == x->parent->left){
					x = x->parent;
					right_rotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				left_rotate(x->parent->parent);
			} 
		}
		root->color = BLACK;
	}
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
	
	RBNodePtr RBmin(RBNodePtr rt){
		RBNodePtr ret = NIL;
		while(rt != NIL){
			ret = rt;
			rt = rt->left;
		}
		return ret;
	}
	
	void RBdelete(int key){
		RBNodePtr z = RBsearch(key);
		if(z == NIL) return;
		RBNodePtr y = z,x,w;
		Color y_origin_color = y->color;
		if(z->left == NIL){
			x = z->right;                      // x = y->right
			RBtransplant(z,x);                 // if x is NIL,NIL's parent will point to z's parent
		}else if(z->right == NIL){
			x = z->left;
			RBtransplant(z,x);
		}else{
			y = RBmin(z->right);
			x = y->right;						
			y_origin_color = y->color;
			if(y->parent != z){
				RBtransplant(y,y->right);      // if x is NIL,NIL's parent will point to z's parent
				y->right = z->right;
				y->right->parent = y;
			}else{
				x->parent = y;                 // if x is NIL,NIL's parent will point to z's parent
			}
			
			RBtransplant(z,y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		
		//fixup 
		while(x != root && x->color == BLACK){
			if(x == x->parent->left){
				w = x->parent->right;
				if(w->color == RED){
					w->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					w = x->parent->right;
				} 
				
				if(w->left->color == BLACK && w->right->color == BLACK){
					w->color = RED;
					x = x->parent; 
					continue;
				}
				else if(w->right->color == RED){
					w->color = RED;
					w->left->color = BLACK;
					right_rotate(w);
					w = x->parent->right;
				}
				
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				right_rotate(x->parent);
				x = root;
			}else{
				w = x->parent->right;
				if(w->color == RED){
					w->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					w = x->parent->right;
				} 
					
				if(w->left->color == BLACK && w->right->color == BLACK){
					w->color = RED;
					x = x->parent; 
					continue;
				}
				else if(w->right->color == RED){
					w->color = RED;
					w->left->color = BLACK;
					right_rotate(w);
					w = x->parent->right;
				}
					
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				right_rotate(x->parent);
				x = root;	
			}
		}
		x->color =BLACK;	
	}
	void destory(RBNodePtr rt){
		if(rt != NIL){
			destory(rt->left);
			delete rt;
			destory(rt->right);
		}
	}
	void printWalk(){
		print(root);
		cout << endl;
	}
	void print(RBNodePtr rt){
		if(rt != NIL){
			print(rt->left);
			cout << rt->key << ' ';
			print(rt->right);
		}
	}
};

