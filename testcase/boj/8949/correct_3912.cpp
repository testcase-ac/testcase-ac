#include <bits/stdc++.h>
using namespace std;

#define sz(x) ((int)(x).size())
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string a, b;
	cin >> a >> b;
	if(sz(a) > sz(b)) swap(a,b);
	while(sz(a) < sz(b))
		a = '0' + a;
	for(int i=0; i<sz(a); i++) {
		cout << a[i]-'0'+b[i]-'0';
	}
}
