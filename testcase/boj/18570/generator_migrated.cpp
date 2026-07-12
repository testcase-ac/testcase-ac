#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,100);
    cout<<n<<'\n';
    while(n--) cout<<rnd.next(1,987654321)<<(n?' ':'\n');
}
