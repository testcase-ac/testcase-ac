#include <bits/stdc++.h>
using namespace std;
int key[] = {9, 4, 8, 7, 2, 1, 6, 5, 0, 3};
int conv(int i) {
	int r = 0, f = 1;
	while(i) {
		r += key[i%10]*f;
		i /= 10;
		f *= 10;
	}
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int l, r, n;
	cin >> l >> r;
	n = r-l+1;
	int a[n];
	for(int i=0; i<n; i++) {
		a[i] = l+i;
	}
	sort(a, a+n, [](int x, int y){
		string s = to_string(x), t = to_string(y);
		for(int i=0; i<min(s.size(), t.size()); i++) {
			if(s[i] != t[i])
				return key[s[i]-'0'] < key[t[i]-'0'];
		}
		return s.size() < t.size();
	});
	for(int i=0; i<n; i++) {
		cout << a[i] << (i%10 == 9 ? '\n' : ' ');
	}
}
