#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, K, P;
  cin >> N >> K >> P;

  set<string> load[N];
  while (P--) {
    string o;
    cin >> o;

    vector<int> candidates;
    int mcnt = INF;
    for (int i = 0; i < N; i++) {
      if (load[i].size() == K) continue;

      int cnt = 0;
      for (string y : load[i]) {
        if (y[0] == o[0]) cnt++;
      }
      mcnt = min(mcnt, cnt);
    }

    for (int i = 0; i < N; i++) {
      if (load[i].size() == K) continue;

      int cnt = 0;
      for (string y : load[i]) {
        if (y[0] == o[0]) cnt++;
      }
      if (cnt == mcnt) candidates.push_back(i);
    }

    mcnt = INF;
    for (int i : candidates) mcnt = min(mcnt, (int)load[i].size());

    vector<int> candidates_t;
    for (int i : candidates) {
      if (load[i].size() == mcnt) candidates_t.push_back(i);
    }
    load[candidates_t[0]].insert(o);
  }

  for (int i = 0; i < N; i++) cout << load[i].size() << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
