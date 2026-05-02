#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<ll, ll>;

ll A[36]{}, B[36]{};
ll N;

vector<vector<ii>> res1(19), res2(19);

bool cmp(ii a, ii b) {
    if (a.first == b.first) {
        for (int i = 0; i < N; i++) {
            bool ta = (a.second & (1LL << i));
            bool tb = (b.second & (1LL << i));
            if (ta == tb)  continue;
            return ta < tb;
        }
    }
    return a.first < b.first;
}

void push(ll pos, ll limit, ll visit, ll sum, ll sel, bool fir) {
    if (pos >= limit) {
        if (fir) res1[sel].push_back({ sum, visit });
        else    res2[sel].push_back({ sum, visit });
        return;
    }
    push(pos + 1, limit, visit, sum, sel, fir);
    visit |= (1LL << pos);
    push(pos + 1, limit, visit, sum + A[pos] + B[pos], sel + 1, fir);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i = 0; i < N; i++)    cin >> A[i];
    for (int i = 0; i < N; i++)    cin >> B[i];

    ll S = 0;
    for (ll i = 0; i < N; i++)    S += A[i];

    push(0, N / 2, 0LL, 0LL, 0, 1);
    push(N / 2, N, 0LL, 0LL, 0, 0);

    vector<vector<ll>> val(19), vis(19);
    for (int i = 0; i <= N / 2; i++) {
        sort(res2[i].begin(), res2[i].end(), cmp);
        for (ii j : res2[i])   val[i].push_back(j.first), vis[i].push_back(j.second);
    }

    ll mn = 1e18;
    ll ans = (1LL << 36) - 1;
    for (ll i = 0; i <= N / 2; i++) {
        for (ii j : res1[i]) {
            ll chk = S - j.first;
            ll V1 = j.second;

            ll p = N / 2 - i;

            ll p1 = lower_bound(val[p].begin(), val[p].end(), chk) - val[p].begin();
            if (p1 == val[p].size()) p1--;
            if (abs(chk - val[p][p1]) < mn) {
                mn = abs(chk - val[p][p1]);
                ans = (V1 | vis[p][p1]);
            }
            else if (abs(chk - val[p][p1]) == mn){
                ll temp = (V1 | vis[p][p1]);
                for (int k = 0; k < N; k++) {
                    bool ta = (ans & (1LL << k));
                    bool tb = (temp & (1LL << k));
                    if (ta == tb)    continue;
                    if (tb < ta) ans = temp;
                    break;
                }
            }
            if (p1) {
                int p2 = p1 - 1;
                p1 = lower_bound(val[p].begin(), val[p].end(), val[p][p2]) - val[p].begin();
                if (abs(chk - val[p][p1]) < mn) {
                    mn = abs(chk - val[p][p1]);
                    ans = (V1 | vis[p][p1]);
                }
                else if (abs(chk - val[p][p1]) == mn) {
                    ll temp = (V1 | vis[p][p1]);
                    for (int k = 0; k < N; k++) {
                        bool ta = (ans & (1LL << k));
                        bool tb = (temp & (1LL << k));
                        if (ta == tb)    continue;
                        if (tb < ta) ans = temp;
                        break;
                    }
                }
            }

        }
    }

    for (int i = 0; i < N; i++)    cout << ((ans & (1LL << i)) ? 2 : 1) << ' ';


}
