#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, ll> pii;
unordered_map<int, int> lm, rm;

int gcd(int a, int b){
    return (b != 0 ? gcd(b, a % b) : a);
}

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int N, L, R; cin >> N >> L >> R;
    const int GCD = gcd(2 * L, 2 * R);
    ll sum = 0;
    for(int i = 0; i < N; i++){
        int x, d, w; cin >> x >> d >> w;
        if(x > 0){
            if(d == -1) rm[x] += w;
            else rm[R - x + R + 1] += w;
            sum += w;
        }else{
            x = abs(x);
            if(d == 1) lm[x] += w;
            else lm[L - x + L + 1] += w;
        }
    }
    vector<pii> l, r;
    for(auto iter = lm.begin(); iter != lm.end(); iter++) l.push_back({iter->first % GCD, iter->second});
    for(auto iter = rm.begin(); iter != rm.end(); iter++) r.push_back({iter->first % GCD, iter->second});

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int pl = 0, pr = 0;
    while(pl < l.size() && pr < r.size()){
        while(pl < l.size() && l[pl].first < r[pr].first){
            sum += l[pl].second;
            pl++;
        }
        ll l_val = 0, r_val = r[pr].second;
        while(pr < r.size() - 1 && r[pr].first == r[pr + 1].first){
            r_val = min(r_val, r[pr + 1].second);
            pr++;
        }
        while(pl < l.size() && l[pl].first == r[pr].first){
            l_val = max(l_val, l[pl].second);
            pl++;
        }
        if(l_val > r_val) sum += l_val - r_val;
        pr++;
    }
    while(pl < l.size()){
        sum += l[pl].second;
        pl++;
    }
    cout << sum;

    return 0;
}

