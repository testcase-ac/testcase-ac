//GPT 코드
#include "testlib.h"
using namespace std;
int main(int c,char**v){
	registerGen(c,v,1);
	int n=rnd.next(0,30);
	printf("%d\n",n);
	int d=n?2000000/n:1;
	for(int i=0;i<n;i++){
		int y1=-1000000+i*d+rnd.next(0,d);
		int y2=-1000000+(i+1)*d-rnd.next(0,d);
		if(y1==y2)y2++;
		int x1=rnd.next(-1000000,1000000);
		int x2=rnd.next(-1000000,1000000);
		while(x1==x2)x2=rnd.next(-1000000,1000000);
		printf("%d %d %d %d\n",x1,y1,x2,y2);
	}
	printf("%d\n",rnd.next(-1000000,1000000));
}
