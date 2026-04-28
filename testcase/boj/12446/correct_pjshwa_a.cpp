#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include <string.h>
#include <queue>
#include <stack>
#define pb push_back
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
ll mod=1e9+7;
ll exp(ll x,ll t,ll md){ll ret=1;while(t){if(t%2){ret=(ret*x)%md;t--;}else{x=(x*x)%md;t/=2;}}return ret;} 
ll gcd(ll x,ll y){return x%y==0?y:gcd(y,x%y);}
ll lcm(ll x,ll y){return x*(y/gcd(x,y));}
ll bsum(ll u,ll b){return u<b?u:bsum(u/b,b)+u%b;}
ll prival(ll u,ll p){int cn=0;while(u%p==0){cn++;u=u/p;}return cn;}
bool isprime(ll x){for(ll i=2;i*i<=x;i++){if(x%i==0){return false;}}return true;}
void YAY(void){cout<<"YES"<<endl;}
void NAY(void){cout<<"NO"<<endl;}
ll CUT=1111;
int tc; ll a, b, c;
ll dp[1111][1111];
ll phi[1111];

ll spex(ll x, ll t) // min(CUT,x^t)
{
	ll ret=1;
	x=min(x,CUT);
	while(t)
	{
		if(t%2==1)
		{
			ret=min(ret*x,CUT);
			t--;
		}
		else if(t%2==0)
		{
			x=min(x*x,CUT);
			t/=2;
		}
	}
	return ret;
}

ll solve(ll num, ll lev, ll md)
{
	int i, j;
	if(md==1)
	{
		return 0;
	}
	ll t=md;
	vector<int> cand;
	while(t!=1)
	{
		cand.push_back(t);
		t=phi[t];
	}
	cand.push_back(1);
	for(i=0 ; i<cand.size() ; i++)
	{
		dp[0][i]=num%cand[i];
	}
	for(i=1 ; i<=lev ; i++)
	{
		for(j=0 ; j<cand.size()-1 ; j++)
		{
			if(num<CUT) dp[i][j]=exp(dp[i-1][j],num,cand[j]); // exponent too small -> straightforward calculation
			else dp[i][j]=exp(dp[i-1][j],cand[j+1]*CUT+dp[i-1][j+1],cand[j]); // exponent large enough -> gcd not a problem anymore -> modular on exponent ok
		}
		dp[i][cand.size()-1]=0;															// for example, gcd(4^10,6^5)!=gcd(4^10,6^8) but gcd(4^10,6^100)=gcd(4^10,6^200)
		num=spex(num,num);
	}
	return dp[lev][0];
}

void prepr(void)
{
	int i, j;
	for(i=1 ; i<=1110 ; i++)
	{
		phi[i]=i;
	}
	for(i=1 ; i<=1110 ; i++)
	{
		for(j=2 ; i*j<=1110 ; j++)
		{
			phi[i*j]-=phi[i];
		}
	}
}

int main(void)
{
	cin>>tc;
	prepr();
	int i;
	for(i=1 ; i<=tc ; i++)
	{
		scanf("%lld %lld %lld",&a,&b,&c);
		printf("Case #%d: %lld\n",i,solve(a,b,c));
	}
	return 0;
}
