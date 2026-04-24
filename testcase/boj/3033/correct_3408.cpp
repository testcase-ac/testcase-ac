#include <bits/stdc++.h>
using namespace std;
const int MX = 200000, LOGMX = 19;
int P[LOGMX][MX*2], k, cnt;
int lcp(int a, int b) {
	int ret = 0;
	for(int t=k-1; t>=0; t--) {
		if(P[t][a] == P[t][b]) {
			a += 1 << t;
			b += 1 << t;
			ret += 1 << t;
		}
	}
	return ret;
}
int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	int arr[n];
	for(int i=0; i<n; i++) {
		P[0][i] = s[i];
		arr[i] = i;
	}
	auto f = [&](int a, int b) {
		return tie(P[k-1][a], P[k-1][a+cnt]) < tie(P[k-1][b], P[k-1][b+cnt]);
	};
	for(k=1, cnt=1; cnt<n; k++, cnt*=2) {
		sort(arr, arr+n, f);
		P[k][arr[0]] = 1;
		for(int i=1; i<n; i++) {
			P[k][arr[i]] = P[k][arr[i-1]];
			if(f(arr[i-1], arr[i]))
				P[k][arr[i]]++;
		}
	}
	int ans = 0;
	for(int i=0; i<n-1; i++) {
		ans = max(ans, lcp(arr[i], arr[i+1]));
	}
	cout << ans;
}
