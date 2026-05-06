#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int p=rnd.next(1,500);
	int q=rnd.next(p*2-1,1000);
	cout<<p<<' '<<q;
}
