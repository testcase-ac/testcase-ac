#define private public
#include <bitset>
#undef private
#include <bits/stdc++.h>
using namespace std;
void sub(bitset<2000>& a,bitset<2000>& b) {
    unsigned long long borrow=0;
    for(int i=0;i<32;i++) {
        unsigned long long before=a._M_w[i];
        a._M_w[i]=before-b._M_w[i]-borrow;
        borrow=before<b._M_w[i] || (borrow && before==b._M_w[i]);
    }
}
int main() {
    int m=0;
    string a,b,aa;
    bitset<2000> y[26];
    cin>>a>>b;
    a+=a;
    for(int i=0;i<b.length();i++) y[b[i]-'a'][i]=1;
    for(int j=0;j<a.length()/2;j++) {
        bitset<2000> x,r,k;
        aa=a.substr(j,a.length()/2);
        for(int i=0;i<aa.length();i++) {
            x=y[aa[i]-'a']|r;
            r<<=1;r[0]=1;
            k=x;sub(k,r);
            r=x&(x^k);
        } m=max(m,(int)r.count());
    } reverse(b.begin(), b.end());
    for(int i=0;i<26;i++) y[i].reset();
    for(int i=0;i<b.length();i++) y[b[i]-'a'][i]=1;
    for(int j=0;j<a.length()/2;j++) {
        bitset<2000> x,r,k;
        aa=a.substr(j,a.length()/2);
        for(int i=0;i<aa.length();i++) {
            x=y[aa[i]-'a']|r;
            r<<=1;r[0]=1;
            k=x;sub(k,r);
            r=x&(x^k);
        } m=max(m,(int)r.count());
    } cout<<m;
}
