#include<iostream>
#include<string>
#include<time.h>
#include<cstring>
#include<stdlib.h>
#include<fstream>
#include<istream>
using namespace std;
fstream outfile("sudoku.txt",  ios::out);
int Sudoku[9][9]={0};
int number;
int newnum=0;
int t=time(0);

void randnumber(int *a)   //�������1~9 
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

void Init() //��ʼ���������� 
{
	 Sudoku[0][0]=(3+7)%9+1;
}

void printSudoku(int a[9][9]) //������������ʽ��ӡ 
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

bool check(int a[9][9],int m,int n,int k) //�Ƿ���Խ���m�С���n�е�����Ϊk
{
	 
	for(int j=0;j<9;j++) //��m���Ƿ����ظ����� 
	{
		if(a[m][j] == k) return false;
	}
	
	for(int i=0;i<9;i++) //��n���Ƿ����ظ����� 
	{
		if(a[i][n] == k) return false;
	}
	
	int row=(m/3)*3,col=(n/3)*3; //����С�Ź����Ƿ����ظ�����
	for(int i=row;i<row+3;i++)
	{
 		for(int j=col;j<col+3;j++)
  			if(a[i][j] == k) return false;
	}
 	return true;
}

void fillnumbers(int a[9][9],int step)
{
	if(newnum==number) return;
 	int i=step/9,j=step%9;
 	if(a[i][j] != 0) //�Ѿ���ԭʼ����
 	{
  		if(step == 80)   //�����һ�����ӣ�������н�
  		{
			printSudoku(a);
			newnum++;
		}
  		else    //�������һ�����ӣ�����һ������
   			fillnumbers(a,step+1);
 	}
 	else    //û������
	{
		int index[9];
		randnumber(index);
		for(int k=0;k<9;k++)
		{
   			if(check(a,i,j,index[k])) //��i�С���j�п�����k
   			{
				a[i][j]=index[k]; //��Ϊk
				if(step == 80)
				{
					printSudoku(a);
					newnum++;
				}
				else
					fillnumbers(a,step+1);
				a[i][j]=0; //�ָ�Ϊ0���ж���һ��k
   			}
  		}
 	}
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		cout<<"�����ʽ����"<<endl;
		return 0;
	}
	else if(strcmp(argv[1],"-c") != 0)
	{
		cout<<"�����ʽ����"<<endl;
		return 0;
	}
	else
	{
		for(int i = 0;i < strlen(argv[2]);i++)
				if (argv[2][i] <'0'|| argv[2][i]>'9')
				{
					cout<<"������Ŀ����" << endl;
					return 0;
				}
	}
	number=atoi(argv[2]);
	
	Init();
	fillnumbers(Sudoku,0);
	outfile.close();
	return 0; 
}
