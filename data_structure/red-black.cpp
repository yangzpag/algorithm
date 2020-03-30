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
/*				cout << x->parent->parent->key << endl;
				cout << x->parent->key << endl;
				cout << x->parent->parent->right->key << endl;
				cout << x->parent->parent->right->right->key << endl;
*/
				left_rotate(x->parent->parent);
			} 
		}
		root->color = BLACK;
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
			cout << rt->key << ' ' << rt->color << ',';
			print(rt->right);
		}
	}
};
int main(){
	
	RBMap tree;
	tree.RBinsert(1,1);
	//tree.printWalk(); 
	tree.RBinsert(2,1);
//	tree.printWalk(); 
	tree.RBinsert(3,1);
	tree.printWalk(); 
	tree.RBinsert(4,1);
	tree.printWalk(); 
	return 0;
} 
