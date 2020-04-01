#include <redblack.h>



RBNodePtr RBMap::RBsearch(int key){
	RBNodePtr ret = NIL,rt = root;
	while(rt != NIL){
		ret = rt;
		if(key > rt->key) rt = rt->right;
		else if(key == rt->key) break;
		else rt = rt->left; 
	} 
	return ret;
}
RBNodePtr RBMap::RBinsert(int key,int value){
	RBNodePtr ret = NIL;
	RBNodePtr x = new RBNode(key,value,NIL,NIL,NIL);
	ret = x;
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
	return ret;
}

RBNodePtr RBMap::RBmin(RBNodePtr rt){
	RBNodePtr ret = NIL;
	while(rt != NIL){
		ret = rt;
		rt = rt->left;
	}
	return ret;
}

void RBMap::RBdelete(int key){
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

void RBMap::destory(RBNodePtr rt){
	if(rt != NIL){
		destory(rt->left);
		delete rt;
		destory(rt->right);
	}
}

