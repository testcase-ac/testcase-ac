#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll f(int t) {
	int d = 1;
	while(t > (1<<d)) {
		t -= (1<<d);
		d++;
	}
	t--;
	string s;
	for(int i=d-1; i>=0; i--) {
		if(t&(1<<i)) s.push_back('7');
		else s.push_back('4');
	}
	return stoll(s);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b;
	cin >> a >> b;
	int st = -1;
	for(int i=1;; i++) {
		ll t = f(i);
		if(t >= a && st == -1)
			st = i;
		if(t > b)
			return !(cout << (st == -1 ? 0 : i - st));
	}
}
