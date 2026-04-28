#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
vector<pii> a[MAX], w[MAX];

void solve() {
  int n, b;
  cin >> n >> b;
  for (int i = 0; i < n; i++) {
    a[i].clear();
    w[i].clear();
  }

  int x = 0;
  map<string, int> s2x;
  for (int i = 0; i < n; i++) {
    string type, name; int price, qual;
    cin >> type >> name >> price >> qual;

    if (!s2x.count(type)) s2x[type] = x++;
    a[s2x[type]].push_back({qual, price});
  }
  for (int i = 0; i < x; i++) {
    sort(a[i].begin(), a[i].end());

    for (auto [q, p] : a[i]) {
      while (w[i].size() && w[i].back().second >= p) w[i].pop_back();
      w[i].push_back({q, p});
    }
  }

  int left = 0, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    ll cb = 0;

    bool able = true;
    for (int i = 0; i < x; i++) {
      auto it = lower_bound(w[i].begin(), w[i].end(), pii(mid, 0));
      if (it == w[i].end()) {
        able = false;
        break;
      }
      cb += it->second;
    }
    able &= cb <= b;

    if (able) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
