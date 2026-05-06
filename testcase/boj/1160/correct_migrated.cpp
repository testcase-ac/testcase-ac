#include <bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;
lll M,a,c,x0;
void mult(lll A[2][2],lll B[2][2]) {
	lll x=(A[0][0]*B[0][0]+A[0][1]*B[1][0])%M;
	lll y=(A[0][0]*B[0][1]+A[0][1]*B[1][1])%M;
	lll z=(A[1][0]*B[0][0]+A[1][1]*B[1][0])%M;
	lll w=(A[1][0]*B[0][1]+A[1][1]*B[1][1])%M;
	A[0][0]=x;A[0][1]=y;A[1][0]=z;A[1][1]=w;
}
void pw(lll F[2][2],ll n) {
    lll X[2][2]={{a,c},{0,1}};
    while(n>0) {
        if(n%2) mult(F,X);
        mult(X,X);
        n/=2;
    }
}
lll sol(ll n) {
    if(n==0) return 0;
    lll F[2][2]={{1,0},{0,1}};
    pw(F,n);
    return (F[0][0]*x0+F[0][1])%M;
}
int main() {
    ll n,g,mm,aa,cc,xx0;
    cin>>mm>>aa>>cc>>xx0>>n>>g;
    M=mm;a=aa;c=cc;x0=xx0;
    ll t=(ll)sol(n)%g;
    cout<<t;
}
