#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[7], n, m;
vector<int> current;
set<string> used;

void dfs() {
  if (current.size() == m) {
    string r = "";
    for (int c : current) r = r + to_string(c) + ' ';
    if (!used.count(r)) {
      used.insert(r);
      cout << r << '\n';
    }
    return;
  }

  for (int i = 0; i < n; i++) {
    current.push_back(a[i]);
    dfs();
    current.pop_back();
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  dfs();
}
