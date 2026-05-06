#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	cout<<rnd.next(2,30)<<' '<<rnd.next(2,30);
}
