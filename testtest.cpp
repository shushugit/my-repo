#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("test.txt");
ofstream fout("final.txt");

class stacknum; 

class StackArray{
private:
    int top;                 // index of top element
    int capacity;            // allocated memory space of array
    int *stack;              // array representing stack
public:
	friend class stacknum;
	StackArray():top(-1),capacity(0){
	}
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int Top();//取得最上面的值 
    int getSize();
    void print();
    void set(int newtop);
    int gettop();
};

class stacknum{
	private:
    	StackArray *arr;
    	int height;
		int wide; 
    public:
    	stacknum(int h,int w):height(h),wide(w){
		arr=new StackArray[wide];
		for(int i=0;i<wide;i++){
			arr[i].stack=new int[height];
			arr[i].top=-1;
			for(int j=0;j<height;j++){
				arr[i].stack[j]=0;
			}
			
		}
	
	}
		void printcol();  
		void I1(int land);
		void I2(int land); 
		void O(int land);
		void L3(int land);
		void L4(int land);
		void L1(int land);
		void L2(int land);
		void J4(int land);
		void J3(int land);
		void J2(int land);
		void J1(int land);
		void clear();
		void push();
		int getthesize(int col);
	
		
};
int stacknum::getthesize(int col){
	return arr[col].getSize();
}

void stacknum::clear(){
	for(int j=height-1;j>=0;j--){
		    int count=0;
		for(int i=0;i<wide;i++){
			if(arr[i].stack[j]==1){
				count++;
				}	
	    	}
		if(count==wide){
	    	for(int k=0;k<wide;k++){
	    		for(int n=j;n<height;n++){
	    			arr[k].stack[n]=arr[k].stack[n+1];
				}
	    	}
	    
	    	for(int k=0;k<wide;k++){
	    			arr[k].stack[height-1]=0;
	    		}
	    	
	    	for(int k=0;k<wide;k++){
	    		     int nonzero=0;
	    			for(int n=0;n<height;n++){
					   
	    			if(arr[k].stack[n]==1){
	    		    	arr[k].set(n);
	    		    	nonzero++;
						}
					}
					if(nonzero==0){
							arr[k].set(-1);
						}
						
	    			
				}
			}
	    
	    
	}	
}
void stacknum::printcol(){
	for(int j=height-1;j>=0;j--){
		for(int i=0;i<wide;i++){
		
		cout<<arr[i].stack[j];
		}
	  cout<<endl;	
	}
}
void stacknum::I1(int land){
	
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	
}
void stacknum::I2(int land){
	int max=-1;
	for(int i=land-1;i<land+3;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+3;i++){
		arr[i].set(max);
	}

	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
	arr[land+2].Push(1);
	
} 
void stacknum::O(int land){
	int max=-1;
	for(int i=land-1;i<land+1;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+1;i++){
		arr[i].set(max);
	}
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	
}
void stacknum::L3(int land){
	if(arr[land].gettop()+2>=arr[land-1].gettop()){
			arr[land-1].set(arr[land].gettop()+2);
	}
	else{
		arr[land].set(arr[land-1].gettop()-2);
	}

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	
}
void stacknum::L4(int land){
	
	int max=-1;
	for(int i=land-1;i<land+2;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+2;i++){
		arr[i].set(max);
	}

	arr[land+1].Push(1);
	arr[land+1].Push(1);
	arr[land].Push(1);
	arr[land-1].Push(1);

}
void stacknum::L1(int land){
	
	int max=-1;
	for(int i=land-1;i<land+1;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+1;i++){
		arr[i].set(max);
	}

	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land].Push(1);

}
void stacknum::L2(int land){
	int max=-1;
	for(int i=land;i<land+2;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land;i<land+2;i++){
		arr[i].set(max);
	}
	
		if(arr[land-1].gettop()+1>=arr[land].gettop()){
			arr[land].set(arr[land-1].gettop()+1);
			arr[land+1].set(arr[land-1].gettop()+1);
	}//如果以左邊為底 
	else{
		arr[land-1].set(arr[land].gettop()-1);
	}//右邊為底 

	
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
}



void stacknum::J1(int land){
	
	int max=-1;
	for(int i=land-1;i<land+1;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+1;i++){
		arr[i].set(max);
	}

	arr[land].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land-1].Push(1);

}
void stacknum::J2(int land){
	
	int max=-1;
	for(int i=land-1;i<land+2;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}//找出新TOP 
	for(int i=land-1;i<land+2;i++){
		arr[i].set(max);
	}//設新TOP 

	arr[land+1].Push(1);
	arr[land].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);

}


void stacknum::J3(int land){
		if(arr[land-1].gettop()+2>=arr[land].gettop()){
			arr[land].set(arr[land-1].gettop()+2);
	}
	else{
		arr[land-1].set(arr[land].gettop()-2);
	}

	
	arr[land].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);
}

void stacknum::J4(int land){
	int max=-1;
	for(int i=land-1;i<land+1;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+1;i++){
		arr[i].set(max);
	}
	
		if(arr[land+1].gettop()+1>=arr[land].gettop()){
			arr[land].set(arr[land+1].gettop()+1);
			arr[land-1].set(arr[land+1].gettop()+1);
	}//如果以右邊為底 
	else{
		arr[land+1].set(arr[land].gettop()-1);
	}//右邊為底 

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
	arr[land+1].Push(1);
}



void stacknum::push(){
	arr[1].Push(9);
	arr[1].Push(4);
	arr[1].Push(8);
	arr[2].set(2);
	
}


void StackArray::set(int newtop){
	top=newtop;
}
int StackArray::gettop(){
	return top;
}
	

void StackArray::Push(int x){
      
	  stack[++top] = x;             // update top and put x into stack
}

void StackArray::Pop(){

    if (IsEmpty()) {          // if stack is empty, there is nothing to pop
        cout << "Stack is empty.\n";
        return;
    }
    top--;                    // update top
//    stack[top] = 0;         // (*1)
//    stack[top].~T();        // (*2)
}

bool StackArray::IsEmpty(){

    //    if (top == -1) {
    //        return true;
    //    }
    //    else {
    //        return false;
    //    }
    return (top == -1);
}

int StackArray::Top(){

    if (IsEmpty()) {     // check if stack is empty
        cout << "Stack is empty.\n";
        return -1;
    }
    return stack[top];   // return the top element
}
void StackArray::print(){
	for(int i=capacity-1;i>=0;i--){
		cout<<stack[i]<<endl; 
	}
	
}
int StackArray::getSize(){

    return top+1;        // return the number of elements in stack
}

int main(){
	
	int high,wide;
    fin>>high>>wide;
    stacknum n(high,wide);
    string testcase;
    int start;
     
    
    while(fin>>testcase && testcase != "End"){
    	
	fin >> start;
    
    if(testcase=="I1"){
    	n.I1(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="O"){
    	n.O(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
     if(testcase=="I2"){
    	n.I2(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
     if(testcase=="L3"){
    	n.L3(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="L4"){
    	n.L4(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="L1"){
    	n.L1(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="L2"){
    	n.L2(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J3"){
    	n.J3(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J4"){
    	n.J4(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J2"){
    	n.J2(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J1"){
    	n.J1(start);
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>=high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    
}
    n.printcol();
   
     
    cout<<endl;
    return 0;
}
