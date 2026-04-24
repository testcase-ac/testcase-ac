#include <bits/stdc++.h>
using namespace std;
const int MX = 500002, LOGMX = 20;
int P[LOGMX][MX*2], k, cnt;
// Suffix-array doubling implementation adapted for this solution.
// Reference: https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
// BOJ 9248
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
	string s;
	cin >> s;
	int n = s.size();
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
		for(int i=1; i<n; i++)
			P[k][arr[i]] = f(arr[i-1], arr[i]) ? i+1 : P[k][arr[i-1]];
	}
	for(int i=0; i<n; i++) {
		// cout << (s.c_str()+arr[i]) << '\n';
		cout << arr[i]+1 << ' ';
	}
	cout << "\nx ";
	for(int i=0; i<n-1; i++)
		cout << lcp(arr[i], arr[i+1]) << ' ';
}
