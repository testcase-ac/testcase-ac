#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
char f(string& s, int i) {
	return i < s.size() ? s[i] : 0;
}
string arr[3000];
int fac[30];
int ans = 1;
void f(int l, int r, int t) {
	if(l+1 == r)
		return;
	int gcnt = 0;
	for(int i=l, j=l; i<r; i=j) {
		while(j < r && f(arr[i], t) == f(arr[j], t))
			j++;
		f(i, j, t+1);
		gcnt++;
	}
	ans = (ans*fac[gcnt]) % MOD;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	fac[0] = 1;
	for(int i=1; i<=30; i++)
		fac[i] = (fac[i-1]*i)%MOD;
	sort(arr, arr+n);
	f(0, n, 0);
	cout << ans;
}
