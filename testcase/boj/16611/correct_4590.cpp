#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
string a,b;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    a=string(m,'a');
    for(int i=m-n;i<m;++i){
        cin>>a[i];
    }
    cin>>b;
    for(int i=m-1;i>=n;--i){
        a[i-n]=(char)((b[i]-a[i]+26)%26+'a');
    }
    cout<<a;
}
