#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int q=rnd.next(1,20);
    cout<<q<<'\n';
    while(q--) cout<<rnd.next(1,1000000)<<'\n';
}
