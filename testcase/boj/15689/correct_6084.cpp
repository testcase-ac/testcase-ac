#include <bits/stdc++.h>
#define int long long
using namespace std;
struct move_p {
    int a;
    double p, prev_dp;
};
struct edge {
    int a, b, s, t;
    double p;
    void read() {
        cin >> a >> b >> s >> t >> p;
    }
};
map<int, vector<move_p>, greater<int>> moves;
double dp[1000000];
void apply_moves_after(int time) {
    while(moves.size() && moves.begin()->first > time) {
        auto &v = moves.begin()->second;
        map<int, double> nxt_dp;
        for(auto [a, p, prev_dp]: v) {
            double on_try = p * prev_dp + (1 - p) * dp[a];
            nxt_dp[a] = max(nxt_dp[a], on_try);
        }
        for(auto [a, p]: nxt_dp) {
            dp[a] = max(dp[a], p);
        }
        moves.erase(moves.begin());
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N, K;
    cin >> M >> N >> K;
    vector<edge> edges(M);
    for(auto &e: edges) {
        e.read();
    }
    sort(edges.begin(), edges.end(), [](edge a, edge b) {
        return a.t > b.t;
    });
    dp[1] = 1;
    for(auto &[a, b, s, t, p]: edges) {
        if(t > K) {
            continue;
        }

        apply_moves_after(t);
        moves[s].push_back({a, p, dp[b]});
    }

    apply_moves_after(-1);
    cout << fixed << setprecision(6) << dp[0];
}
