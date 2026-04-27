#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

vector<pll> V;
ll S0[200009], S1[200009];

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(0);
    
    int N, Q;
    cin >> N >> Q;
    for(int i=1; i<=N; i++) {
        ll a, x;
        cin >> a >> x;
        V.push_back({x, a});
    }
    sort(V.begin(), V.end());
    for(int i=1; i<=N; i++) {
        ll a, x;
        tie(x, a) = V[i-1];
        S0[i] = S0[i-1] + a;
        S1[i] = S1[i-1] + a * x;
    }
    while(Q--) {
        ll q;
        cin >> q;
        int p = lower_bound(V.begin(), V.end(), pll(q, -1)) - V.begin();
        cout << S1[N] - S0[N] * q - 2LL * (S1[p] - S0[p] * q) << "\n";
    }
    return 0;
}
