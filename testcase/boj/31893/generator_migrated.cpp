#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	int n=uniform_int_distribution<int>(2,100)(rd);
	int c=uniform_int_distribution<int>(2,n*10/9)(rd);
	cout<<n<<' '<<c<<'\n';
	for(int i=0;i<n;i++) {
		cout<<uniform_int_distribution<int>(1,1000)(rd);
		if(i<n-1) cout<<' ';
	}
}
