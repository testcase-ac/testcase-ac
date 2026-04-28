#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int DL, DW;
	double G, L;
	cin >> DL >> DW >> G >> L;
	G *= 0.01;
	L *= 0.01;

	vector<double> dp(101);
	dp[100] = 1 / (1-L);
	for(int i = 99; i >= 0; i--){
		double M = 0.01 * i;
		dp[i] = 1 + L * dp[min(i + DL, 100)] + (1-L) * (1-M) * dp[min(i + DW, 100)];
	}
	cout << setprecision(69) << dp[0] / G << endl;
}

