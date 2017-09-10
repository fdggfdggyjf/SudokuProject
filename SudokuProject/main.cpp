#include<iostream>
#include<string>
#include<time.h>
#include<cstring>
#include<stdlib.h>
#include<fstream>
#include<istream>
using namespace std;
const int NO=(3+7)%9+1;
int Sudoku[9][9]={0};   //数独棋盘 
bool rowbool[9][9]={0}; //rowbool[i][j]=1表示第i行已经有数字j 
bool colbool[9][9]={0}; //colbool[i][j]=1表示第i列已经有数字j 
bool tabbool[9][9]={0}; //tabbool[i][j]=1表示第i个九宫格已经有数字j 
int number;
int newnum=0;
int t=time(0);
fstream outfile("sudoku.txt",  ios::out);

void randnumber(int *a)   //随机排列1~9 
{
	int temp=0,randnum;
	for(int i=0;i<9;i++)
	{
		a[i]=i+1;
	}
	srand((unsigned)(t++));
	for(int i=0;i<9;i++)
	{
		randnum=rand()%9;
		temp=a[i];
		a[i]=a[randnum];
		a[randnum]=temp;
	}
}

void flagbool(int x,int y,int z) //第x行y列写入z，同步rowbool，colbool，tabbool做相应处理
{
	rowbool[x][z]=1; 
	colbool[y][z]=1;
	int t=x/3*3+y/3;
	tabbool[t][z]=1;
} 

void clearflagbool(int x,int y,int z) //第x行y列清除，同步rowbool，colbool，tabbool做相应处理
{
	rowbool[x][z]=0; 
	colbool[y][z]=0;
	int t=x/3*3+y/3;
	tabbool[t][z]=0;
} 

void Init() //初始化数独棋盘 
{
	 Sudoku[0][0]=NO;
	 flagbool(0,0,NO);
}

void printSudoku(int a[9][9]) //按数独棋盘形式打印 
{
	int i,j;
	if (outfile.is_open())
	{
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
			{
				outfile<<a[i][j]<<" ";
			}
			outfile<<endl;
		}
		outfile<<endl; 
	}
}

bool check(int x,int y,int z) //是否可以将第x行第y列的数设为z
{
	 
	if(rowbool[x][z]==1)  return false; //第m行是否有重复出现数字z 
	
   	if(colbool[y][z]==1)  return false; //第n列是否有重复出现数字z

	int t=x/3*3+y/3;
	if(tabbool[t][z]==1)  return false; //所在小九宫格是否有重复出现数字z

 	return true;
}

void fillnumbers(int a[9][9],int step)
{
	if(newnum==number) return;
	if(step == 81)   //是最后一步，输出可行解
  	{
		printSudoku(a);
		newnum++;
	}
	else
	{
		int x=step/9,y=step%9;
 		if(a[x][y] != 0)  //已经填啦数字，处理下一个 
 		{
   			fillnumbers(a,step+1);
 		}
 		else
		{
			int index[9];
			randnumber(index); //取随机数填入 
			for(int k=0;k<9;k++)
			{
   				if(check(x,y,index[k])) //尝试第x行、第y列填index[k]
   				{
					a[x][y]=index[k];
					flagbool(x,y,index[k]);
					
					fillnumbers(a,step+1);
					
					a[x][y]=0;
					clearflagbool(x,y,index[k]); 
   				}
  			}
 		}
	}
 	
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		cout<<"输入格式有误"<<endl;
		return 0;
	}
	else if(strcmp(argv[1],"-c") != 0)
	{
		cout<<"输入格式有误"<<endl;
		return 0;
	}
	else
	{
		for(int i = 0;i < strlen(argv[2]);i++)
				if (argv[2][i] <'0'|| argv[2][i]>'9')
				{
					cout<<"输入格式有误" << endl;
					return 0;
				}
	}
	number=atoi(argv[2]);
	Init();
	fillnumbers(Sudoku,0);
	outfile.close();
	return 0; 
}
