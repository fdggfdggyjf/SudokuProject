#include<iostream>
#include<string>
#include<time.h>
#include<cstring>
#include<stdlib.h>
#include<fstream>
#include<istream>
using namespace std;
const int NO=(3+7)%9+1;
int Sudoku[9][9]={0};   //�������� 
bool rowbool[9][9]={0}; //rowbool[i][j]=1��ʾ��i���Ѿ�������j 
bool colbool[9][9]={0}; //colbool[i][j]=1��ʾ��i���Ѿ�������j 
bool tabbool[9][9]={0}; //tabbool[i][j]=1��ʾ��i���Ź����Ѿ�������j 
int number;
int newnum=0;
int t=time(0);
fstream outfile("sudoku.txt",  ios::out);

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

void flagbool(int x,int y,int z) //��x��y��д��z��ͬ��rowbool��colbool��tabbool����Ӧ����
{
	rowbool[x][z]=1; 
	colbool[y][z]=1;
	int t=x/3*3+y/3;
	tabbool[t][z]=1;
} 

void clearflagbool(int x,int y,int z) //��x��y�������ͬ��rowbool��colbool��tabbool����Ӧ����
{
	rowbool[x][z]=0; 
	colbool[y][z]=0;
	int t=x/3*3+y/3;
	tabbool[t][z]=0;
} 

void Init() //��ʼ���������� 
{
	 Sudoku[0][0]=NO;
	 flagbool(0,0,NO);
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

bool check(int x,int y,int z) //�Ƿ���Խ���x�е�y�е�����Ϊz
{
	 
	if(rowbool[x][z]==1)  return false; //��m���Ƿ����ظ���������z 
	
   	if(colbool[y][z]==1)  return false; //��n���Ƿ����ظ���������z

	int t=x/3*3+y/3;
	if(tabbool[t][z]==1)  return false; //����С�Ź����Ƿ����ظ���������z

 	return true;
}

void fillnumbers(int a[9][9],int step)
{
	if(newnum==number) return;
	if(step == 81)   //�����һ����������н�
  	{
		printSudoku(a);
		newnum++;
	}
	else
	{
		int x=step/9,y=step%9;
 		if(a[x][y] != 0)  //�Ѿ��������֣�������һ�� 
 		{
   			fillnumbers(a,step+1);
 		}
 		else
		{
			int index[9];
			randnumber(index); //ȡ��������� 
			for(int k=0;k<9;k++)
			{
   				if(check(x,y,index[k])) //���Ե�x�С���y����index[k]
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
					cout<<"�����ʽ����" << endl;
					return 0;
				}
	}
	number=atoi(argv[2]);
	Init();
	fillnumbers(Sudoku,0);
	outfile.close();
	return 0; 
}
