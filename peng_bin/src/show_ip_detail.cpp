#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <bitset>
#include <arpa/inet.h>
#include <string>
using namespace std;

int test_print()
{
     int i;
     for (i = 1; i <= 32; i++) 
     {
	  if((i - 1) % 8 == 0 && i != 1)
	       cout<<"    ";
	  printf("%3d",i);
     }
     printf("\n");
     return 0;
}
int fun(const string IP)
{
     test_print();
     struct in_addr in;
     unsigned int t;
     inet_aton(IP.c_str(),&in);
     string s(inet_ntoa(in));
     // cout<<s<<endl;

     memcpy(&t,&in,sizeof(struct in_addr));
     t = ntohl(t);
     // printf("%#x\n",t);
     bitset<32> a(t);
     // cout<<a<<endl;

     for (int i = 31; i >= 0; --i) 
     {
	  printf("%3d",(int)a[i]);
	  if((i) % 8 == 0 && i != 31)
	       cout<<"    ";
     }
     cout<<endl;


     bitset<8> a1(t>>24);
     bitset<8> a2(t>>16);
     bitset<8> a3(t>>8);
     bitset<8> a4(t);
     // cout<<a1<<","<<a2<<","<<a3<<","<<a4<<endl;
     cout<<a1<<"\t"<<a2<<"\t"<<a3<<"\t"<<a4<<endl;
     // cout<<a1.to_ulong()<<"\t"<<a2.to_ulong()<<"\t"<<a3.to_ulong()<<"\t"<<a4.to_ulong()<<endl;

     cout<<a1.to_ulong()<<"\t";
     cout<<a2.to_ulong()<<"\t";
     cout<<a3.to_ulong()<<"\t";
     cout<<a4.to_ulong()<<endl;

     return 0;
}
int main(int argc, char *argv[])
{
     if(argc <= 1)
     {
	  cout<<"usage: "<<argv[0]<<" IP_address"<<endl;
	  exit(-1);
     }
     int i;
     for (i = 1; i < argc; i++) 
     {
	  fun(argv[i]);
     }

     return 0;
}
