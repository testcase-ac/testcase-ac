#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	int n=g()%50+1;
	cout<<n<<'\n';
	while(n--) {
	    int l=g()%500000+1,r=g()%500000+1;
	    if(l>r) swap(l,r);
	    cout<<l<<' '<<r<<'\n';
	}
}
