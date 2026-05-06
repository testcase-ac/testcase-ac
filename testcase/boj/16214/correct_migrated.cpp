#include<iostream>
#define l long
using namespace std;l p(l n){l a=n;for(l p=2;p*p<=n;p++){if(n%p==0)a=a/p*(p-1);while(n%p==0)n=n/p;}return n==1?a:a/n*(n-1);}l s(l n,l m){if(n==1||m==1) return 1;l a=n,b=s(n,p(m))+p(m),r=1;while(b){if(b%2)r=r*a%m;b/=2;a=a*a%m;}return r;}main(){l t,n,m,r;cin>>t;while(t--) {cin>>n>>m;cout<<s(n,m)%m<<'\n';}}
