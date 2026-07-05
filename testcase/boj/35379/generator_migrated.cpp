#include "testlib.h"
using namespace std;

int gcd(int a, int b) {
	while (b != 0) {
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int p=rnd.next(1,500);
	int q=rnd.next(p*2-1,1000);
	while (gcd(p, q) != 1) {
		q=rnd.next(p*2-1,1000);
	}
	cout<<p<<' '<<q;
}
