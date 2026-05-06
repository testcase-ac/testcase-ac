#include <bits/stdc++.h>
#define ll long long
using namespace std;
string x="Messi ",y="Messi Gimossi ";
ll l[50];
char f(int i,ll k) {
    if(i==1) return x[k-1];
    if(i==2) return y[k-1];
    if(k<=l[i-1]) return f(i-1,k);
    return f(i-2,k-l[i-1]);
}
int main() {
    int n=x.size(),m=y.size();
    l[1]=n;l[2]=m;
    int mx=0;
    for(int i=3;;i++) {
        l[i]=l[i-1]+l[i-2];
        if(l[i]>1e10) {mx=i;break;}
    } ll M;
    cin>>M;
    char ans=f(mx,M);
    if(ans==' ') cout<<"Messi Messi Gimossi";
    else cout<<ans;
}
