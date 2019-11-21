#include<iostream>
#include<list>
using namespace std;

void DFS_visit(const int v,bool visited[]);
int main() {
    
	int i,j;
    int col,row;
    int **matrix;
    list<int>*L;
    

    cin >> col >> row ;
    L=new list<int>[col*row];

    matrix = new int*[col];
    for(i = 0; i < col; i++)
        matrix[i] = new int[row];

    for(i=0;i < col; i++){
        for(j=0;j < row; j++){
        	
        	cin>>matrix[i][j];
        }    
    }
    for(i=0;i < col; i++){//test
        for(j=0;j < row; j++){
        	cout<<matrix[i][j];
        	
        }
		cout<<endl;    
}

		for(int i=0;i<col;i++){//製作adjacency list 
        		for(int j=0;j<row;j++){
            		if(matrix[i][j]==0){
            			if(matrix[i+1][j]==0)
            				L[i*row+j].push_back((i+1)*row+j);//[6][9]=6*row+9=69
            			if(matrix[i-1][j]==0)
            				L[i*row+j].push_back((i-1)*row+j);//[1][1]=1*row+1  
						if(matrix[i][j+1]==0)
            				L[i*row+j].push_back(i*row+j+1);//[1][1]=1*row+1
						if(matrix[i][j-1]==0)
            				L[i*row+j].push_back(i*row+j-1);//[1][1]=1*row+1                                
            	}
			}
        }

	bool*visited=new bool[row*col];//bool visited[vertex number]每個點有一個布林值 ex:visited[7]=0就是7還沒走過的意思 
    for(int i=0;i<row*col;i++){
    	visited[i]=false;//一開始先設FALSE 
    }
		DFS_visit(3,visited);
		
		
}

 

DFS_visit(const int v,bool visited[]){
	visited[v]=true;//6 visited過了 
	 cout<<v<<"　"; 
	 
    	list<int>::iterator i;
    	for(i=L[v].begin();i!=L[v].end();++i){
    		if(!visited[*i]){
    			DFS_visit(*i,visited);
			}
		}

}

