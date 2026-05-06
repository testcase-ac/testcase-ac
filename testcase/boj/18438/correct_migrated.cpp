#include <bits/stdc++.h>
using namespace std;
string a,b,s;
void lcs(int l,int r,int L,int R) {
    if(l>r||L>R) return;
    if(l==r) for(int i=L;i<=R;i++) if(a[l]==b[i]) {s+=b[i];return;}
    int m=(l+r)/2;
    vector<int> v1(R-L+3),v2(R-L+3),t(R-L+3);
    for(int i=l;i<=m;i++) {
        for(int j=L;j<=R;j++) {
            if(a[i]==b[j]) v1[j-L+1]=t[j-L]+1;
            else v1[j-L+1]=max(v1[j-L],t[j-L+1]);
        } t=v1;
    } t=vector<int> (R-L+3);
    for(int i=r;i>m;i--) {
        for(int j=R;j>=L;j--) {
            if(a[i]==b[j]) v2[j-L+1]=t[j-L+2]+1;
            else v2[j-L+1]=max(v2[j-L+2],t[j-L+1]);
        } t=v2;
    } int mx=L; 
    for(int i=L+1;i<=R+1;i++) if(v1[i-L]+v2[i-L+1]>v1[mx-L]+v2[mx-L+1]) mx=i;
    lcs(l,m,L,mx-1);
    lcs(m+1,r,mx,R);
}
int main() {
    cin>>a>>b;
    lcs(0,a.length()-1,0,b.length()-1);
    cout<<s.length()<<'\n'<<s;
}
