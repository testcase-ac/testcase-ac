#include <bits/stdc++.h>
using namespace std;
int main() {
    long n,m,ans=0;
    cin>>n>>m;
    if(n%2==0) {
        for(int i=1;;i++) {
            bool f=0;
            int p=n,q=1-n;
            for(int j=1;j<n;j++) {
                p*=i;q*=i;
                if(abs(p)>m||abs(q)>m) {f=1;break;}
            } q*=i;
            if(abs(q)>m) f=1;
            if(f) break;
            ans++;
        } cout<<ans*2+1;
    } else {
        ans=(m*2+1)*(m+1);
        for(int p=1;p<=m;p++) {
            long double t=(long double)p/n;
			long double x=pow(t,1.0/(n-1));
			long double l=pow(x,n)-p*x,r=-l;
			l=ceil(l),r=floor(r);
			l=max(l,-(long double)m),r=min(r,(long double)m);
			ans+=round(l+m)+round(m-r);
        } cout<<ans;
    }
}
