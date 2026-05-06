//GPT 코드
#include "testlib.h"
using namespace std;

int main(int argc,char*argv[]) {
	registerTestlibCmd(argc,argv);

	long long n=inf.readLong();
	long long a=ouf.readLong();
	long long b=ouf.readLong();
	long long c=ouf.readLong();
	long long d=ouf.readLong();

	if(a<0||b<0||c<0||d<0)
		quitf(_wa,"negative number");

	__int128 s=(__int128)a*a+(__int128)b*b+(__int128)c*c+(__int128)d*d;

	if(s!=n)
		quitf(_wa,"sum of squares mismatch");

	ouf.readEof();
	quitf(_ok,"correct");
}
