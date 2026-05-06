#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,100),k=rnd.next(5,1000000);
	cout<<n<<' '<<k<<'\n';
	while(n--) {
	    int x=rnd.next(0,3);
	    if(x==0) cout<<1;
	    if(x==1) cout<<3;
	    if(x==2) cout<<4;
	    if(x==3) cout<<k*rnd.next(1,1000000000/k);
	    cout<<' ';
	}
}
