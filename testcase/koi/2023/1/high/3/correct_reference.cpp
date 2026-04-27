#include <iostream>
using namespace std;
using ll=long long;
const int N=105,M=10005;
const ll inf=1e15;
int n,l,r,a[N];
ll s[N],dp[N][M];
int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i]-l;
	r-=l;
	if(s[n]<0||s[n]>r*n){
		cout<<"-1\n";
		return 0;
	}
	for(int i=0;i<=n;i++) for(int j=0;j<=r*n;j++) dp[i][j]=inf;
	dp[0][0]=0;
	for(int v=0;v<=r;v++) for(int i=1;i<=n;i++) for(int j=v;j<=v*i;j++){
		dp[i][j]=min(dp[i][j],dp[i-1][j-v]+abs(s[i]-j));
	}
	cout<<dp[n][s[n]]<<"\n";
	return 0;
}