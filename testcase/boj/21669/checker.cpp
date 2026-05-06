#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll M=9e18;
int main(int argc,char*argv[]) {
	registerTestlibCmd(argc,argv);
	ll s=inf.readLong(1,M);
	ll v=ouf.readLong(1,M),a=ouf.readLong(1,M),b=ouf.readLong(1,M),c=ouf.readLong(1,M);
	ll V=ans.readLong(1,M);
	if(v!=V) quitf(_wa,"wrong max volume: expected %d, found %d",V,v);
	ll t=a*b+b*c+c*a;t*=2;
	if(t>s) quitf(_wa,"exeeded surface area limit: %d > %d",t,s);
	if(a*b*c!=v) quitf(_wa,"lengths don't match with volume: %d != %d",a*b*c,v);
	quitf(_ok,"correct");
}
