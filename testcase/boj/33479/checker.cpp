#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc,char* argv[]) {
	registerTestlibCmd(argc,argv);
	int p=inf.readInt(1,1000000000);
	long long n=inf.readLong(1,1000000000000000000LL);
	long long x=ouf.readInt();
	long long y=ans.readInt();
	if(x!=y) quitf(_wa,"Wrong Answer");
	quitf(_ok,"Accepted");
}
