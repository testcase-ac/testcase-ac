#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
stack<int> ss[MAX];
vector<int> arr;

void solve() {
  int q, m;
  cin >> q >> m;

  int n = 0;
  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x;
      cin >> x;
      ss[x % m].push(arr.size());
      arr.push_back(x % m);
      n++;
    }
    if (op == 2) {
      if (!arr.size()) continue;
      ss[arr.back()].pop();
      arr.pop_back();
      n--;
    }
    if (op == 3) {
      bool able = true;
      int xvalue = 0;
      for (int i = 0; i < m; i++) {
        if (ss[i].empty()) {
          cout << "-1\n";
          able = false;
          break;
        }
        xvalue = max(xvalue, n - ss[i].top());
      }
      if (able) cout << xvalue << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
