#include "testlib.h"
using namespace std;
bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int p;
	do {
		p = rnd.next(2,2999999);
	} while (!isPrime(p));
	cout<<p<<"\n";
}
