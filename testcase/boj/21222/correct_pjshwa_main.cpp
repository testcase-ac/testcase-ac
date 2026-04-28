#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

const int MAXN = 1000;
vector<pii> adj[MAXN + 1];
ll cdist[MAXN + 1], N;

void dijk(int s) {
  fill(cdist, cdist + N, LLONG_MAX);

  using T = pair<ll, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  cdist[s] = 0; pq.push({0, s});

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (cdist[u] < d) continue;

    for (auto [v, w] : adj[u]) {
      if (cdist[v] > cdist[u] + w) {
        cdist[v] = cdist[u] + w;
        pq.push({cdist[v], v});
      }
    }
  }
}

void solve() {
  int M; cin >> N >> M;
  for (int i = 0; i < M; i++) {
    string S, T; int w; cin >> S >> T >> w;
    int s = fidx(S), t = fidx(T);
    adj[s].push_back({t, w});
  }
  assert(fcount == N);

  int Q; cin >> Q;
  while (Q--) {
    string S, T; cin >> S >> T;
    dijk(fidx(S));

    ll ans = cdist[fidx(T)];
    if (ans == LLONG_MAX) cout << "Roger\n";
    else cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
