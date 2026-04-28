#include <bits/stdc++.h>
#define f first
#define s second
#define MOD 1000000007
#define PMOD 998244353
#define pb(x) push_back(x)
using namespace std;

typedef long long int ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> plii;
typedef pair<int, pii> piii;
const int INF = 1e9+10;
const ll LINF = 1LL*INF*INF;
const int MAXN = 2e5+10;
const int MAXM = 5e3+10;

priority_queue<int> pq;
vector<vector<int> > graph;
queue<int> que;

int dp[1010][30];

int getphi(int n)
{
    int res = n;

    for(int i=2;i*i<=n;i++){
        if(n%i)continue;

        res/=i;
        res*=(i-1);

        while(!(n%i)){
            n/=i;
        }
    }

    if(n>1){
        res/=n;
        res*=(n-1);
    }

    return res;
}


int main()
{
    int n,m,k,a,b,x,y,q;
    int sum = 0;
    int cnt = 0;
    int mx = 0;
    int mn = INF;
    int cur = 0, idx = -1;
    int curv;
    int vv;
    int tc;
    int gv,cv;
    int gg;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>tc;

    for(int runs=1;runs<=tc;runs++){

        cin>>a>>b>>k;

        vector<int> vv;

        while(k>1){
            vv.push_back(k);
            k = getphi(k);
        }

        vv.push_back(1);

        reverse(vv.begin(),vv.end());

        n = (int)vv.size();

        for(int i=0;i<n;i++){
            dp[0][i] = a%vv[i];
        }

        for(int i=1;i<=b;i++){
            dp[i][0] = 0;

            for(int j=1;j<n;j++){
                x = dp[i-1][j];

                if(x<=1){
                    dp[i][j] = x;
                    continue;
                }

                cur = 1;
                curv = vv[j];

                if(a<=10&&i==1){
                    for(int t=0;t<a;t++){
                        cur*=a;
                        cur%=curv;
                    }

                    dp[i][j] = cur;
                }
                else if(a==2&&i==2){
                    dp[i][j] = 256%vv[j];
                }
                else {

                    y = dp[i-1][j-1]+10*vv[j-1];

                    while(y){
                        if(y&1){
                            cur*=x;
                            cur%=curv;
                        }
                        x*=x;
                        x%=curv;
                        y>>=1;
                    }

                    dp[i][j] = cur;
                }
            }
        }

        cout<<"Case #"<<runs<<": "<<dp[b][n-1]<<"\n";
    }

    return 0;
}
