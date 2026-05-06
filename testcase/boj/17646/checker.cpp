#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int main(int argc,char*argv[]) {
	registerTestlibCmd(argc,argv);
	ll n=inf.readLong(1,1000000000000000000LL);
	int k1=ouf.readInt(1,4);
	vector<ll> a(k1);
	ll s1=0;
	for(int i=0;i<k1;i++){
		a[i]=ouf.readLong(1,n);
		s1+=a[i]*a[i];
	} int k2=ans.readInt(1,4);
	vector<ll> b(k2);
	ll s2=0;
	for(int i=0;i<k2;i++){
		b[i]=ans.readLong(1,n);
		s2+=b[i]*b[i];
	} if(s1!=n)quitf(_wa,"wrong sum of squares in output");
	if(k1>k2)quitf(_wa,"not minimal count of squares: %d > %d",k1,k2);
	quitf(_ok,"correct: %d squares",k1);
}
