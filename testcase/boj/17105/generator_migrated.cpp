#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
	mt19937_64 g(rd());
	int t=g()%100+1;
	cout<<t<<'\n';
	while(t--) cout<<(g()%499996)*2+7<<'\n';
}
