#include <stdio.h>
#define MOD (1000000007)
#define ll long long
ll c[51][51];
ll C(int a, int b){
	if(c[a][b])return c[a][b];
	if(b == 0 || a == b)return c[a][b] = 1;
	return c[a][b] = (C(a-1,b) + C(a-1,b-1))%MOD;
}
int max(int a, int b){return a>b?a:b;}
int main(){
	int a, b, c, n, f = 1, m;
	scanf("%d %d %d %d",&n,&a,&b,&c);
	m = max(a,max(b,c));
	ll ans = 0;
	for(int i=n; i>=m; i--){
		ans += MOD + f*((((((C(i, a)*C(i, b))%MOD)*C(i, c))%MOD)*C(n,i))%MOD);
		ans%=MOD;
		f*=-1;
	}
	printf("%lld\n",ans);
	return 0;
}
