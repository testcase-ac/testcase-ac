#include <bits/stdc++.h>
using namespace std;
int n, k, ans = 0;
int wordhas[50];
void f(int d, int t, int mask) {
	if(!t) {
		int cnt = 0;
		for(int i=0; i<n; i++)
			cnt += ((wordhas[i]&mask) == wordhas[i]);
		ans = max(ans, cnt);
		return;
	}
	for(int i=d; i+t<=26; i++) {
		if(mask&(1<<i)) continue;
		f(i, t-1,mask|(1<<i));
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k;
	if(k < 5) return !(cout << 0);
	else if(k == 26) return !(cout << n);
	int init = 0;
	for(char c: {'a', 'n', 't', 'i', 'c'}) {
		init |= 1<<(c-'a');
	}
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		for(char c: s)
			wordhas[i] |= (1<<(c-'a'));
	}
	f(0,k-5,init);
	cout << ans;
}
