#include<iostream>
using namespace std;
char re(int j,char a,char b,char c,char d);
int main()
{
	char a,b,c,d;
	char e[5];
	int i;
	a=97;
	b=66;
	c=67;
	d=68;
	for(i=0;i<=3;i++)
	{
		e[i]=re(i,a,b,c,d);
	}
	cout<<e<<endl;
}
char re(int j,char a,char b,char c,char d)
{
	switch(j)
	{
		case 0:return a;
		case 1:return b;
		case 2:return c;
		case 3:return d;
	}
}
