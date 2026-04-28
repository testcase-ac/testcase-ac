#include <bits/stdc++.h>
#define va first
#define vb second
#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define pp push_back
#define ep emplace_back
#define all(v) (v).begin(),(v).end()
#define szz(v) ((int)(v).size())
#define bi_pc __builtin_popcount
#define bi_pcll __builtin_popcountll
#define bi_tz __builtin_ctz
#define bi_tzll __builtin_ctzll
#define fio ios_base::sync_with_stdio(0);cin.tie(0);
#ifdef TAMREF
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) 42
#endif
using namespace std;
using ll = long long; using lf = long double; 
using pii = pair<int,int>; using ppi = pair<int,pii>;
using pll = pair<ll,ll>; using pff = pair<lf,lf>;
using ti = tuple<int,int,int>;
using base = complex<double>;
const lf PI = 3.14159265358979323846264338L;
template <typename T>
inline T umax(T& u, T v){return u = max(u, v);}
template <typename T>
inline T umin(T& u, T v){return u = min(u, v);}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int a[1050000];
int n;

int main(){
    fio;
    cin >> n;
    for(int i = 0; i < (1 << n); i++) cin >> a[i];
    int msk = (1 << n) - 1;
    for(int b = 0; b <= msk; b++) {
        for(int c = (msk ^ b); c; c &= c-1) {
            for(int d = (c & c-1); d; d &= d-1) {
                if(a[b | (c & -c)] + a[b | (d & -d)] < a[b | (c & -c) | (d & -d)] + a[b]) {
                    cout << (b | (c & -c)) << ' ' << (b | (d & -d)) << '\n';
                    return 0;
                }
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}
