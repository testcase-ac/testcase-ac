#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 100;
string v[MAX];
bool vis[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> v[i];

  vector<string> left, right, self;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    if (vis[i] || vis[j]) continue;
    string u = v[i];
    reverse(u.begin(), u.end());
    if (u == v[j]) {
      vis[i] = vis[j] = true;
      left.push_back(v[i]);
      right.push_back(v[j]);
    }
  }
  reverse(right.begin(), right.end());

  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;

    string u = v[i];
    reverse(u.begin(), u.end());
    if (u == v[i]) {
      vis[i] = true;
      self.push_back(u);
    }
  }

  int total = left.size() * 2;
  if (self.size()) total++;

  cout << m * total << '\n';
  for (auto& e : left) cout << e;
  if (self.size()) cout << self[0];
  for (auto& e : right) cout << e;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
