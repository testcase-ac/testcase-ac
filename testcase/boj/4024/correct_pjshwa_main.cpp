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

const int MAXN = 8, THRESHOLD = 1e5;
vector<tuple<int, ll, ll>> adj[MAXN];

void init() {
  fi.clear(); fcount = 0;
  for (int i = 0; i < MAXN; ++i) adj[i].clear();
}

int M, tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  init();
  while (M--) {
    int r1, r2; string c1_s, c2_s, op;
    cin >> r1 >> c1_s >> op >> r2 >> c2_s;
    int c1 = fidx(c1_s), c2 = fidx(c2_s);
    adj[c1].emplace_back(c2, r2, r1);
    adj[c2].emplace_back(c1, r1, r2);
  }

  int rq; string cq_s; cin >> rq >> cq_s;
  int cq = fidx(cq_s), N = fcount;

  pair<ll, ll> cdist[N];
  fill(cdist, cdist + N, make_pair(-1, -1));
  queue<int> Q; Q.push(cq); cdist[cq] = {1, 1};

  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    auto [ni, di] = cdist[u];
    for (auto& [v, rn, rd] : adj[u]) {
      ll rnj = rn * ni, rdj = rd * di; ll g = gcd(rnj, rdj);
      rnj /= g, rdj /= g;

      auto& [nj, dj] = cdist[v];
      if (nj == -1) {
        nj = rnj, dj = rdj;
        Q.push(v);
      }
    }
  }

  __int128_t na = -1, da; ll req_a; string name_a;
  for (auto& [name, idx] : fi) {
    auto [nj, dj] = cdist[idx];
    if (nj == -1 || idx == cq) continue;

    ll req = (rq * nj - 1) / dj + 1;
    if (req > THRESHOLD) continue;

    ll nd = req * dj - rq * nj, dd = nj;
    assert(nd >= 0 && dd > 0);

    if (na == -1 || na * dd > nd * da) {
      na = nd, da = dd;
      req_a = req, name_a = name;
    }
  }

  cout << req_a << ' ' << name_a << '\n';
}

int main() {
  fast_io();

  while (cin >> M) {
    if (M == 0) break;
    solve();
  }
}
