// A C++ Program to implement A* Search Algorithm 
#include<bits/stdc++.h> 
using namespace std; 
  
#define ROW 9 
#define COL 10 
  
// Creating a shortcut for int, int pair type 
typedef pair<int, int> Pair; 
  
// Creating a shortcut for pair<int, pair<int, int>> type 
typedef pair<double, pair<int, int> > pPair; //pPair:要放入openlist的f值+座標

int c,r;//c=7,r=10
bool*visited; 

  
// A structure to hold the neccesary parameters 
struct cell 
{ 
    // Row and Column index of its parent 
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
    int parent_i, parent_j; //cell parent 的i,j 
    // f = g + h 
    double f, g, h; 
}; 
  
// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not. 
bool isValid(int row, int col) //界定點的範圍 
{ 
    // Returns true if row number and column number 
    // is in range 
    return (row >= 0) && (row < ROW) && 
           (col >= 0) && (col < COL); 
} 
  
// A Utility Function to check whether the given cell is 
// blocked or not 
bool isUnBlocked(int grid[][COL], int row, int col) //控制1可以走，改成0 
{ 
    // Returns true if the cell is not blocked else false 
    if (grid[row][col] == 1) 
        return (true); 
    else
        return (false); 
} 
  
// A Utility Function to check whether destination cell has 
// been reached or not //是否已經到達終點 ，dest.first=終點i,dest.second=終點j(座標) 
bool isDestination(int row, int col, Pair dest) 
{ 
    if (row == dest.first && col == dest.second) 
        return (true); 
    else
        return (false); 
} 
  
// A Utility Function to calculate the 'h' heuristics. //計算估計數h用來做嘗試
//g=移動代價，等下設1，並刪除斜向，f=g+h，下一格會走f最小之點 
double calculateHValue(int row, int col, Pair dest) 
{ 
    // Return using the distance formula 
    return ((double)sqrt ((row-dest.first)*(row-dest.first) 
                          + (col-dest.second)*(col-dest.second))); 
} 
  
// A Utility Function to trace the path from the source //
// to destination 

void tracePath(cell cellDetails[][COL], Pair dest) 
{ 
    printf ("\nThe Path is "); 
    int row = dest.first; //row跟col代表終點座標 
    int col = dest.second; 
  
    stack<Pair> Path; 
    stack<Pair> Back;
    int count;
  
    while (!(cellDetails[row][col].parent_i == row 
             && cellDetails[row][col].parent_j == col ))//走回去直到回到開始點，row跟col一直往開始前進 
    { 
        Path.push (make_pair (row, col));//push進存放path的stack,等下可直接pop出
		                                 //注意push是直接Push一組pair，也就是座標 
		                                 //第一個push的就是終點 
		visited[row*r+col]=true;
      	                                 
		count++;
		
        int temp_row = cellDetails[row][col].parent_i; //前進中 
        int temp_col = cellDetails[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    } 
    cout<<count*2+1<<endl;
    
    Path.push (make_pair (row, col));//push開始點，也就是開始點
	visited[row*r+col]=true; 
    while (!Path.empty()) 
    { 
        pair<int,int> p = Path.top(); //p存top 
        Path.pop(); 
        Back.push(p);
        
        printf("-> (%d,%d) ",p.first,p.second); //print出p之座標，直到stack全被pop出為止 
        
    } 
    Back.pop(); 
    while(!Back.empty()){
    	pair<int,int> q = Back.top();
    	Back.pop();
    	cout<<endl<<q.first<<" "<<q.second;
    	
	} 
	
  
    return; 
} 
  
// A Function to find the shortest path between 
// a given source cell to a destination cell according 
// to A* Search Algorithm 
void aStarSearch(int grid[][COL], Pair src, Pair dest) 
{ 
    // If the source is out of range 
    if (isValid (src.first, src.second) == false) 
    { 
        printf ("Source is invalid\n"); 
        return; 
    } 
  
    // If the destination is out of range 
    if (isValid (dest.first, dest.second) == false) 
    { 
        printf ("Destination is invalid\n"); 
        return; 
    } 
  
    // Either the source or the destination is blocked 
    if (isUnBlocked(grid, src.first, src.second) == false || //若起點或終點為0 
            isUnBlocked(grid, dest.first, dest.second) == false) 
    { 
        printf ("Source or the destination is blocked\n"); 
        return; 
    } 
  
    // If the destination cell is the same as source cell 
    if (isDestination(src.first, src.second, dest) == true) 
    { 
        printf ("We are already at the destination\n"); 
        return; 
    } 
  
    // Create a closed list and initialise it to false which means 
    // that no cell has been included yet 
    // This closed list is implemented as a boolean 2D array 
    bool closedList[ROW][COL]; 
    memset(closedList, false, sizeof (closedList)); //將closelist全部存0 
  
    // Declare a 2D array of structure to hold the details 
    //of that cell 
    cell cellDetails[ROW][COL];//每一個cell的相關資料，包刮f,g,h跟parent 
  
    int i, j; 
  
    for (i=0; i<ROW; i++) 
    { 
        for (j=0; j<COL; j++) 
        { 
            cellDetails[i][j].f = FLT_MAX; //設定i,j之f,g,h值 ，先設為很大，之後比她小就更新 
            cellDetails[i][j].g = FLT_MAX; //
            cellDetails[i][j].h = FLT_MAX; //
            cellDetails[i][j].parent_i = -1; //parents先放-1 
            cellDetails[i][j].parent_j = -1; //
        } 
    } 
  
    // Initialising the parameters of the starting node 
    i = src.first, j = src.second; //初始化source 
    cellDetails[i][j].f = 0.0; //f,g,h都是double 
    cellDetails[i][j].g = 0.0; //
    cellDetails[i][j].h = 0.0; //
    cellDetails[i][j].parent_i = i; //parents設自己 
    cellDetails[i][j].parent_j = j; 
  
    /* 
     Create an open list having information as- 
     <f, <i, j>> 
     where f = g + h, 
     and i, j are the row and column index of that cell 
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
     This open list is implenented as a set of pair of pair.*/
    set<pPair> openList; 
  
    // Put the starting cell on the open list and set its 
    // 'f' as 0 
    openList.insert(make_pair (0.0, make_pair (i, j))); 
  
    // We set this boolean value as false as initially 
    // the destination is not reached. 
    bool foundDest = false; 
  
    while (!openList.empty()) //直到list中全部做完,當list中還有就做 
    { 
        pPair p = *openList.begin(); 
  
        // Remove this vertex from the open list 
        openList.erase(openList.begin()); 
  
        // Add this vertex to the closed list 
        i = p.second.first; 
        j = p.second.second; 
        closedList[i][j] = true; 
       
       /* 
        Generating all the 8 successor of this cell 
  
            N.W   N   N.E 
              \   |   / 
               \  |  / 
            W----Cell----E 
                 / | \ 
               /   |  \ 
            S.W    S   S.E 
  
        Cell-->Popped Cell (i, j) 
        N -->  North       (i-1, j) 
        S -->  South       (i+1, j) 
        E -->  East        (i, j+1) 
        W -->  West           (i, j-1) 
        N.E--> North-East  (i-1, j+1) 
        N.W--> North-West  (i-1, j-1) 
        S.E--> South-East  (i+1, j+1) 
        S.W--> South-West  (i+1, j-1)*/
  
        // To store the 'g', 'h' and 'f' of the 8 successors 
        double gNew, hNew, fNew; //存鄰近八個格子的g h f值 
  
        //----------- 1st Successor (North) ------------ 
  
        // Only process this cell if this is a valid one 
        if (isValid(i-1, j) == true) 
        { 
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i-1, j, dest) == true) 
            { 
                // Set the Parent of the destination cell 
                cellDetails[i-1][j].parent_i = i; 
                cellDetails[i-1][j].parent_j = j; 
                printf ("The destination cell is found\n"); 
                tracePath (cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i-1][j] == false && 
                     isUnBlocked(grid, i-1, j) == true) //不在close list上且可以走 
            { 
                gNew = cellDetails[i][j].g + 1.0; //走這個點距離會加一 
                hNew = calculateHValue (i-1, j, dest); //算這個點跟終點距離 
                fNew = gNew + hNew; 
  
                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i-1][j].f == FLT_MAX || //1.還沒在開啟列表中:
				                                         //先把這個格子加入開啟列表
				                                        //2.在開啟列表中且走這格的f比較小
														//也加入新f跟這個點座標的pair
														//兩個情況都會更新個點的fgh值
														//並改指父節點(若第二種情況
														//第一個找到這個點的並不是一開始的父節點 
                        cellDetails[i-1][j].f > fNew) 
                { 
                    openList.insert( make_pair(fNew, 
                                               make_pair(i-1, j))); //加入openlist 
  
                    // Update the details of this cell 
                    cellDetails[i-1][j].f = fNew; 
                    cellDetails[i-1][j].g = gNew; 
                    cellDetails[i-1][j].h = hNew; 
                    cellDetails[i-1][j].parent_i = i; 
                    cellDetails[i-1][j].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 2nd Successor (South) ------------ 
  
        // Only process this cell if this is a valid one 
        if (isValid(i+1, j) == true) 
        { 
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i+1, j, dest) == true) 
            { 
                // Set the Parent of the destination cell 
                cellDetails[i+1][j].parent_i = i; 
                cellDetails[i+1][j].parent_j = j; 
                printf("The destination cell is found\n"); 
                tracePath(cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i+1][j] == false && 
                     isUnBlocked(grid, i+1, j) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue(i+1, j, dest); 
                fNew = gNew + hNew; 
  
                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i+1][j].f == FLT_MAX || 
                        cellDetails[i+1][j].f > fNew) 
                { 
                    openList.insert( make_pair (fNew, make_pair (i+1, j))); 
                    // Update the details of this cell 
                    cellDetails[i+1][j].f = fNew; 
                    cellDetails[i+1][j].g = gNew; 
                    cellDetails[i+1][j].h = hNew; 
                    cellDetails[i+1][j].parent_i = i; 
                    cellDetails[i+1][j].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 3rd Successor (East) ------------ 
  
        // Only process this cell if this is a valid one 
        if (isValid (i, j+1) == true) 
        { 
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i, j+1, dest) == true) 
            { 
                // Set the Parent of the destination cell 
                cellDetails[i][j+1].parent_i = i; 
                cellDetails[i][j+1].parent_j = j; 
                printf("The destination cell is found\n"); 
                tracePath(cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
  
            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i][j+1] == false && 
                     isUnBlocked (grid, i, j+1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue (i, j+1, dest); 
                fNew = gNew + hNew; 
  
                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i][j+1].f == FLT_MAX || 
                        cellDetails[i][j+1].f > fNew) 
                { 
                    openList.insert( make_pair(fNew, 
                                        make_pair (i, j+1))); 
  
                    // Update the details of this cell 
                    cellDetails[i][j+1].f = fNew; 
                    cellDetails[i][j+1].g = gNew; 
                    cellDetails[i][j+1].h = hNew; 
                    cellDetails[i][j+1].parent_i = i; 
                    cellDetails[i][j+1].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 4th Successor (West) ------------ 
  
        // Only process this cell if this is a valid one 
        if (isValid(i, j-1) == true) 
        { 
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i, j-1, dest) == true) 
            { 
                // Set the Parent of the destination cell 
                cellDetails[i][j-1].parent_i = i; 
                cellDetails[i][j-1].parent_j = j; 
                printf("The destination cell is found\n"); 
                tracePath(cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
  
            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i][j-1] == false && 
                     isUnBlocked(grid, i, j-1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue(i, j-1, dest); 
                fNew = gNew + hNew; 
  
                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i][j-1].f == FLT_MAX || 
                        cellDetails[i][j-1].f > fNew) 
                { 
                    openList.insert( make_pair (fNew, 
                                          make_pair (i, j-1))); 
  
                    // Update the details of this cell 
                    cellDetails[i][j-1].f = fNew; 
                    cellDetails[i][j-1].g = gNew; 
                    cellDetails[i][j-1].h = hNew; 
                    cellDetails[i][j-1].parent_i = i; 
                    cellDetails[i][j-1].parent_j = j; 
                } 
            } 
        }      
    } 
  
    // When the destination cell is not found and the open 
    // list is empty, then we conclude that we failed to 
    // reach the destiantion cell. This may happen when the 
    // there is no way to destination cell (due to blockages) 
    if (foundDest == false) 
        printf("Failed to find the Destination Cell\n"); 
  
    return; 
} 
  
  
// Driver program to test above function 
int main() 
{ 
    /* Description of the Grid- 
     1--> The cell is not blocked 
     0--> The cell is blocked    */
     
     cin>>c>>r;
     int i,j;
     
     
    visited=new bool[c*r];//bool visited[every number]每個點有一個布林值 ex:visited[7]=0就是7還沒走過的意思  
    for(int i=0;i<c*r;i++){
    	visited[i]=false;//一開始先設FALSE 
    }
     
    //bool*visited=new bool[c*r];//標記走過的點就不用再設為dest 
      //   for(int i=0;i<c*r;i++){
    	//visited[i]=false;//一開始先設FALSE 
    //}                                 
     
     char **matrix = new char*[c];
    for(i = 0; i < c; i++){
	   matrix[i] = new char[r];
}
    for(i=0;i < c; i++){
        for(j=0;j < r; j++){
        	
        	cin>>matrix[i][j];
        }    
    }
    for(i=0;i < c; i++){//test print
        for(j=0;j < r; j++){
        	cout<<matrix[i][j];
        }   
        	cout<<endl;
}
    for(i=0;i < c; i++){//test
        for(j=0;j < r; j++){
        	matrix[i][j]-=48;
        }   
}
//int number;
//number=matrix[0][0];
//cout<<number;
int startc,startr;
int destc,destr;
for(i=0;i < c; i++){//test
        for(j=0;j < r; j++){
        	if(matrix[i][j]==34){
        		cout<<i<<j;
        		startc=i;
        		startr=j;
        		
			}
        }   
}//c=7 r=10


     
    int grid[ROW][COL] = 
    { 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 }, 
        { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
    }; 
  
    Pair src = make_pair(startc,startr); 
    Pair dest = make_pair(destc,destr);//宣告sourse destination 
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
    cout<<destc<<destr; 
    
	if(destc==1&&destr==r-2){//從右上開始 
		for(i=0;i<c-2;i++){//由右往左由上往下，R在左下 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc+i][destr-j]==1&&!visited[(destc+i)*r+destr-j]){
		 
         		dest = make_pair(destc+i, destr-j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10

	if(destc==1&&destr==1){//從左上開始 
		for(i=0;i<c-2;i++){//由左往右由上往下，R在右下 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc+i][destr+j]==1&&!visited[(destc+i)*r+destr+j]){
		 
         		dest = make_pair(destc+i, destr+j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10
	
	if(destc==c-2&&destr==1){//從左下開始 
		for(i=0;i<c-2;i++){//由左往右由下往上，R在右上 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc-i][destr+j]==1&&!visited[(destc-i)*r+destr+j]){
		 
         		dest = make_pair(destc-i, destr+j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10

	if(destc==c-2&&destr==r-2){//從右下開始 
		for(i=0;i<c-2;i++){//由右往左由下往上，R在左上 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc-i][destr-j]==1&&!visited[(destc-i)*r+destr-j]){
		 
         		dest = make_pair(destc-i, destr-j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10

  aStarSearch(grid, src, dest); 
    for(i=0;i < c; i++){//test print
        for(j=0;j < r; j++){
        	cout<<visited[i*r+j];
        }   
        	cout<<endl;
}
  
  
    return(0); 
}
