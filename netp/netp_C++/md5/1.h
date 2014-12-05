#include<iostream>
#include<time.h>
#include<string>
using namespace std;

char re(int j,char a,char b,char c,char d);
char re1(int j,char a,char b,char c,char d,char e,char f);
string main1(string *sFormatSting)	//sFormatSting返回sFormatString
{
	/*
	int t=0x1234;
	int s,h;
	s=(t & 0xFF);
	h=(t &0xFF00)/0x100;
	cout<<s<<endl;
	cout<<h<<endl;
	*/
#if 0
	double a=1355043661;
	a*=1717986919;
	a/=4294967296;
	int z;
	z=a;
	z/=2;
	cout<<z<<endl;
	int r,b,c,d;
	r=(z & 0xFF);
	b=(z & 0xFF00)/0x100;
	c=(z & 0xFF0000)/0x10000;
	d=(z & 0xFF000000)/0x1000000;
	cout<<r<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
#endif
	time_t la;
	la=time(NULL);
//	cout<<la<<endl;


	double a=la;
	a*=1717986919;
	a/=4294967296;
	int z;
	z=a;
	z/=2;
//	cout<<z<<endl;
	int r,b,c,d;
	r=(z & 0xFF);
	b=(z & 0xFF00)/0x100;
	c=(z & 0xFF0000)/0x10000;
	d=(z & 0xFF000000)/0x1000000;
	/*cout<<r<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	cout<<d<<endl;
*/
	int e[4];
	e[0]=r;
	e[1]=b;
	e[2]=c;
	e[3]=d;
//	cout<<"r="<<r<<endl;
//	cout<<"b="<<b<<endl;
//	cout<<"c="<<c<<endl;
//	cout<<"d="<<d<<endl;
	
	string S;
	char o[4];
	int i;
	for(i=0;i<4;i++)
	{
		o[i]=re(i,d,c,b,r);
	}
	S=o;
//	cout<<o<<endl;
//	cout<<S<<endl;



	int e2[4];
	e2[0]=e[0];
	e2[1]=e[1];
	e2[2]=e[2];
	e2[3]=e[3];
//	for(i=0;i<4;i++)				//输出S2以供查
//	{
//		cout<<"S2["<<i<<"]="<<e2[i]<<endl;
//	}

	int e3[4];
	e3[0]=0;
	e3[1]=0;
	e3[2]=0;
	e3[3]=0;

	int j=0,k=0;
	for(i=0;i<0x20;i++)
	{
		j=(i/0x8);
		k=3-(i%0x4);
		e3[k]*=0x2;
		if((e2[j]%2)==1)
		{
			e3[k]++;
		}
		e2[j]/=2;
	}
//	for(i=0;i<4;i++)				//输出S3以供查
//	{
//		cout<<"S3["<<i<<"]="<<e3[i]<<endl;
//	}
	int e4[6];
	e4[0]=0;
	e4[1]=0;
	e4[2]=0;
	e4[3]=0;
	e4[4]=0;
	e4[5]=0;

	int t1,t2;
								t1 = e3[3];
								t1 /= 0x4;
								e4[0]=t1;
								t1=e3[3];
								t1=t1 & 0x3;
								t1 *=0x10;
								e4[1]=t1;
								t2 = e3[2];
								t2 /= 0x10;
								t2 = t2 | t1;
								e4[1] = t2;
								t1 = e3[2];
								t1 = t1 & 0x0F;
								t1 *= 0x04;
								e4[2] = t1;
								t2 = e3[1];
								t2 /= 0x40;
								t2 = t2 | t1;
								e4[2] =t2;
								t1 = e3[1];
								t1 = t1 & 0x3F;
								e4[3] =t1;
								t2 = e3[0];
								t2 /= 0x04;
								e4[4] =t2;
								t1 = e3[0];
								t1 = t1 & 0x03;
								t1 *= 0x10;
								e4[5] =t1;

	for(i=0;i<6;i++)
	{
		e4[i]+=0x20;
		if((e4[i])>=0x40)
		{
			e4[i]++;
		}
	}
//	for(i=0;i<6;i++)				//输出S4以供查
//	{
//		cout<<"S4["<<i<<"]="<<e4[i]<<endl;
//	}

	int w0,w1,w2,w3,w4,w5;
	w0=e4[0];
	w1=e4[1];
	w2=e4[2];
	w3=e4[3];
	w4=e4[4];
	w5=e4[5];


	char yy[6];
	for(i=0;i<6;i++)
	{
		yy[i]=re1(i,w0,w1,w2,w3,w4,w5);
	}
	string kk;
	kk=yy[0];
	for(i=0;i<5;i++)
	{
		kk+=yy[i+1];
	}
/*	cout<<yy[0]<<endl;
	cout<<yy[1]<<endl;
	cout<<yy[2]<<endl;
	cout<<yy[3]<<endl;
	cout<<yy[4]<<endl;
	cout<<yy[5]<<endl;
	cout<<yy<<endl;
	cout<<kk<<endl;
*/
	*sFormatSting=kk;



	string strInput;
//	cout<<S<<endl;
	strInput=S+"15310614657"+"cqxinliradius002";
//	cout<<strInput<<endl;
	return strInput;
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
char re1(int j,char a,char b,char c,char d,char e,char f)
{
	switch(j)
	{
		case 0:return a;
		case 1:return b;
		case 2:return c;
		case 3:return d;
		case 4:return e;
		case 5:return f;
	}
}
