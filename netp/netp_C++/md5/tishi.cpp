#include<iostream>
using namespace std;
int main(){
	time_t a;
	time_t b;
	struct tm *am;
	struct tm *bm;
	int s;
	int xx=1;
//	int peng=0;
//	int t=0;
	int flag=0;
	a=time(NULL);
	am=localtime(&a);
	s=am->tm_min;
	cout<<endl<<"Warning program has been operating!!!"<<endl;
	cout<<"begin at "<<am->tm_hour<<":"<<am->tm_min<<":"<<am->tm_sec<<endl;
	cout<<endl;
//	int i=0;
	while(1)
	{
		if(flag==0)
		{
			s=(s+50)%60;
			flag=1;
		}
//		cout<<s<<endl;
//		cout<<"a_sec="<<s<<endl;
//		cout<<"b_sec="<<bm->tm_sec<<endl;
//		cout<<"b="<<b<<endl;
		if(s==bm->tm_min){
			cout<<endl<<"Warning!Warning!Warning!Warning!Warning!Warning!"<<endl;
			cout<<"Now,time is "<<bm->tm_hour<<":"<<bm->tm_min<<":"<<bm->tm_sec;
			cout<<" you need some rest!!!"<<endl;
			cout<<"It's the "<<xx<<"th times"<<endl;
			xx++;
			flag=0;
//			peng=1;
		}
//		if(flag==1&&peng==0)
//		{
//			cout<<bm->tm_sec<<endl;
//		}
		b=time(NULL);
		bm=localtime(&b);
//	i++;
	}
}
