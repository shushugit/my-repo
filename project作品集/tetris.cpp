#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("Tetris.data");
ofstream fout("Tetris.output");

class stacknum; 

class StackArray{

	private:
    	
		int top;                 
    	int *stack;              
	
	public:
		
		friend class stacknum;
		StackArray():top(-1){}
    	void Push(int x); 
    	void set(int newtop);
    	int getSize();
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
				arr[i].stack=new int[height+10];
				arr[i].top=-1;
				for(int j=0;j<height+10;j++){
					arr[i].stack[j]=0;
				}
			}
		}  
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
		void S1(int land);
		void S2(int land);
		void Z1(int land);
		void Z2(int land);
		void T1(int land);
		void T2(int land);
		void T3(int land);
		void T4(int land);
		
		void printcol();
		void clear();
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
	    		for(int n=j;n<height+9;n++){
	    			arr[k].stack[n]=arr[k].stack[n+1];
	    			arr[k].stack[height+9]=0;
	    			
				}
	    	}
	    	
	    	for(int k=0;k<wide;k++){
	    		     int nonzero=0;
	    			for(int n=0;n<height+9;n++){
					   
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
		
		fout<<arr[i].stack[j];
		}
	  fout<<endl;	
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
void stacknum::T1(int land){
	int max=-1;
	
	if(arr[land-1].gettop()>=arr[land+1].gettop()){
		arr[land+1].set(arr[land-1].gettop());	
	}//左比較高以左為底重設右 
	else{
		arr[land-1].set(arr[land+1].gettop());
	}
	
		if(arr[land].gettop()+1>=arr[land+1].gettop()){
		
			arr[land+1].set(arr[land].gettop()+1);
			arr[land-1].set(arr[land].gettop()+1);
	}//如果以中間為底 
	else{
		arr[land].set(arr[land+1].gettop()-1);
	}//左右邊為底 

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
}

void stacknum::T2(int land){
	
		if(arr[land].gettop()+1>=arr[land-1].gettop()){
		
			arr[land-1].set(arr[land].gettop()+1);
	}//如果以右邊為底，要重設左邊 
	else{
		arr[land].set(arr[land-1].gettop()-1);
	}//左邊為底，要重設右邊 

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
}

void stacknum::T3(int land){
	int max=-1;
	for(int i=land-1;i<land+2;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+2;i++){
		arr[i].set(max);
	}
	
	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
}

void stacknum::T4(int land){
	
		if(arr[land-1].gettop()+1>=arr[land].gettop()){
		
			arr[land].set(arr[land-1].gettop()+1);
	}//如果以左邊為底，要重設右邊 
	else{
		arr[land-1].set(arr[land].gettop()-1);
	}//右邊為底，要重設左邊 

	
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land].Push(1);
}

void stacknum::S1(int land){
	int max=-1;
	for(int i=land-1;i<land+1;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land-1;i<land+1;i++){
		arr[i].set(max);
	}
	
		if(arr[land-1].gettop()+1>=arr[land+1].gettop()){
		
			arr[land+1].set(arr[land-1].gettop()+1);
	}//如果以左邊為底 
	else{
		arr[land-1].set(arr[land+1].gettop()-1);
	}//右邊為底 

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
}

void stacknum::Z1(int land){
	int max=-1;
	for(int i=land;i<land+2;i++){
	if(max<arr[i].gettop()){
		max=arr[i].gettop();
		}	
	}
	for(int i=land;i<land+2;i++){
		arr[i].set(max);
	}
	
		if(arr[land+1].gettop()+1>=arr[land-1].gettop()){
		
			arr[land-1].set(arr[land+1].gettop()+1);
	}//如果以右邊為底重設左邊 
	else{
		arr[land+1].set(arr[land-1].gettop()-1);
	}//左邊為底重設右邊 

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
}


void stacknum::S2(int land){
	
		if(arr[land].gettop()+1>=arr[land-1].gettop()){
		
			arr[land-1].set(arr[land].gettop()+1);
	}//如果以右邊為底，要重設左邊 
	else{
		arr[land].set(arr[land-1].gettop()-1);
	}//左邊為底，要重設右邊 

	
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
}

void stacknum::Z2(int land){
	
		if(arr[land-1].gettop()+1>=arr[land].gettop()){
		
			arr[land].set(arr[land-1].gettop()+1);
	}//如果以左邊為底，要重設右邊 
	else{
		arr[land-1].set(arr[land].gettop()-1);
	}//右邊為底，要重設左邊 

	
	arr[land-1].Push(1);
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land].Push(1);
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
	}//左邊為底 

	
	arr[land-1].Push(1);
	arr[land].Push(1);
	arr[land+1].Push(1);
	arr[land+1].Push(1);
}

void StackArray::set(int newtop){
	top=newtop;
}

int StackArray::gettop(){
	return top;
}
	
void StackArray::Push(int x){
      
	  stack[++top] = x;            
}

int StackArray::getSize(){

    return top+1;        
}

int main(){
	
	int high,wide;
    fin>>high>>wide;
    stacknum n(high,wide);
    string testcase;
    int start;
     
    
    while(fin>>testcase && testcase != "End"){
    	
	fin >> start;
	
	if(testcase=="T1"){
    	n.T1(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="T2"){
    	n.T2(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="T3"){
    	n.T3(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="T4"){
    	n.T4(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
	
	if(testcase=="S1"){
    	n.S1(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="Z1"){
    	n.Z1(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="S2"){
    	n.S2(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="Z2"){
    	n.Z2(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    
    if(testcase=="I1"){
    	n.I1(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="O"){
    	n.O(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    			
    		n.printcol();
    		exit(1);
			}
		}
    }
     if(testcase=="I2"){
    	n.I2(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
     if(testcase=="L3"){
    	n.L3(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="L4"){
    	n.L4(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="L1"){
    	n.L1(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="L2"){
    	n.L2(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J3"){
    	n.J3(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J4"){
    	n.J4(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J2"){
    	n.J2(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
    		n.printcol();
    		exit(1);
			}
		}
    }
    if(testcase=="J1"){
    	n.J1(start);
    	n.clear();
    	n.clear();
    	n.clear();
    	n.clear();
    	for(int i=0;i<wide;i++){
    		if(n.getthesize(i)>high){
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
© 2020 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub
Pricing
API
Training
Blog
About
