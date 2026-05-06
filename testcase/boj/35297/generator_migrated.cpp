#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int l=rnd.next(1,1000);
	string a="KSA";
	while(l--) cout<<a[rnd.next(0,2)];
}
