#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	int t=uniform_int_distribution<int>(1,3)(rd);
	if(t==1) cout<<"1\n"<<uniform_int_distribution<long long>(1000000000,1000000000000)(rd);
	else if(t==2) {
	    t=uniform_int_distribution<int>(1,100)(rd);
	    cout<<t;
	    while(t--) cout<<'\n'<<uniform_int_distribution<int>(1000000,1000000000)(rd);
	} else {
	    t=uniform_int_distribution<int>(1,10000)(rd);
	    cout<<t;
	    while(t--) cout<<'\n'<<uniform_int_distribution<int>(1,1000000)(rd);
	}
}
