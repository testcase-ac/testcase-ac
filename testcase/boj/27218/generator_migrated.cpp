#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(2,200000);
	int k=rnd.next(2,30);
	cout<<n<<' '<<k<<'\n';
}
