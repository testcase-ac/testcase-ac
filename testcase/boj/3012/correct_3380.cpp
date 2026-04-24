#include <bits/stdc++.h>
using namespace std;
#define ll long long
char arr[201];
ll dp[200][200], dpe[200][200];
bool over[200][200], overe[200][200], ov;
const int MOD = 100000;
bool ispr(char a, char b) {
	return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}');
}
bool isl(char a) {
	return a == '(' || a == '[' || a == '{';
}
bool isr(char a) {
	return a == ')' || a == ']' || a == '}';
}
int fpr(char a, char b) {
	if(a == '?' && b == '?') return 3;
	else if((a == '?' && isr(b)) || (isl(a) && b == '?') || ispr(a, b)) return 1;
	else return 0;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> arr;
	if(n&1) return !(cout << 0);
	for(int i=0; i<n-1; i++) {
		dp[i][i+1] = dpe[i][i+1] = fpr(arr[i], arr[i+1]);
	}
	for(int w=3; w<n; w+=2) {
		for(int l=0; l+w<n; l++) {
			int r = l+w;
			dpe[l][r] = dp[l+1][r-1]*fpr(arr[l], arr[r]);
			dp[l][r] = dpe[l][r];
			for(int i=l+2; i<r; i++) 
				dp[l][r] += dpe[l][i-1]*dp[i][r];
			if(dp[l][r] >= 2*MOD) {
				dp[l][r] = MOD + dp[l][r]%MOD;
			}
		}
	}
	printf(dp[0][n-1] >= MOD ? "%05lld\n" : "%lld\n", dp[0][n-1]%MOD);
}
