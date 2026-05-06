#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,50);
	cout<<n<<'\n';
    while(n--) cout<<rnd.next(2LL,1000000000000000000LL)<<' ';
}
