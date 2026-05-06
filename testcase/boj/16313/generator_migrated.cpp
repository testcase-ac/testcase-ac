#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int a[4];
	while(1) {
	    for(int i=0;i<4;i++) a[i]=rnd.next(1,1000);
	    sort(a,a+4);
	    if(a[3]<a[0]+a[1]+a[2]) {
	        shuffle(a,a+4);
	        break;
	    }
	} cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3];
}
