#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int q=rnd.next(1,10);
	cout<<q<<'\n';
	while(q--) {
	    int a=rnd.next(1,1000000000);
	    int b=rnd.next(a,1000000000);
	    cout<<a<<' '<<b<<' '<<rnd.next(0,100000)<<'\n';
	}
}
