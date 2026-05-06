#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int t=rnd.next(1,10);
	cout<<t<<'\n';
	while(t--) cout<<rnd.next(1,1000000000)<<' '<<rnd.next(1,1000000000)<<' '<<rnd.next(1,1000000000)<<' '<<rnd.next(1,1000000000)<<' '<<rnd.next(1,1000000000)<<'\n';
}
