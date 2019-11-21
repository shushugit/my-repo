#include<iostream> 
#include <fstream>
#include<string.h>
#include<float.h>
#include<math.h>
using namespace std; 
ifstream fin("floor.data");

class Pair{
	public:
	int first;//column
	int second;//row
	Pair(int f,int s){
		first=f;
		second=s;
	}
	Pair(){
	}
	
};
class pPair{
	public:
	double first;
	Pair second;
	pPair(double f,Pair s){
		first=f;
		second=s;
	}
	pPair(){
	}
};

class list{
   
public:
    int capacity, front, back;
    pPair *queue;
    list():capacity(1),front(-1),back(-1){
        queue = new pPair[capacity];
    };
    void push_back(pPair x);
    void pop_front();
    bool empty();
    pPair Front();
    void DoubleCapacity();
};

void list::push_back(pPair x){
	 if (back == capacity - 1) {    // if stack is full, double the capacity
        DoubleCapacity();
    }

    queue[++back] = x;
}
void list::pop_front(){

    for(int i=1;i<=back;i++){
    queue[i-1]=queue[i];
}
   back--;
	        
}
bool list::empty(){

    return (front  == back);
}
pPair list::Front(){
	
	return queue[front+1];
}
void list::DoubleCapacity(){
	 
	 capacity *= 2;                            
    pPair *newqueue = new pPair[capacity];        

    for (int i = 0 ; i < capacity/2; i++) {   
        newqueue[i] = queue[i];
    }
   delete [] queue;              
    queue = newqueue;             
}

class stack{
	public:
		int top;      
		int capacity;           
    	Pair *stackarray;             
		stack():top(-1),capacity(1){
		  stackarray=new Pair[capacity];
		}
    	void push(Pair x); 
    	void pop();
    	bool empty();
    	Pair gettop();
    	void DoubleCapacity();
    	
};

void stack::push(Pair x){
	if (top == capacity - 1) { 
        DoubleCapacity();
    }

    stackarray[++top] = x;             
}

void stack::pop(){
    top--;    

}

bool stack::empty(){

    return (top == -1);
}

Pair stack::gettop(){
	return stackarray[top];
}

void stack::DoubleCapacity(){

    capacity *= 2;                            
    Pair *newstackarray = new Pair[capacity];        

    for (int i = 0 ; i < capacity/2; i++) {   
        newstackarray[i] = stackarray[i];
    }
    delete [] stackarray;              
    stackarray = newstackarray;             
}

int c,r,l;//c=7,r=10
bool*visited; 
char**grid;
 
struct cell 
{ 
    int parent_i, parent_j; //cell parent 的i,j 
    // f = g + h 
    double f, g, h; 
}; 
cell **cellDetails;
  
bool isValid(int col, int row) //界定點的範圍 
{ 
    return (col >= 0) && (col < c) && 
           (row >= 0) && (row < r); 
} 
  
// been reached or not //是否已經到達終點 ，dest.first=終點i,dest.second=終點j(座標) 
bool isDestination(int row, int col, Pair dest) 
{ 
    if (row == dest.first && col == dest.second) 
        return (true); 
    else
        return (false); 
} 
   //計算估計數h用來做嘗試
//g=移動代價，等下設1，並刪除斜向，f=g+h，下一格會走f最小之點 
double calculateHValue(int row, int col, Pair dest) 
{ 
    return ((double)sqrt ((row-dest.first)*(row-dest.first) 
                          + (col-dest.second)*(col-dest.second))); 
} 

void tracePath( Pair dest) 
{ 
    int row = dest.first; //row跟col代表終點座標 
    int col = dest.second; 
  
    stack Path; 
    stack Back;
    int count=0;
  
    while (!(cellDetails[row][col].parent_i == row 
             && cellDetails[row][col].parent_j == col ))//走回去直到回到開始點，row跟col一直往開始前進 
    { 
        
        Pair make(row,col);
        Path.push(make);//push進存放path的stack,等下可直接pop出
		                                 //push是直接Push一組pair，也就是座標 
		                                 //第一個push的就是終點  
		visited[row*r+col]=true;
      	                                 
		count++;
		
        int temp_row = cellDetails[row][col].parent_i; //前進中 
        int temp_col = cellDetails[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    } 
    cout<<count*2+1<<endl;
    if(l>count*2+1){
    	Pair make(row,col);
    	Path.push (make);//push開始點
		visited[row*r+col]=true; 
    	while (!Path.empty()) 
    	{ 
        	Pair p = Path.gettop(); //p存top 
        	Path.pop(); 
        	Back.push(p);
        	cout<<p.first<<" "<<p.second<<endl; //print出p之座標，直到stack全被pop出為止 
        
    	} 
    	Back.pop(); 
    	while(!Back.empty()){
    		Pair q = Back.gettop();
    		Back.pop();
    		cout<<q.first<<" "<<q.second<<endl;
    	
	} 
}
    delete [] Path.stackarray;
    delete [] Back.stackarray;
    return; 
} 
  
void aStarSearch( Pair src, Pair dest) 
{ 
  
    bool closedList[c][r]; 
    memset(closedList, false, sizeof (closedList)); //將closelist全部存0 
  //每一個cell的相關資料，包刮f,g,h跟parent 
      int i, j; 
      cellDetails = new cell*[c];
    for(i = 0; i < c; i++){
	  cellDetails[i] = new cell[r];
}
    
  for (i=0; i<c; i++) 
    { 
        for (j=0; j<r; j++) 
        { 
            cellDetails[i][j].f = FLT_MAX; //設定i,j之f,g,h值 ，先設為很大，之後比她小就更新 
            cellDetails[i][j].g = FLT_MAX; //
            cellDetails[i][j].h = FLT_MAX; //
            cellDetails[i][j].parent_i = -1; //parents先放-1 
            cellDetails[i][j].parent_j = -1; //
        } 
    } 
  
    i = src.first, j = src.second; //初始化source 
    cellDetails[i][j].f = 0.0; //f,g,h都是double 
    cellDetails[i][j].g = 0.0; //
    cellDetails[i][j].h = 0.0; //
    cellDetails[i][j].parent_i = i; //parents設自己 
    cellDetails[i][j].parent_j = j; 
    
	list openList; 
  
    Pair p(i,j);
    pPair make(0.0,p);
    openList.push_back(make); 
  
    while (!openList.empty()) //直到list中全部做完,當list中還有就做 
    { 
	    pPair p = openList.Front(); 
        openList.pop_front(); 
  
        i = p.second.first; 
        j = p.second.second; 
        closedList[i][j] = true; 
   
        double gNew, hNew, fNew; //存鄰近八個格子的g h f值 
  
        if (isValid(i-1, j) == true) 
        { 
          
            if (isDestination(i-1, j, dest) == true) 
            { 
               
                cellDetails[i-1][j].parent_i = i; 
                cellDetails[i-1][j].parent_j = j; 
               
                tracePath ( dest); 
                delete [] openList.queue;
                return; 
            } 
         
            else if (closedList[i-1][j] == false && 
                     grid[i-1][j]==0) //不在close list上且可以走 
            { 
                gNew = cellDetails[i][j].g + 1.0; //走這個點距離會加一 
                hNew = calculateHValue (i-1, j, dest); //算這個點跟終點距離 
                fNew = gNew + hNew; 
  
                if (cellDetails[i-1][j].f == FLT_MAX || 
                        cellDetails[i-1][j].f > fNew) 
                { 
                Pair p(i-1,j);
    			pPair make(fNew,p);//p跟新f綁在一起 
    			openList.push_back(make);//加入openlist 
  
                    cellDetails[i-1][j].f = fNew; 
                    cellDetails[i-1][j].g = gNew; 
                    cellDetails[i-1][j].h = hNew; 
                    cellDetails[i-1][j].parent_i = i; 
                    cellDetails[i-1][j].parent_j = j; 
                } 
            } 
        } 
  
       
        if (isValid(i+1, j) == true) 
        { 
        
            if (isDestination(i+1, j, dest) == true) 
            { 
                
                cellDetails[i+1][j].parent_i = i; 
                cellDetails[i+1][j].parent_j = j; 
                tracePath( dest); 
                delete [] openList.queue;
                return; 
            } 
           
            else if (closedList[i+1][j] == false && 
                     grid[i+1][j] == 0) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue(i+1, j, dest); 
                fNew = gNew + hNew; 
  
               
                if (cellDetails[i+1][j].f == FLT_MAX || 
                        cellDetails[i+1][j].f > fNew) 
                {   
					Pair p(i+1,j);
   					pPair make(fNew,p);
    				openList.push_back(make); 
                  
                    cellDetails[i+1][j].f = fNew; 
                    cellDetails[i+1][j].g = gNew; 
                    cellDetails[i+1][j].h = hNew; 
                    cellDetails[i+1][j].parent_i = i; 
                    cellDetails[i+1][j].parent_j = j; 
                } 
            } 
        } 
  
      
        if (isValid (i, j+1) == true) 
        { 
            if (isDestination(i, j+1, dest) == true) 
            { 
                // Set the Parent of the destination cell 
                cellDetails[i][j+1].parent_i = i; 
                cellDetails[i][j+1].parent_j = j; 
                tracePath(dest); 
                delete [] openList.queue;
                return; 
            } 
            else if (closedList[i][j+1] == false && 
                     grid[i][j+1] == 0) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue (i, j+1, dest); 
                fNew = gNew + hNew; 
  
                if (cellDetails[i][j+1].f == FLT_MAX || 
                        cellDetails[i][j+1].f > fNew) 
                { 
                    Pair p(i,j+1);
   					pPair make(fNew,p);
    				openList.push_back(make); 
  
                    cellDetails[i][j+1].f = fNew; 
                    cellDetails[i][j+1].g = gNew; 
                    cellDetails[i][j+1].h = hNew; 
                    cellDetails[i][j+1].parent_i = i; 
                    cellDetails[i][j+1].parent_j = j; 
                } 
            } 
        } 
  
     
        if (isValid(i, j-1) == true) 
        { 
          
            if (isDestination(i, j-1, dest) == true) 
            { 
               
                cellDetails[i][j-1].parent_i = i; 
                cellDetails[i][j-1].parent_j = j; 
                tracePath( dest); 
                delete [] openList.queue;
                return; 
            } 
  
            else if (closedList[i][j-1] == false && 
                    grid[i][j-1] == 0) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue(i, j-1, dest); 
                fNew = gNew + hNew; 
  
                if (cellDetails[i][j-1].f == FLT_MAX || 
                        cellDetails[i][j-1].f > fNew) 
                { 
                    	Pair p(i,j-1);
   						pPair make(fNew,p);
    					openList.push_back(make); 
  
                    cellDetails[i][j-1].f = fNew; 
                    cellDetails[i][j-1].g = gNew; 
                    cellDetails[i][j-1].h = hNew; 
                    cellDetails[i][j-1].parent_i = i; 
                    cellDetails[i][j-1].parent_j = j; 
                } 
            } 
        }      
    } 
    return; 
} 

int main() 
{ 
     fin>>c>>r>>l;
     int i,j;
    
	visited=new bool[c*r];//bool visited[every number]每個點有一個布林值 ex:visited[7]=0就是7還沒走過的意思  
    for(int i=0;i<c*r;i++){
    	visited[i]=false;//一開始先設FALSE 
    }
     grid = new char*[c];
    for(i = 0; i < c; i++){
	   grid[i] = new char[r];
}
    for(i=0;i < c; i++){
        for(j=0;j < r; j++){
        	
        	fin>>grid[i][j];
        }    
    }
   
    for(i=0;i < c; i++){//test
        for(j=0;j < r; j++){
        	grid[i][j]-=48;
        }   
}

int startc,startr;
int destc,destr;
for(i=0;i < c; i++){//test
        for(j=0;j < r; j++){
        	if(grid[i][j]==34){
        		
        		startc=i;
        		startr=j;
        		
			}
        }   
}//c=7 r=10

    Pair src (startc,startr); 
    Pair dest (destc,destr);//宣告sourse destination 
    if(startc<c/2){//R靠上，先跑下面 
	destc=c-2;
	}
	else{
	destc=1;//R靠下，先跑上面 
	}
	if(startr<r/2){
	destr=r-2;
	}
	else{
	destr=1;
	}
     
    
	if(destc==1&&destr==r-2){//從右上開始 
		for(i=0;i<c-2;i++){//由右往左由上往下，R在左下 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc+i][destr-j]==0&&!visited[(destc+i)*r+destr-j]){
		        Pair dest(destc+i, destr-j);
         		aStarSearch( src, dest); 
    		}
		}
    }
}//c=7 r=10

	if(destc==1&&destr==1){//從左上開始 
		for(i=0;i<c-2;i++){//由左往右由上往下，R在右下 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc+i][destr+j]==0&&!visited[(destc+i)*r+destr+j]){
		 
         	Pair dest(destc+i, destr+j); 
    
        		aStarSearch(src, dest); 
    		}
		}
    }
}//c=7 r=10
	
	if(destc==c-2&&destr==1){//從左下開始 
		for(i=0;i<c-2;i++){//由左往右由下往上，R在右上 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc-i][destr+j]==0&&!visited[(destc-i)*r+destr+j]){
		 
         		Pair dest(destc-i, destr+j); 
    
        		aStarSearch( src, dest); 
    		}
		}
    }
}//c=7 r=10

	if(destc==c-2&&destr==r-2){//從右下開始 
		for(i=0;i<c-2;i++){//由右往左由下往上，R在左上 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc-i][destr-j]==0&&!visited[(destc-i)*r+destr-j]){
		 
         		Pair dest(destc-i, destr-j); 
    
        		aStarSearch( src, dest); 
    		}
		}
    }
}//c=7 r=10

    //for(i=0;i < c; i++){//test print
       // for(j=0;j < r; j++){
        //	cout<<visited[i*r+j];
       // }   
        //	cout<<endl;
//}
  
  
    return(0); 
}
