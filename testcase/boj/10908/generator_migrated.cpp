#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	cout<<rnd.next(0LL,1000000000000LL)<<' '<<rnd.next(1LL,1000000000000LL);
}
