#include <stdio.h> 
#include <stdlib.h> 
#include<iostream>
using namespace std;
struct Node 
{ 
    int data; 
    struct Node *left, *right; 
}; 

struct Stack 
{ 
    int size; 
    int top; 
    struct Node* *array; 
}; 
  
struct Node* newNode(int data) 
{ 
    struct Node* node = new struct Node; 
    node->data = data; 
    node->left = node->right = NULL; 
    return node; 
} 
  
// A utility function to create a stack of given size 
struct Stack* createStack(int size) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack->size = size; 
    stack->top = -1; 
    stack->array = (struct Node**) malloc(stack->size * sizeof(struct Node*)); 
    return stack; 
} 
  
// BASIC OPERATIONS OF STACK 
int isFull(struct Stack* stack) 
{  return stack->top - 1 == stack->size; } 
  
int isEmpty(struct Stack* stack) 
{  return stack->top == -1; } 
  
void push(struct Stack* stack, struct Node* node) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = node; 
} 
  
struct Node* pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return NULL; 
    return stack->array[stack->top--]; 
} 
  
struct Node* peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return NULL; 
    return stack->array[stack->top]; 
} 
  
void postOrderIterative(struct Node* root) 
{  
    if (root == NULL) 
        return; 
      
    struct Stack* stack = createStack(100); 
    do
    { 
        while (root) 
        { 
            if (root->right) 
                push(stack, root->right); 
            push(stack, root);  
            root = root->left; 
        } 
     
        root = pop(stack); 
  
        if (root->right && peek(stack) == root->right) 
        { 
            pop(stack); 
            push(stack, root); 
            root = root->right; 
        } 
        else
        { 
            cout<<root->data;
            root = NULL; 
        } 
    } while (!isEmpty(stack)); 
} 

int main() 
{ 
    struct Node* root = NULL; 
    root = newNode(1); 
    root->left = newNode(2); 
   //«Ø¥ßtree 
    postOrderIterative(root); 
   
      
  
    return 0; 
} 
