#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	int n=g()%100+1;
	cout<<n<<'\n';
	for(int i=0;i<n;i++) cout<<g()%1000000000+1<<' ';
	cout<<'\n';
	int a[n];
	iota(a,a+n,1);
	shuffle(a,a+n,g);
	for(int i:a) cout<<i<<' ';
}
