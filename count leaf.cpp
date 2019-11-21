#include <iostream> 
using namespace std; 
  
struct node  
{  
    int data;  
    struct node* left;  
    struct node* right;  
};  
  
int getLeaf(struct node* node)  
{  
    if(node == NULL)      
        return 0;  
    if(node->left == NULL && node->right == NULL)  
        return 1;//leaf          
    else
        return getLeaf(node->left)+getLeaf(node->right);  
}  

struct node* newNode(int data)//³Ð·snode 
{  struct node* node = new struct node;  
    node->data = data;  
    node->left = NULL;  
    node->right = NULL;  
    return(node);  
}  

int main()  
{  
    /*create a tree*/
    struct node *root = newNode(1);  
    root->left = newNode(2);  
    root->right = newNode(3);  
    root->left->left = newNode(4);  
    root->left->right = newNode(5);  
      
/*get leaf count of the above created tree*/
cout << "Leaf count of the tree is : "<<  
                getLeafCount(root) << endl;  
return 0;  
}  
  
// This code is contributed by SHUBHAMSINGH10 
