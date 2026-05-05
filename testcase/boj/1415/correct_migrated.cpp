#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
#define ll long long
#define M (500001)
map<int,int> mp;
ll dp[M];
int prime[M];
int pc;
bool p[M];
int main(){
	int n, maxi = 0;
	ll ans = 0;
	dp[0]=1;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int a;
		scanf("%d",&a);
		if(mp.find(a) == mp.end())mp[a]=1;
		else mp[a]++;
	}
	for(auto it = mp.begin(); it!=mp.end(); it++){
		int cost = it->first;
		int how = it->second;
		if(cost > 0){
			for(int j=maxi; j>=0; j--){
				if(dp[j]){
					for(int k=1; k<=how; k++){
						dp[j + k*cost] += dp[j];
					}
				}
			}
			maxi += cost*how;
		}
		else{
			for(int j=maxi; j>=0; j--)dp[j]*=how+1;
		}
	}
	for(ll i=2; i<=maxi; i++){
		if(p[i])continue;
		prime[pc++]=i;
		for(ll j = i*i; j<=maxi; j+=i)p[j]=true;
	}
	for(int j=0; j<pc; j++)ans += dp[prime[j]];
	cout<<ans<<endl;
	return 0;
}
