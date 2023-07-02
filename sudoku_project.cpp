#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
int n = 9;
int mat[9][9];
int correct[9][9];
int SRn = sqrt(n);
int randomGenerator(int num)
{
	return (int)floor((float)(rand()/double(RAND_MAX)*num+1));
}

bool unusedInBox(int rstart , int cstart , int num)
{
	for(int i = 0; i<3 ;i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(mat[rstart+i][cstart+j] == num)
			{
				return false;
			}
		}
	}
	return true;
}

void fillBox(int row , int col)
{
	int num;
	for(int i = 0; i<3 ;i++)
	{
		for(int j = 0; j<3; j++)
		{
			do{
				num = randomGenerator(n);
			}while(!unusedInBox(row,col,num));
			mat[row+i][row+j] = num;
		}
	}
}

void fillDiagonal()
{
	for(int i=0;i<n;i=i+3)
	{
		fillBox(i,i);
	}
}

bool unUsedInRow(int i, int num)
{
	for(int j = 0; j<9 ;j++)
	{
		if(mat[i][j] == num)
		return false;
	}
	return true;
}

bool unUsedInCol(int j, int num)
{
	for(int i = 0; i<9 ;i++)
	{
		if(mat[i][j] == num)
		return false;
	}
	return true;
}

bool CheckIfSafe(int i , int j ,int num)
{
	return (unUsedInRow(i,num) && unUsedInCol(j,num) && unusedInBox(i-i%3,j-j%3,num));
}
    
	bool fillRemaining(int i, int j)
	{
		if (j >= n && i < n - 1) {
			i = i + 1;
			j = 0;
		}
		if (i >= n && j >= n) {
			return true;
		}
		if (i < SRn) {
			if (j < SRn) {
				j = SRn;
			}
		}
		else if (i < n - SRn) {
			if (j == (int)(i / SRn) * SRn) {
				j = j + SRn;
			}
		}
		else {
			if (j == n - SRn) {
				i = i + 1;
				j = 0;
				if (i >= n) {
					return true;
				}
			}
		}
		for (int num = 1; num <= n; num++) {
			if (CheckIfSafe(i, j, num)) {
				mat[i][j] = num;
				if (fillRemaining(i, j + 1)) {
					return true;
				}
				mat[i][j] = 0;
			}
		}
		return false;
	}
	void removek(int k)
	{
		for(int i = 0; i<9 ;i++)
		{
			for(int j = 0; j<9 ; j++)
			{
				correct[i][j] = mat[i][j];
			}
		}
		int count = k;
		while(count!=0)
		{
			int cell = randomGenerator(81)-1;
			int i = cell/9;
			int j = cell%9;
			if(j!=0)
			{
				j--;
			}
			if(mat[i][j]!=0)
			{
				count--;
				mat[i][j]=0;
			}
		}
		
	}
void fillvalues(int k)
{
	fillDiagonal();
	fillRemaining(0,SRn);
	removek(k);
}
void printsudoku(int mat[9][9])
{
   for(int i = 0 ; i<9 ;i++)
	{
		
	    if(i==0){
	    	cout<<"\t";	
			cout<<endl<<endl;
		cout<<"\t"<<"-----------------------------------"<<endl;
		cout<<endl;
	   }
	   cout<<"\t";
		for(int j = 0 ; j < n ; j++)
		{
			if(j==0)
			{
			cout<<"|";
			cout<<" ";
			}
			cout<<mat[i][j]<<"  ";
			if((j+1)%3==0)
			{
			cout<<"|";
			cout<<" ";
			}
		}
	
		//cout<<endl;
		if((i+1)%3 == 0){
			cout<<endl<<endl;
			cout<<"\t"<<"-----------------------------------"<<endl;
		cout<<endl;
	}
		else
		cout<<endl<<endl;
		
	}
}
bool isSafe(int board[9][9],int row,int col,int num)
   {
       int count=0;
       for(int i=0;i<9;i++)
       {
           if(board[row][i]==num)
           count++;
       }
       if(count>1)
       return false;
       count=0;
       for(int i=0;i<9;i++)
       {
           if(board[i][col]==num)
           count++;
       }
       if(count>1)
       return false;
       count=0;
       int sqr=3;
       int startRow=row-(row%sqr);
       int startCol=col-(col%sqr);
       for(int i=startRow;i<startRow+sqr;i++)
       {
           for(int j=startCol;j<startCol+sqr;j++)
           {
               if(board[i][j]==num)
               count++;
           }
       }
       if(count>1)
       return false;
       return true;
   }
    bool isValidSudoku(int board[9][9]) {
        int row=0;
        int col=0;
        int num;
         for(int i=0;i<9;i++)
         {
             for(int j=0;j<9;j++)
             {
                 if(board[i][j]!=0)
                 {
                     row=i;
                     col=j;
                     num=board[row][col];
                     if(!isSafe(board,row,col,num))
                     return false;
                 }

             }
         }
         return true;
    }
    int answer[9][9];
void gameMenu(int mat[9][9],int k)
{	
   vector<int>v;
   int x = 0;
    for(int i=0 ;i<9 ;i++)
    {
    	for(int j = 0;j<9;j++)
    	answer[i][j] = mat[i][j];
	}
	printsudoku(answer);
	int count = k;
	stack<int>sr;
	stack<int>sc;
		 while(count!=0)
				   {
					int i,j,val;
				    cout<<"\n Enter row column and value or PRESS 0 TO 'SHOW' PRESS -1 TO 'UNDO' or PRESS -2 QUIT or PRESS 10 to 'REPLAY'\n\n ";
					cin>>i;
					if(i<-2 || i>10)
					{
						cout<<"\n Enter numbers between 1 and 9\n\n ";
						//continue;
					}
					if(i>0 && i<10)
					{
						cin>>j>>val;
						if(answer[i-1][j-1]!=0)
						cout<<"\n Cannot update -- it is already filled\n\n ";
						else{
							answer[i-1][j-1] = val;
						sr.push(i);
						sc.push(j);
						count--;
						v.push_back(i);
						v.push_back(j);
						v.push_back(val);
						}
					}
					else if(i==-1)
					{
						if(sr.empty() || sc.empty())
						{
							cout<<"\n Cannot undone !!"<<endl<<" ";
						}
						else
						{
						answer[sr.top()-1][sc.top()-1]=0;
						count++;
						sr.pop();
						sc.pop();
						cout<<"\n Undone success "<<endl<<endl;
						}
					}
					else if(i==-2)
					{
						cout<<"\n You QUITTED the game\n\n";
						break;
					}
					else if(i==10)
					{
						for(int z =0; z<v.size();z++)
						{
							if(z%3 == 0)
							cout<<endl;
							cout<<v[z]<<" ";
						}
						cout<<endl;
					}
					else
					printsudoku(answer);
				}
				if(count==0){
				cout<<"\n You filled all entries\n\n";
				printsudoku(answer);
		  	   }
					cout<<" Press any key to go back and check the answer\n";
}
int main()
{
	int choice;
	
	cout<<"\n********SUDOKO*********\n";
	do{
		int count = 0;
	system("cls");
	cout<<"\n  *******************SUDOKO****************************  \n";
	cout<<endl;
	cout<<"\n             ------------MENU----------\n\n";
	cout<<" 1.Instructions \n\n 2.New Game \n\n 3.Check Answer \n\n 4.Show Answer \n\n 5.Exit\n";
	cout<<"\n Enter your choice \n\n ";
	cin>>choice;
	switch(choice)
	{
		case 1 : system("cls");
		          cout<<"\n\n---------------INSTRUCTIONS-------------\n\n";
		          cout<<" 1.Each row must contain numbers from 1 - 9 exactly ONCE each\n\n";
		          cout<<" 2.Each column must contain numbers from 1 - 9 exactly ONCE each\n\n";
		          cout<<" 3.Each 3x3 box must contain numbers from 1 - 9 exactly ONCE each\n\n";
		          cout<<" 4.You need to enter the row and column number and the value that you want to add\n\n";
		          cout<<" 5.You cannot enter the update the cell which is already filled\n\n";
		          cout<<" 6.Press -2 to quit whenever you want\n";
		          cout<<"\n\n Press any key to go back to menu\n";
		          getch();
		          break;
		case 2 : system("cls");
								for(int i = 0 ; i<n ;i++)
								{
									for(int j = 0 ; j < n ; j++)
									{
										mat[i][j] = 0;
									}
								}
					         int difficulty;
								cout<<"\n\n---------SELECT DIFFICULTY LEVEL---------\n\n";
								cout<<" 1.Easy\n\n 2.Medium\n\n 3.Hard\n\n ";
								cin>>difficulty;
								int k;
								if(difficulty == 1)
								k = 25;
								else if(difficulty == 2)
								k = 35;
								else
								k = 50;
								fillvalues(k);
					         gameMenu(mat,k);
					         getch();
					         break;
					         
				case 3 : 	
							for(int i = 0; i<9;i++)
							{
								for(int j = 0; j<9 ; j++)
								{
									if(answer[i][j] != 0)
									count++;
								}
							}
							if(count==81 && isValidSudoku(answer))
							cout<<"\n ********** CONGRATULATIONS!!! .....YOU WON!!!!! ************* "<<endl<<endl;
							else
							cout<<"\n ----------WRONG ANSWER !!! ---------------------\n\n";
							cout<<"\n Press Any key to go back to menu\n";
							getch();
							break;
				case 4 :  
							printsudoku(correct);
				            cout<<"Press Any key to go back to menu\n";
				            getch();
				            break;
				case 5 :    exit(0);
				default : cout<<"Invalid"<<endl;
		}
	}while(1);
}
