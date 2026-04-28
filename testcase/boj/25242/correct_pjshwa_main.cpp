#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
const ll INF = 1e18;
map<string, int> fi;
int fcount;
vector<int> graph[MAX];
ll cdist[20][MAX];
map<int, int> pos[MAX];
int inv[MAX];

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

void solve() {
  int n, q;
  cin >> n >> q;

  int b = 0;
  vector<int> transfers;

  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    vector<string> v(m);
    for (int j = 0; j < m; j++) {
      cin >> v[j];
      if (fi.count(v[j])) transfers.push_back(fidx(v[j]));
      pos[i][fidx(v[j])] = j;
      inv[fidx(v[j])] = i;
    }
    for (int j = 0; j < m - 1; j++) {
      int x = fidx(v[j]), y = fidx(v[j + 1]);
      graph[x].push_back(y);
      graph[y].push_back(x);
    }
  }

  compress(transfers);
  int z = transfers.size();

  for (int i = 0; i < z; i++) {
    int s = transfers[i];

    fill(cdist[i], cdist[i] + MAX + 1, INF);
    cdist[i][s] = 0;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
      auto [wi, ui] = pq.top();
      pq.pop();

      if (wi > cdist[i][ui]) continue;

      for (auto &vi : graph[ui]) {
        if (cdist[i][vi] > wi + 1) {
          cdist[i][vi] = wi + 1;
          pq.push({cdist[i][vi], vi});
        }
      }
    }
  }

  while (q--) {
    string xs, ys;
    cin >> xs >> ys;
    int x = fidx(xs), y = fidx(ys);

    ll res = INF;
    if (inv[x] == inv[y]) res = min(res, (ll)abs(pos[inv[x]][x] - pos[inv[x]][y]));

    for (int i = 0; i < z; i++) {
      if (cdist[i][x] == INF || cdist[i][y] == INF) continue;
      res = min(res, cdist[i][x] + cdist[i][y]);
    }

    if (res == INF) cout << "-1\n";
    else cout << res * 2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
