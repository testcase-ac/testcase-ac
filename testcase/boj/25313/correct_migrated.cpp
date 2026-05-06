#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
using mat=vector<vector<ll>>;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
void hessenberg(mat&A) {
    int n=A.size();
    for(int i=1;i<n;i++) {
        for(int j=i;j<n;j++) { 
            if(A[j][i-1]!=0) {
                swap(A[i],A[j]);
                for(int k=0;k<n;k++) swap(A[k][i],A[k][j]);
                break;
            }
        } if(A[i][i-1]==0) continue;
        ll x=A[i][i-1],y=pw(x,M-2);
        for(int j=0;j<n;j++) A[j][i]=A[j][i]*x%M;
        for(int j=i-1;j<n;j++) A[i][j]=A[i][j]*y%M;
        for(int j=i+1;j<n;j++) {
            ll z=A[j][i-1]%M,w=(M-z)%M;
            for(int k=0;k<n;k++) A[k][i]=(A[k][j]*z+A[k][i])%M;
            for(int k=i-1;k<n;k++) A[j][k]=(A[i][k]*w+A[j][k])%M;
        }
    }
}
vector<ll> charpoly(mat A) {
    hessenberg(A);
    int n=A.size();
    vector<vector<ll>> dp(n+1,vector<ll>(n+1));
    dp[0][0]=1;
    for(int i=0;i<n;i++) {
        ll x=1;
        for(int j=i;j>=0;j--) {
            ll y=(M-x*A[j][i]%M)%M;
            for(int k=0;k<=j;k++) dp[i+1][k]=(y*dp[j][k]+dp[i+1][k])%M;
            if(j) x=x*A[j][j-1]%M;
        } for(int k=0;k<=i;k++) dp[i+1][k+1]=(dp[i][k]+dp[i+1][k+1])%M;
    } return dp[n];
}
vector<ll> linear_det(mat A,mat B) {
    int n=A.size();
    ll det=1;
    auto rswap=[&](int i,int j) {
        if(i==j) return;
        swap(A[i],A[j]);
        swap(B[i],B[j]);
        det=(M-det)%M;
    }; auto cswap=[&](int i,int j) {
        if(i==j) return;
        for(int r=0;r<n;r++) {
            swap(A[r][i],A[r][j]);
            swap(B[r][i],B[r][j]);
        } det=(M-det)%M;
    }; auto radd=[&](int i,int j,ll c) {
        if(i==j) return;
        c%=M;
        if(c==0) return;
        for(int k=0;k<n;k++) {
            A[i][k]=(A[i][k]+c*A[j][k])%M;
            B[i][k]=(B[i][k]+c*B[j][k])%M;
        }
    }; auto cadd=[&](int i,int j,ll c) {
        if(i==j) return;
        c%=M;
        if(c==0) return;
        for(int r=0;r<n;r++) {
            A[r][i]=(A[r][i]+c*A[r][j])%M;
            B[r][i]=(B[r][i]+c*B[r][j])%M;
        }
    }; auto rmul=[&](int i,ll c) {
        c%=M;
        if(c==1) return;
        for(int k=0;k<n;k++) {
            A[i][k]=A[i][k]*c%M;
            B[i][k]=B[i][k]*c%M;
        } det=det*c%M;
    }; int a=0,b=0;
    while(a+b<n) {
        for(int i=0;i<a;i++) cadd(a,i,M-A[i][a]);
        for(int i=a;i<n-b;i++) {
            if(A[i][a]) {
                rswap(a,i);
                break;
            }
        } if(A[a][a]) {
            rmul(a,pw(A[a][a],M-2));
            for(int i=a+1;i<n;i++) radd(i,a,M-A[i][a]);
            a++;
        } else {
            int r=n-1-b;
            cswap(a,r);
            int p=-1;
            for(int i=r;i>=0;i--) if(B[i][r]) {p=i;break;}
            if(p==-1) return {};
            if(p<a) {
                rswap(p,a-1);
                cswap(p,a-1);
                rswap(a-1,r);
                a--;
            } else rswap(p,r);
            rmul(r,pw(B[r][r],M-2));
            for(int i=0;i<r;i++) radd(i,r,M-B[i][r]);
            b++;
        }
    } mat C(a,vector<ll>(a));
    for(int i=0;i<a;i++) for(int j=0;j<a;j++) C[i][j]=(M-B[i][j])%M;
    auto r=charpoly(C);
    det=pw(det,M-2);
    for(int i=0;i<=a;i++) r[i]=r[i]*det%M;
    return r;
}
int main() {
    int r,c,n,m,s;
    cin>>r>>c>>n>>m>>s;
    s--;
    int a[n],b[n],t[n],x[m],y[m];
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    for(int i=0;i<n;i++) cin>>t[i];
    for(int i=0;i<m;i++) cin>>x[i]>>y[i];
    auto f=[&](int sx,int sy) {
        vector<vector<int>> dp(r,vector<int>(c,0));
        dp[sx][sy]=1;
        if(sx%2) for(int j=1;j<c;j++) dp[sx][j]=(dp[sx][j]+dp[sx][j-1])%M;
        else for(int j=c-2;j>=0;j--) dp[sx][j]=(dp[sx][j]+dp[sx][j+1])%M;
        for(int i=sx+1;i<r;i++) {
            if(i!=s+1) for(int j=0;j<c;j++) dp[i][j]=dp[i-1][j];
            else {
                int z=0;
                for(int j=0;j<c;j++) {
                    if(z<n&&t[z]-1==j) {z++;continue;}
                    dp[i][j]=dp[i-1][j];
                }
            } if(i%2) for(int j=1;j<c;j++) dp[i][j]=(dp[i][j]+dp[i][j-1])%M;
            else for(int j=c-2;j>=0;j--) dp[i][j]=(dp[i][j]+dp[i][j+1])%M;
        } return dp;
	};
	auto g=[&](int sx,int sy) {
        vector<vector<int>> dp(r,vector<int>(c,0));
        if(sx>s) return dp;
        dp[sx][sy]=1;
        if(sx%2) for(int j=1;j<c;j++) dp[sx][j]=(dp[sx][j]+dp[sx][j-1])%M;
        else for(int j=c-2;j>=0;j--) dp[sx][j]=(dp[sx][j]+dp[sx][j+1])%M;
        for(int i=sx+1;i<r;i++) {
            if(i!=s+1) for(int j=0;j<c;j++) dp[i][j]=dp[i-1][j];
            else {
                int z=0;
                for(int j=0;j<c;j++) {
                    if(t[z]-1==j) {dp[i][j]=dp[i-1][j];z++;if(z==n) break;}
                }
            } if(i%2) for(int j=1;j<c;j++) dp[i][j]=(dp[i][j]+dp[i][j-1])%M;
            else for(int j=c-2;j>=0;j--) dp[i][j]=(dp[i][j]+dp[i][j+1])%M;
        } return dp;
	};
    vector<int> sx,sy,ex,ey;
    for(int i=0;i<n;i++) {
        sx.push_back(0);
        sy.push_back(a[i]-1);
        ex.push_back(r-1);
        ey.push_back(b[i]-1);
    } for(int i=0;i<m;i++) {
        sx.push_back(x[i]-1);
        sy.push_back(y[i]-1);
        ex.push_back(x[i]-1);
        ey.push_back(y[i]-1);
    } int k=sx.size();
    mat A(k,vector<ll>(k,0)),B(k,vector<ll>(k,0));
    for(int i=0;i<k;i++) {
        auto dp1=f(sx[i],sy[i]),dp2=g(sx[i],sy[i]);
        for(int j=0;j<k;j++) {
            B[i][j]=dp1[ex[j]][ey[j]];
            if(ex[j]>s) A[i][j]=dp2[ex[j]][ey[j]];
        }
    } auto p=linear_det(A,B);
    for(int i=0;i<=n;i++) {
        if(i>=p.size()) cout<<"0 ";
        else cout<<p[i]<<' ';
    }
}
