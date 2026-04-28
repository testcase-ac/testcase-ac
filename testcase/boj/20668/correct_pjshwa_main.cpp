#include "iostream"
#include "vector"
#include "limits"
#include "queue"
#include "tuple"
#include "algorithm"
using namespace std;
typedef long long ll;
ll dist[10003][11];
const ll INF = 1e18;
vector<tuple<ll, ll, ll>> G[10003];
ll n, m;
void dij(ll s) {
    dist[s][1]=0;
    // 거리, 정점 번호, 속도
    priority_queue<tuple<ll, ll, ll>> pq;
    pq.push({0, s, 1});
    while (!pq.empty()) {
        auto cur = pq.top();pq.pop();
        ll cost = -get<0>(cur);
        ll now = get<1>(cur);
        ll speed = get<2>(cur);
        if (dist[now][speed]!=cost) continue;
        for (auto x:G[now]) {
            ll nxt = get<0>(x);
            ll limit = get<2>(x);
            for (ll d = -1; d <= 1; d++) {
                ll nxtSpeed = speed+d;
                if (nxtSpeed<=0) continue;
                if (nxtSpeed>10) continue;
                if (nxtSpeed>limit) continue;
                ll nxtCost = cost + (get<1>(x) * 2520) / nxtSpeed;
                if (nxtCost<dist[nxt][nxtSpeed]) {
                    dist[nxt][nxtSpeed] = nxtCost;
                    pq.push({-nxtCost, nxt, nxtSpeed});
                }
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 0; i < 10003; i++)
        for (ll j = 0; j < 11; j++)
            dist[i][j] = INF;
    for (ll i = 0; i < m; i++) {
        ll a,b,l,k;
        cin >> a >> b >> l >> k;
        G[a].push_back({b, l, k});
        G[b].push_back({a, l, k});
    }
    dij(1);
    long double ans = *min_element(dist[n], dist[n]+11);
    ans /= 2520;
    printf("%.9Lf\n", ans);
}
