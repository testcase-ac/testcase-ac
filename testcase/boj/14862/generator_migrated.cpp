#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int t=rnd.next(1,10);
	cout<<t<<'\n';
	while(t--) {
	    int k=rnd.next(2,5);
	    cout<<k<<'\n';
	    while(k--) {
	        int a=rnd.next(1,200000);
	        int b=rnd.next(a,200000);
	        cout<<a<<' '<<b<<'\n';
	    }
	}
}
