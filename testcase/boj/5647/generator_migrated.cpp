#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,30);
	while(n--) cout<<rnd.next(1LL,99999999999999LL)<<'\n';
	cout<<0<<'\n';
}
