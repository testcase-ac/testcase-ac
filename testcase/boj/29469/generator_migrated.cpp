#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	cout<<rnd.next(1LL,(long long)(1e18))<<' '<<rnd.next(2,1000000000);
}
