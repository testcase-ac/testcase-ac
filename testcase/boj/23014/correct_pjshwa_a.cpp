#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
using ll=long long;
std::ostream& operator<<( std::ostream& dest, __int128_t value ){
    std::ostream::sentry s( dest );
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do{
            --d;*d = "0123456789"[ tmp % 10 ];tmp /= 10;
        }while ( tmp != 0 );
        if ( value < 0 ) {
            --d;*d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
struct node{
    int m,p,c,e;/////s*m+p+v(s)*c+e
}tree[1048673];
node operator+(const node& a,const node& b){
    return {a.m+b.m,a.p+b.p,a.c+b.c,a.e+b.e};
}node arr[500'010];
int getC(ll a,ll b){
    if(a==0)return 0;
    int cnt=0;
    while(a%b==0){
        cnt++;
        a/=b;
    }return cnt;
}
node gets(ll a,ll p){
    ll k=a%p;
    if(k==0)return {getC(a,p),0,0,0};
    if(a==k)return {0,0,0,0};
    return {0,getC(a-k,p),1,getC(a+k,p)-1};
}
node init(int n,int s,int e){
    if(s==e){
        return tree[n]=arr[s];
    }int mid=s+e>>1;
    return tree[n]=init(n<<1,s,mid)+init(n<<1|1,mid+1,e);
}
void update(int n,int s,int e,int t,node p){
    if(e<t||t<s)return;
    if(s==e){
        tree[n]=p;
        return;
    }int mid=s+e>>1;
    update(n<<1,s,mid,t,p);
    update(n<<1|1,mid+1,e,t,p);
    tree[n]=tree[n<<1]+tree[n<<1|1];
}
node query(int n,int s,int e,int l,int r){
    if(e<l||r<s)return {0,0,0,0};
    if(l<=s&&e<=r)return tree[n];
    int mid=s+e>>1;
    return query(n<<1,s,mid,l,r)+query(n<<1|1,mid+1,e,l,r);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc;
    cin>>tc;
    for(int t=1;t<=tc;t++){
        int n,q,p;
        cout<<"Case #"<<t<<":";
        ll a,b,c,d;
        cin>>n>>q>>p;
        for(int i=1;i<=n;i++){
            cin>>a,arr[i]=gets(a,p);
        }init(1,1,n);
        while(q--){
            cin>>a>>b>>c;
            if(a==1){
                update(1,1,n,b,gets(c,p));
            }else{
                cin>>d;
                node tmp=query(1,1,n,c,d);
                /////s*m+p+v(s)*c+e
                cout<<' ';
                if(p==2&&(~b&1))cout<<b*tmp.m+tmp.p+getC(b,p)*tmp.c+tmp.e;
                else cout<<b*tmp.m+tmp.p+getC(b,p)*tmp.c;
            }
        }cout<<'\n';
    }
}
