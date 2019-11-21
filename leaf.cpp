#include <iostream> 
using namespace std; 
class tree{
	public:
	
	  int *node;
	  
	  int getLeafCount(int);
	  int newnode(int);
};
int tree::getLeafCount(int index)  
{  
    if(this->node[index] == NULL)      
        return 0;  
    if(this->node[2*index+1] == NULL && this->node[2*index+2] == NULL)  
        return 1;          
    else
        return getLeafCount(2*index+1)+getLeafCount(2*index+2);  
}  
  
int main()  
{  
tree n;
n.node=new int[100];
for(int i=0;i<100;i++){
	n.node[i]=0;
}
n.node[0]=1;
n.node[1]=2;
n.node[2]=2;
n.node[3]=2;
n.node[4]=2;
n.node[5]=2;
n.node[6]=2;
n.node[7]=2;
n.node[8]=2;



//«Ø¥ßtree 
cout << "Leaf count of the tree is : "<<  
                n.getLeafCount(0) << endl;  
return 0;  
}  
  
// This code is contributed by SHUBHAMSINGH10 
