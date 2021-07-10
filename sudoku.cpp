#include <iostream>
#include<vector>
using namespace std;

void printBoard(int ar[9][9])
{
    cout<<"HERE IS YOUR SOLVED SUDOKU BOARD"<<endl<<endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<ar[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"<________________>"<<endl<<endl;
}

bool canPut_n(int ar[9][9],int row,int col,int n)
{
    if(ar[row][col]!=0)
    return false;
    bool istrue=true;

    int x3grid = (col/3) * 3;
    int y3grid = (row/3) * 3;

    for(int i=0;i<9;i++)
    {
        //Checking x direction for n
        if(ar[row][i]==n)
        {
            istrue = false;
            break;
        }
        //Checking y direction for n
        if(ar[i][col]==n)
        {
            istrue = false;
            break;
        }
        //Checking every 3 * 3 grid element for n
        if(ar[y3grid + i/3][x3grid + i%3] == n)
        {
            istrue = false;
            break;
        }  
    }
    return istrue;
}

void findNextBlank(int ar[9][9],int row, int col, int &nextrow, int &nextcol)
{
    int nextIndex = 9 * 9 + 1;
    //traversing 2d-array like 1-d array
    for(int i = row * 9 + col + 1; i < 9 * 9 ;i++)
    {
        if(ar[i/9][i%9] == 0)
        {
            nextIndex = i;
            break;
        }
    }
    nextrow = nextIndex / 9;    //gives row 
    nextcol = nextIndex % 9;    //gives col
}

void copy2Darray(int ar[9][9],int copiedar[9][9])
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            copiedar[i][j] = ar[i][j];
        }
    }
}

std::vector<int> findAllplacables(int ar[9][9], int row, int col)
{
    //keeping all placables elements in the vector
    // its size can vary from 0 to 9 
    vector<int> placebles;
    //checking all n from 1 to 9 
    for(int n=1;n<=9;n++)
    {
        if(canPut_n(ar,row,col,n))
        {
            placebles.push_back(n);
        }
    }
    return placebles;
}

bool solve9x9Sudoku(int ar[9][9],int row,int col)
{
    
    if(row>8)
    return true;    //That's mean we have already completed the board

    if(ar[row][col]!=0)
    {   //moving to the next empty box if current is filled
        int nextrow,nextcol;
        findNextBlank(ar,row,col,nextrow,nextcol);
        return solve9x9Sudoku(ar,nextrow,nextcol);
    }
    std::vector<int>placebles=findAllplacables(ar,row,col);
    if(placebles.size()==0)
    return false;

    bool istrue = false;
    for(int i=0;i<placebles.size();i++)
    {
        int n = placebles[i];
        int copiedar[9][9];
        copy2Darray(ar,copiedar);
        copiedar[row][col] = n;
        int nextrow = row;
        int nextcol = col;
        findNextBlank(copiedar,row,col,nextrow,nextcol);
        if(solve9x9Sudoku(copiedar,nextrow,nextcol))
        {
            copy2Darray(copiedar,ar);
            istrue = true;
            break;
        }
    }
    return istrue;
}

int main(int argc, char** argv)
{
	int board[9][9] ;
    cout<<"Fill the borad and enter 0 for blank BOX"<<endl;
    cout<<"Fill row wise"<<endl;
    for(int i=0;i<9;i++)
    {   
        for(int j=0;j<9;j++)
        {
            cin>>board[i][j];
        }
    }
	cout<<endl;
	if (solve9x9Sudoku(board, 0, 0))
	printBoard(board);
    else
    cout<<"Not possible dear"<<endl;

	return 0;
}
