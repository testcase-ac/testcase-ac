#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MX = 10005;
ll a[MX], b[MX];
int n;
int nxt(int i){return i == n-1 ? 0 : i+1;}
ll gen(int init, ll val) {
	int i = init;
	ll mn = val;
	a[i] = val;
	do {
		int i1 = nxt(i), i2 = nxt(i1), i3 = nxt(i2);
		a[i3] = a[i]-b[i1]+b[i2];
		i = i3;
		mn = min(mn, a[i]);
	} while(i != init);
	return mn;
}
void add(int init, ll diff) {
	if(diff > 0) {
		int i = init;
		do {
			a[i] += diff;
			i = (i+3)%n;
		} while(i != init);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> b[i];
	if(n % 3) {
		gen(0, 1);
		add(0, (b[1]-a[0]-a[1]-a[2])/3);
	} else {
		add(0, 1-gen(0, 1));
		add(1, 1-gen(1, 1));
		gen(2, b[1]-a[0]-a[1]);
	}
	for(int i=0; i<n; i++) {
		cout << a[i] << '\n';
	}
}
