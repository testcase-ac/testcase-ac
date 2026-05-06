//GPT 코드
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(int argc,char*argv[]) {
	registerTestlibCmd(argc,argv);

	ll n=inf.readLong();
	int k=inf.readInt();

	string s=ouf.readToken();

	if(s=="NO") {
		ouf.readEof();
		quitf(_ok,"NO");
	}

	if(s!="YES")
		quitf(_wa,"Expected YES or NO");

	vector<ll>a(k);
	for(int i=0;i<k;i++)
		a[i]=ouf.readLong();

	ouf.readEof();

	set<ll>st;
	ll sum=0;

	for(int i=0;i<k;i++) {
		if(a[i]<=0)
			quitf(_wa,"Non-positive number");
		if(!st.insert(a[i]).second)
			quitf(_wa,"Numbers not distinct");
		sum+=a[i];
	}

	if(sum!=n)
		quitf(_wa,"Sum is incorrect");

	for(int i=0;i<k;i++) {
		ll x=n-a[i];
		ll r=sqrt((long double)x);
		if(r*r!=x)
			quitf(_wa,"Not a square");
	}

	quitf(_ok,"YES");
}
