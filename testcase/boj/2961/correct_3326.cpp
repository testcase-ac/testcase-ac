#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll s[10], b[10], ans = LLONG_MAX;
int n;
void f(int i, ll st, ll bt) {
	if(i == n) {
		if(bt)
			ans = min(ans, abs(st-bt));
		return;
	}
	f(i+1, st, bt);
	if(!__builtin_mul_overflow(st, s[i], &st))
		f(i+1, st, bt+b[i]);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> s[i] >> b[i];
	}
	f(0, 1, 0);
	cout << ans;
}
