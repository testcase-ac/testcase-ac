#include <bits/stdc++.h>
using namespace std;

int dp[100001];
int f(int i) {
	if(i <= 100000 && dp[i])
		return dp[i];
	int r = max(i, f(i%2 ? 3*i+1 : i/2));
	if(i <= 100000)
		dp[i] = r;
	return r;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	dp[1] = 1;
	int n;
	cin >> n;
	while(n--) {
		int k;
		cin >> k;
		cout << f(k) << '\n';
	}
}
