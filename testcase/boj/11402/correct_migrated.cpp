#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

ll mtx[2001][2001];
int m;

vector<int> getLuca(ll v, int m) {
    vector<int> r;
    while (v > 0) {
        int rem = v % m;
        r.push_back(rem);
        v /= m;
    }
    return r;
}

ll comb(int n, int r) {
    if (n < r) return 0;
    if (n / 2 < r) r = n - r;

    ll &res = mtx[n][r];
    if (res != -1) return res;

    if (r == 0) return res = 1;
    else if (r == 1) return res = n;

    return res = (comb(n - 1, r - 1) + comb(n - 1, r)) % m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(mtx, -1, sizeof(mtx));

    ll n, k, res = 1;

    cin >> n >> k >> m;

    vector<int> ln, lk;
    ln = getLuca(n, m);
    lk = getLuca(k, m);

    int minIdx = min(ln.size(), lk.size());
    for (int i = 0; i < minIdx; ++i) {
        int n = ln[i];
        int r = lk[i];

        res = res * comb(n, r);
        res %= m;
    }
    cout << res << "\n";
    return 0;
}
