#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int t=rnd.next(1,50);
    while(t--) cout<<rnd.next(1,1000000000)<<'\n';
}
