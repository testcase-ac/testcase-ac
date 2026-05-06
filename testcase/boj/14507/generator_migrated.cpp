#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(4,1000);
	cout<<n<<'\n';
	while(n--) {
	    cout<<rnd.next(-1000,1000)<<' '<<rnd.next(-1000,1000)<<'\n';
	}
}
