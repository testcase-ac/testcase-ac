#include <cstdio>
typedef long long ll;
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
ll n,m,a[30][55];
ll amel(ll p){
    ll ret=0;
    for(int i=n-1,zero=0,cnt=n>>1;i>=0;i--){
        if(!(p&1ll<<i)) {zero++; continue;}
        if(!i) return ret+(zero==1);
        if(!zero) return ret+a[cnt][i-1];
        ret+=a[cnt][i-1];
        zero--; cnt--;
    }
    return ret;
}
ll sol(){
    if(n%2) return m;
    a[1][0]=a[1][1]=1;
    for(int i=2;i<=n>>1;i++){
        for(int j=i-1;j+1<i<<1;j++)
            a[i][j]=a[i][j-1]+a[i-1][j-1];
        a[i][(i<<1)-1]=a[i][(i<<1)-2];
    }
    if(m>=(1ll<<n)-a[n>>1][n-1]) return -1;
    ll p=0,ret=amel(m);
    while(amel(m+ret)!=ret) ret=amel(m+ret);
    return m+ret;
}
int main(){
    scanf("%lld %lld",&n,&m);
    ll ans=sol();
    if(ans<0) printf("-1");
    else
        for(int i=n-1;i>=0;i--) printf(ans&1ll<<i?")":"(");
    return 0;
}
