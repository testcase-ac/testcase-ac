#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, c;
  cin >> n >> m >> c;
  if (n < m) return cout << "NONE\n", 0;

  priority_queue<pii> qx;
  priority_queue<pii, vector<pii>, greater<pii>> qm;

  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    qx.push({x, i});
    qm.push({x, i});
  }

  vector<int> ans;
  if (qx.top().first - qm.top().first <= c) ans.push_back(1);

  for (int i = m; i < n; i++) {
    while (!qx.empty() && qx.top().second <= i - m) qx.pop();
    while (!qm.empty() && qm.top().second <= i - m) qm.pop();

    int x;
    cin >> x;
    qx.push({x, i});
    qm.push({x, i});

    if (qx.top().first - qm.top().first <= c) ans.push_back(i - m + 2);
  }

  if (ans.size()) for (auto i : ans) cout << i << '\n';
  else cout << "NONE\n";
}
