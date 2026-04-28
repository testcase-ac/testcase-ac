#include <bits/stdc++.h>
using namespace std;
unsigned n,a[100000],ans;
main(){
	cin>>n;for(int i=0;i<n;i++)cin>>a[i];sort(a,a+n);
	for(int i=0;i<n;i++){
		int s=0, e=n;
		for(int j=31;j>=0;j--){
			if((a[s]&(1<<j))==(a[e-1]&(1<<j))) continue;
			(a[i]&(1<<j)?e:s)=lower_bound(a+s,a+e,1<<j,[&](int a, int b){return (a&(1<<j)) < (b&(1<<j));})-a;
		}
		ans=max(ans,a[i]^a[s]);
	}
	cout<<ans;
}
