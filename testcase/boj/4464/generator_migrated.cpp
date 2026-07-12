#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,30);
	while(n--) cout<<rnd.next(1ULL,999999999999999999ULL)<<'\n';
    cout<<0<<'\n';
}
