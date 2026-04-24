#include <bits/stdc++.h>
using namespace std;
#define int long long
struct cow {
    int p, c, i;
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K, M;
    cin >> N >> K >> M;
    auto cmp_c = [&](const cow &a, const cow &b) { return a.c > b.c; };
    auto cmp_p = [&](const cow &a, const cow &b) { return a.p > b.p; };
    auto cmp_diff = [&](const cow &a, const cow &b) { return a.p - a.c > b.p - b.c; };
    priority_queue<cow, vector<cow>, decltype(cmp_c)> pq_c(cmp_c);
    priority_queue<cow, vector<cow>, decltype(cmp_p)> pq_p(cmp_p);
    priority_queue<cow, vector<cow>, decltype(cmp_diff)> pq_diff(cmp_diff);
    vector<cow> cows(N);
    vector<bool> used(N);
    for(int i = 0; i < N; i++) {
        cin >> cows[i].p >> cows[i].c;
        cows[i].i = i + 1;
        pq_c.push(cows[i]);
        pq_p.push(cows[i]);
    }
    int ans = 0, sum = 0;
    auto add_to_sum = [&](int x) {
        if(sum + x > M) {
            cout << ans << '\n';
            exit(0);
        }
        sum += x;
        ans++;
    };

    for(int i = 0; i < K; i++) {
        cow c = pq_c.top();
        pq_c.pop();
        add_to_sum(c.c);
        used[c.i] = true;
        pq_diff.push(c);
    }
    while(ans < N) {
        while(used[pq_c.top().i]) {
            pq_c.pop();
        }
        while(used[pq_p.top().i]) {
            pq_p.pop();
        }
        int add_without_cpn = pq_p.top().p;
        int exchange_cpn = pq_c.top().c + pq_diff.top().p - pq_diff.top().c;
        if(add_without_cpn < exchange_cpn) {
            used[pq_p.top().i] = true;
            add_to_sum(add_without_cpn);
        } else {
            used[pq_c.top().i] = true;
            pq_diff.pop();
            pq_diff.push(pq_c.top());
            add_to_sum(exchange_cpn);
        }
    }
    cout << ans;
}
