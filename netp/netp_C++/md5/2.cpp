#include<iostream>
#include<time.h>
using namespace std;
int main(){
	time_t a;
	a=time(NULL);
	struct tm *b;
	b=localtime(&a);
	cout<<b->tm_wday<<endl;
	cout<<b->tm_mon<<endl;
	cout<<b->tm_year<<endl;
	cout<<b->tm_hour<<endl;
	cout<<b->tm_min<<endl;
	cout<<b->tm_sec<<endl;
	while(1)
	{
		a=time(NULL);
		b=localtime(&a);
		cout<<b->tm_sec<<endl;
	}
}
