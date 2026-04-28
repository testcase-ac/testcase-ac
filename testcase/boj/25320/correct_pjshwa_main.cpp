#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
bool vis[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  vector<pii> R(M);
  for (int i = 0; i < M; ++i) {
    string p;
    cin >> p;
    R[i].first = p == "B";

    cin >> p >> R[i].second;
    vis[R[i].second] = true;
  }
  if (!vis[1]) return cout << "NO\n", void();

  set<int> avail;
  for (int i = 1; i <= 2 * N; i++) {
    if (!vis[i]) avail.insert(i);
  }

  int lplay = 1, lblk = -1;
  vector<tii> moves;
  for (int i = 0; i < M; i++) {
    auto& [cplay, cblk] = R[i];
    if (lplay == cplay) {
      auto it = avail.upper_bound(lblk);
      if (it == avail.end()) {
        cout << "NO\n";
        return;
      }

      int t = *it;
      moves.push_back({1 - cplay, 1, t});
      avail.erase(it);
    }

    moves.push_back({cplay, 0, cblk});
    tie(lplay, lblk) = R[i];
  }

  if (lplay == 0) {
    auto it = avail.upper_bound(lblk);
    if (it == avail.end()) {
      cout << "NO\n";
      return;
    }

    int t = *it;
    moves.push_back({1, 1, t});
    avail.erase(it);
  }

  cout << "YES\n";
  bool flag = false;
  for (auto& [p, t, k] : moves) {
    if (flag && t == 0) {
      while (!avail.empty()) {
        int s1 = *avail.begin();
        avail.erase(avail.begin());
        int s2 = *avail.begin();
        avail.erase(avail.begin());

        if (p == 0) {
          cout << "A CHAIN " << s1 << '\n';
          cout << "B CHAIN " << s2 << '\n';
        }
        else {
          cout << "B CHAIN " << s1 << '\n';
          cout << "A CHAIN " << s2 << '\n';
        }
      }
      flag = false;
    }

    if (p == 0) cout << "A ";
    else cout << "B ";

    if (t == 0) cout << "BLOCK ";
    else cout << "CHAIN ";

    cout << k << '\n';
    if (k == 1) flag = true;
  }

  if (flag) {
    while (!avail.empty()) {
      int s1 = *avail.begin();
      avail.erase(avail.begin());
      int s2 = *avail.begin();
      avail.erase(avail.begin());

      cout << "A CHAIN " << s1 << '\n';
      cout << "B CHAIN " << s2 << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
