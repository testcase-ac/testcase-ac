#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,1000);
	while(n--) cout<<char(rnd.next('a','z'));
}
