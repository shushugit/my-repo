#include <iostream> 
using namespace std; 
  
class node  
{  
public: 
    int data;  
    node* left;  
    node* right;  
};  
node* newNode(int data)  
{  
    node* Node = new node(); 
    Node->data = data;  
    Node->left = NULL;  
    Node->right = NULL;  
          
    return(Node);  
}  
  
int size(node* node)  
{  
    if (node == NULL)  
        return 0;  
    else
        return(size(node->left) + 1 + size(node->right));  
}  
int main()  
{  
    node *root = newNode(1);  
    root->left = newNode(2);  
    //«Ø¥ßtree 
      
    cout << "Size of the tree is " << size(root);  
    return 0;  
}  
