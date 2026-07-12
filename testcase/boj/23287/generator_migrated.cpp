#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	long n,t;
	while(1) {
	n=rnd.next(1LL,(long long)1e18);t=n;
	for(int i=2;i<100000;i++) {
	    while(t%i==0) t/=i;
	} if(t==1) {cout<<n<<'\n';return 0;}
	}
}
