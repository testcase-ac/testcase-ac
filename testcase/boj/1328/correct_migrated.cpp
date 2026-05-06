#include <iostream>
#define f(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
typedef long long ll;
const int MOD=1000000007;
int n,l,r,s[101][101][101];

int main(){
    cin>>n>>l>>r;
    s[1][1][1]=1;
    f(i,2,n)f(j,1,l)f(k,1,r)
        s[i][j][k]=((ll)s[i-1][j][k]*(i-2)+s[i-1][j][k-1]+s[i-1][j-1][k])%MOD;
    cout<<s[n][l][r];
    return 0;
}
