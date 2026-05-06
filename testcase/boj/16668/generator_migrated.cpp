#include <bits/stdc++.h>
#define ll long long
using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device

ll mul(ll a,ll b,ll m) {
    long double x=(long double)a*b/m;
    ll c=(ll)(x);
    __int128 r=(__int128)a*b-(__int128)c*m;
    if(r<0) r+=m;
    else if(r>=(__int128)m) r-=m;
    return (ll)r;
}
ll pw(__int128 x,__int128 y,__int128 m) {
    x%=m;
    __int128 r=1;
    while(y) {
        if(y%2) r=mul(r,x,m);
        x=mul(x,x,m);
        y/=2;
    } return (ll)r;
}
bool chk(ll n,ll a) {
    if(a%n==0) return 1;
    ll k=n-1;
    while(1) {
        ll t=pw(a,k,n);
        if(t==n-1) return 1;
        if(k%2) return (t==1||t==n-1);
        k/=2;
    }
}
bool isprime(ll n) {
    if(n==2||n==3) return 1;
    if(n%2==0) return 0;
    ll a[]={2,3,5,7};
    for(int i=0;i<4;i++) if(!chk(n,a[i])) return 0;
    return 1;
}
int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> T(1,400);
    uniform_int_distribution<long long> p(100000000,1000000000);
    int t=T(g);
    ll P;
    while(1) {
        P=p(g);
        if(isprime(P)) break;
    } cout<<t<<' '<<P<<'\n';
    while(t--) cout<<T(g)<<'\n';
}
