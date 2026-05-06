#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(2,100);
    cout<<n<<'\n';
    while(n--) cout<<rnd.next(0,(1<<24)-1)<<'\n';
}
