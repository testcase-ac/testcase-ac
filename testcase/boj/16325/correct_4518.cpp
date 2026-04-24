#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007

int comb[2520][2520];
void cal_comb() {
	for(int i=2; i<=2500; i++) {
		for(int j=1; j<=i; j++) {
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
		}
	}
}
int power(int a, int b) {
	if(b==0)
		return 1LL;
	return (a * power(a,b-1)) % MOD;
}
int32_t main() {
	for(int i=1; i<=2500; i++) {
		comb[i][0] = 1;
		comb[i][i] = 1;
	}
	cal_comb();
	int k, n;
	scanf("%lld %lld",&k,&n);
	for(int i=0,x; i<k-1; i++) {
		scanf("%lld",&x);
	}
	if(k==1 && n==1) {
		printf("1");
		return 0;
	}
	int cur = 1, ans = 0;
	for(int i=n; i>=2; i--) {
		ans = (ans + cur * (((comb[n][i] * i) % MOD) * power(i-1,k-1)) %MOD + MOD)%MOD;
		cur = -cur;
	}
	printf("%lld", ans);
}
