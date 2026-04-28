#include <bits/stdc++.h>
using namespace std;
using T = string;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  deque<string> dq = {"WELCOME", "TO", "CCC", "GOOD", "LUCK", "TODAY"};
  int N; cin >> N;
  while (!dq.empty()) {
    int sz = -1;
    vector<string> line;
    while (!dq.empty() && sz + dq.front().size() + 1 <= N) {
      sz += dq.front().size() + 1;
      line.push_back(dq.front());
      dq.pop_front();
    }

    int wcnt = 0;
    for (auto& s : line) wcnt += s.size();
    int scnt = N - wcnt, Z = line.size();
    if (Z == 1) {
      cout << line[0];
      for (int i = 0; i < scnt; ++i) cout << '.';
    } else {
      int q = scnt / (Z - 1), r = scnt % (Z - 1);
      for (int i = 0; i < Z; ++i) {
        cout << line[i];
        if (i + 1 < Z) {
          for (int j = 0; j < q; ++j) cout << '.';
          if (r > 0) cout << '.', --r;
        }
      }
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
