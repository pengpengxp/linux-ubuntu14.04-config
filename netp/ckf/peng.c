#include<stdio.h>
#include<stdlib.h>
int main()
{
	time_t peng;
	peng=time(0);
	int xie=peng%255;
	while(1)
	{
		if(xie != 0 && xie !=255 && xie != 1)
		{
			printf("%x\n",xie);
			return 0;
		}
	}
}
