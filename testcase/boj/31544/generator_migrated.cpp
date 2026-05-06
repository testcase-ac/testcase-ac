#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	cout<<rnd.next(1,1000000)<<' '<<rnd.next(1,1000000)<<' '<<rnd.next(1,1000000);
}
