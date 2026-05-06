#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int t=rnd.next(1,20);
    cout<<t<<'\n';
    while(t--) cout<<rnd.next(1,1000)<<'\n';
}
