#include <bits/stdc++.h>
using namespace std;
bool isp(int n) {
    if(n<2) return 0;
    for(int i=2;i<n;i++) if(n%i==0) return 0;
    return 1;
}
int main() {
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    if(n==2&&a[0]==1&&isp(a[1])) {cout<<"NO";return 0;}
    cout<<"YES\n"<<n<<'\n';
    for(int i:a) cout<<i<<' ';
}
