#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	long long a=rnd.next(1LL,(long long)1e18);
	cout<<a<<' '<<rnd.next(a,(long long)1e18);
}
