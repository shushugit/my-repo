#include<iostream>
#include<stdlib.h>
using namespace std;
class tree;
class node {
	friend class tree;
	public:
   int d;
   struct node *l,*r;
};
class stack {
   public:
   int v;
   node  *link;
   stack *n;
};

 node*create_node(int value) {
   node*new_node=new node;
   if(new_node!=NULL) {
      new_node->d=value;
      new_node->l=new_node->r=NULL;
      return new_node;
   } 
}
void push(node *node,stack **top) {
   stack*new_node=new stack;
   if(new_node!=NULL) {
      new_node->link=node;
      new_node->n=*top;
      new_node->v=0;
      *top=new_node;
   }
}
void pop(stack**top) {
   if(*top!=NULL) {
      stack*remove=*top;
      *top=(*top)->n;
      remove->link=NULL;
      remove->n=NULL;
      remove=NULL;
   }
}
void postorder_traversal(node *t,stack **top) {//傳入 
   
   cout<<"\n Postorder Data Using Stack :";
   push(t,top);//push進stack存 
  stack *store=NULL;//store指向NULL 
   while(t) {
      store=*top;//top指向store 
      if(!store->v) {
         if(t->r) {
            (store->v)++;
            push(t->r,top);
         }
         if(t->l) {
            (store->v)++;
            push(t->l,top);
         }
         if(store->v==0) {
            cout<<t->d;
            t=NULL;
            pop(top);
         }
      }
      else {
         cout<<t->d;
         t=NULL;
         pop(top);
      }
      if(*top!=NULL)
         t=(*top)->link;
	cout<<" ";
   }
}
int main(){
   node*root=NULL;
   stack*top=NULL;
   root = create_node(20);
   root->l = create_node(10);
   root->r = create_node(30);
   root->r->r = create_node(7);
   root->l->l = create_node(25);
   root->l->r = create_node(35);
   root->l->r->r = create_node(40);
   root->l->l->r = create_node(26);
   postorder_traversal(root,&top);//top一開始為NULL 
   return 0;
}
