#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cd;
void fft(vector<cd>& a, bool inv) {
    int n=a.size(),j=0;
    vector<cd> x(n/2);
    for(int i=1;i<n;i++) {
        int b=(n>>1);
        while(j>=b) {
            j-=b;
            b>>=1;
        } j+=b;
        if(i<j) swap(a[i],a[j]);
    } double ang=2*acos(-1)/n*(inv?-1:1);
    for(int i=0;i<n/2;i++) x[i]=cd(cos(ang*i),sin(ang*i));
    for(int i=2;i<=n;i<<=1) {
		int p=n/i;
        for(int j=0;j<n;j+=i) for(int k=0;k<i/2;k++) {
			cd u=a[j+k],v=a[j+k+i/2]*x[p*k];
			a[j+k]=u+v;
			a[j+k+i/2]=u-v;
        }
    } if(inv) for(int i=0;i<n;i++) a[i]/=n;
}
vector<int> mult(vector<int>& a,vector<int>& b) {
    vector<cd> A(a.begin(),a.end()),B(b.begin(),b.end());
    int n=2;
    while(n<a.size()+b.size()) n<<=1;
    A.resize(n);B.resize(n);
    fft(A,0);fft(B,0);
    for(int i=0;i<n;i++) A[i]*=B[i];
    fft(A,1);
    vector<int> r(n);
    for(int i=0;i<n;i++) r[i]=(int)round(A[i].real());
    return r;
}
int main() {
    string s;
    cin>>s;
    int l=s.length();
    vector<int> a(l),b(l),c;
    for(int i=0;i<l;i++) {
        if(s[l-1-i]=='A') a[i]=1;
        else b[l-i-1]=1;
    } c=mult(a,b);
    for(int i=l-2;i>=0;i--) cout<<c[i]<<'\n';
}
