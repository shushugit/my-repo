// A C++ Program to implement A* Search Algorithm 
#include<bits/stdc++.h> 
using namespace std; 
  
#define ROW 9 
#define COL 10 
  
// Creating a shortcut for int, int pair type 
typedef pair<int, int> Pair; 
  
// Creating a shortcut for pair<int, pair<int, int>> type 
typedef pair<double, pair<int, int> > pPair; //pPair:�n��Jopenlist��f��+�y��

int c,r;//c=7,r=10
bool*visited; 

  
// A structure to hold the neccesary parameters 
struct cell 
{ 
    // Row and Column index of its parent 
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
    int parent_i, parent_j; //cell parent ��i,j 
    // f = g + h 
    double f, g, h; 
}; 
  
// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not. 
bool isValid(int row, int col) //�ɩw�I���d�� 
{ 
    // Returns true if row number and column number 
    // is in range 
    return (row >= 0) && (row < ROW) && 
           (col >= 0) && (col < COL); 
} 
  
// A Utility Function to check whether the given cell is 
// blocked or not 
bool isUnBlocked(int grid[][COL], int row, int col) //����1�i�H���A�令0 
{ 
    // Returns true if the cell is not blocked else false 
    if (grid[row][col] == 1) 
        return (true); 
    else
        return (false); 
} 
  
// A Utility Function to check whether destination cell has 
// been reached or not //�O�_�w�g��F���I �Adest.first=���Ii,dest.second=���Ij(�y��) 
bool isDestination(int row, int col, Pair dest) 
{ 
    if (row == dest.first && col == dest.second) 
        return (true); 
    else
        return (false); 
} 
  
// A Utility Function to calculate the 'h' heuristics. //�p����p��h�ΨӰ�����
//g=���ʥN���A���U�]1�A�çR���צV�Af=g+h�A�U�@��|��f�̤p���I 
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
    int row = dest.first; //row��col�N����I�y�� 
    int col = dest.second; 
  
    stack<Pair> Path; 
    stack<Pair> Back;
    int count;
  
    while (!(cellDetails[row][col].parent_i == row 
             && cellDetails[row][col].parent_j == col ))//���^�h����^��}�l�I�Arow��col�@�����}�l�e�i 
    { 
        Path.push (make_pair (row, col));//push�i�s��path��stack,���U�i����pop�X
		                                 //�`�Npush�O����Push�@��pair�A�]�N�O�y�� 
		                                 //�Ĥ@��push���N�O���I 
		visited[row*r+col]=true;
      	                                 
		count++;
		
        int temp_row = cellDetails[row][col].parent_i; //�e�i�� 
        int temp_col = cellDetails[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    } 
    cout<<count*2+1<<endl;
    
    Path.push (make_pair (row, col));//push�}�l�I�A�]�N�O�}�l�I
	visited[row*r+col]=true; 
    while (!Path.empty()) 
    { 
        pair<int,int> p = Path.top(); //p�stop 
        Path.pop(); 
        Back.push(p);
        
        printf("-> (%d,%d) ",p.first,p.second); //print�Xp���y�СA����stack���Qpop�X���� 
        
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
    if (isUnBlocked(grid, src.first, src.second) == false || //�Y�_�I�β��I��0 
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
    memset(closedList, false, sizeof (closedList)); //�Ncloselist�����s0 
  
    // Declare a 2D array of structure to hold the details 
    //of that cell 
    cell cellDetails[ROW][COL];//�C�@��cell��������ơA�]��f,g,h��parent 
  
    int i, j; 
  
    for (i=0; i<ROW; i++) 
    { 
        for (j=0; j<COL; j++) 
        { 
            cellDetails[i][j].f = FLT_MAX; //�]�wi,j��f,g,h�� �A���]���ܤj�A�����o�p�N��s 
            cellDetails[i][j].g = FLT_MAX; //
            cellDetails[i][j].h = FLT_MAX; //
            cellDetails[i][j].parent_i = -1; //parents����-1 
            cellDetails[i][j].parent_j = -1; //
        } 
    } 
  
    // Initialising the parameters of the starting node 
    i = src.first, j = src.second; //��l��source 
    cellDetails[i][j].f = 0.0; //f,g,h���Odouble 
    cellDetails[i][j].g = 0.0; //
    cellDetails[i][j].h = 0.0; //
    cellDetails[i][j].parent_i = i; //parents�]�ۤv 
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
  
    while (!openList.empty()) //����list����������,��list���٦��N�� 
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
        double gNew, hNew, fNew; //�s�F��K�Ӯ�l��g h f�� 
  
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
                     isUnBlocked(grid, i-1, j) == true) //���bclose list�W�B�i�H�� 
            { 
                gNew = cellDetails[i][j].g + 1.0; //���o���I�Z���|�[�@ 
                hNew = calculateHValue (i-1, j, dest); //��o���I����I�Z�� 
                fNew = gNew + hNew; 
  
                // If it isn��t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i-1][j].f == FLT_MAX || //1.�٨S�b�}�ҦC��:
				                                         //����o�Ӯ�l�[�J�}�ҦC��
				                                        //2.�b�}�ҦC���B���o�檺f����p
														//�]�[�J�sf��o���I�y�Ъ�pair
														//��ӱ��p���|��s���I��fgh��
														//�ç�����`�I(�Y�ĤG�ر��p
														//�Ĥ@�ӧ��o���I���ä��O�@�}�l�����`�I 
                        cellDetails[i-1][j].f > fNew) 
                { 
                    openList.insert( make_pair(fNew, 
                                               make_pair(i-1, j))); //�[�Jopenlist 
  
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
  
                // If it isn��t on the open list, add it to 
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
  
                // If it isn��t on the open list, add it to 
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
  
                // If it isn��t on the open list, add it to 
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
     
     
    visited=new bool[c*r];//bool visited[every number]�C���I���@�ӥ��L�� ex:visited[7]=0�N�O7�٨S���L���N��  
    for(int i=0;i<c*r;i++){
    	visited[i]=false;//�@�}�l���]FALSE 
    }
     
    //bool*visited=new bool[c*r];//�аO���L���I�N���ΦA�]��dest 
      //   for(int i=0;i<c*r;i++){
    	//visited[i]=false;//�@�}�l���]FALSE 
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
    Pair dest = make_pair(destc,destr);//�ŧisourse destination 
    if(startc<c/2){//R�a�W�A���]�U�� 
	destc=c-2;
	}
	else{
	destc=1;//R�a�U�A���]�W�� 
	}
	if(startr<r/2){
	destr=r-2;
	}
	else{
	destr=1;
	}
    cout<<destc<<destr; 
    
	if(destc==1&&destr==r-2){//�q�k�W�}�l 
		for(i=0;i<c-2;i++){//�ѥk�����ѤW���U�AR�b���U 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc+i][destr-j]==1&&!visited[(destc+i)*r+destr-j]){
		 
         		dest = make_pair(destc+i, destr-j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10

	if(destc==1&&destr==1){//�q���W�}�l 
		for(i=0;i<c-2;i++){//�ѥ����k�ѤW���U�AR�b�k�U 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc+i][destr+j]==1&&!visited[(destc+i)*r+destr+j]){
		 
         		dest = make_pair(destc+i, destr+j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10
	
	if(destc==c-2&&destr==1){//�q���U�}�l 
		for(i=0;i<c-2;i++){//�ѥ����k�ѤU���W�AR�b�k�W 
			for(j=0;j < r-2; j++){//test
         	if(grid[destc-i][destr+j]==1&&!visited[(destc-i)*r+destr+j]){
		 
         		dest = make_pair(destc-i, destr+j); 
    
        		aStarSearch(grid, src, dest); 
    		}
		}
    }
}//c=7 r=10

	if(destc==c-2&&destr==r-2){//�q�k�U�}�l 
		for(i=0;i<c-2;i++){//�ѥk�����ѤU���W�AR�b���W 
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
