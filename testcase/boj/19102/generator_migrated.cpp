#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	int t=uniform_int_distribution<int>(1,20)(rd);
	cout<<t;
	while(t--) cout<<'\n'<<uniform_int_distribution<long long>(2,1000000000000000)(rd);
}
