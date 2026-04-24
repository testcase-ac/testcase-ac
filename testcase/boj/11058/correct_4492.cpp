#include <bits/stdc++.h>
using namespace std;
/*
optimal substructure: can be solved from smaller instance of problem
overlapping subproblem: "smaller instance of problem" overlaps while going down the tree

Max at N:
	If use buffer:
		Ctrl A, C, V*t from N-2-t
	else:
		A from N-1
*/
#define ll long long
ll dp[101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	dp[1] = 1;
	for(int i=2; i<=n; i++) {
		dp[i] = dp[i-1]+1;
		for(int t=1;i-2-t>=1; t++) {
			dp[i] = max(dp[i], dp[i-2-t]*(t+1));
		}
	}
	cout << dp[n];
}
