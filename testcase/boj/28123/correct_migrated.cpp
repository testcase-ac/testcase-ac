#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n,k,x,a;
    cin>>n>>k>>x;
    int r[10]={0,1,2,2,3,3,3,3,4,4};
    a=n+1-r[x]-3*k+3;
    if(x==4||x==8||x==9) a+=1;
    cout<<a;
}
