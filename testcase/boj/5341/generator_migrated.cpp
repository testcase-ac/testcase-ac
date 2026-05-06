#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
	int t=g()%10+1;
	while(t--) cout<<g()%100+1<<'\n';
	cout<<0;
}
