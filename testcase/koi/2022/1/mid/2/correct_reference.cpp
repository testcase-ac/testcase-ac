#include <iostream>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define ends " "
#define fio()                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0)
using namespace std;

typedef long long ll;

ll cal(vector<ll> pt, vector<ll> l) {
    l.push_back(-1e9);
    l.push_back(1e9);
    sort(all(pt)); sort(all(l));

    int cnt = 0;
    ll ret = 0;

    auto f = [](vector<ll> &v, int st, int en) {
        if (st > en) return 0LL;
        return v[en] - (st != 0 ? v[st - 1] : 0);
    };

    for (int i = 1; i < l.size(); i++) {
        vector<ll> t;
        ll le = l[i - 1], ri = l[i];
        while (cnt < pt.size() && pt[cnt] <= ri)
            t.push_back(pt[cnt++]);

        int n = t.size();
        if (!n) continue;
        vector<ll> ps(n);
        ps[0] = t[0];
        for (int j = 1; j < n; j++)
            ps[j] = ps[j - 1] + t[j];

        for (int j = 1; j < n; j++) {
            int pos = upper_bound(all(t), min(t[j], le + ri - t[j])) - t.begin() - 1; // 마지막 left 
            pos = min(pos, j - 1);
            if (pos >= 0) ret += (f(ps, 0, pos) - le * (pos + 1)) * 2;
            ret += 2 * (j - pos - 1) * (ri - t[j]);
        }
    }

    ll s = 0;
    for (int i = 0; i < pt.size(); i++) {
        ret += pt[i] * i - s;
        s += pt[i];
    }

    return ret;
}

int main() {
    fio();

    int n, m, k;
    cin >> n >> m >> k;
    
    vector<ll> lx(n), ly(m);
    for (int i = 0; i < n; i++)
        cin >> lx[i];
    for (int i = 0; i < m; i++)
        cin >> ly[i];

    vector<ll> x(k), y(k);
    for (int i = 0; i < k; i++)
        cin >> x[i] >> y[i];

    ll ans = 0;
    ans += cal(x, lx);
    ans += cal(y, ly);

    cout << ans;

    return 0;
}