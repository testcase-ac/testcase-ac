#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m;
int a[8];
vector<int> current;
set<string> s;

void dfs() {
  if (current.size() == m) {
    string item = "";
    for (int i = 0; i < m; i++) item += (to_string(current[i]) + ' ');
    if (s.find(item) == s.end()) {
      cout << item << '\n';
      s.insert(item);
    }
    return;
  }

  for (int i = 0; i < n; i++) {
    if (current.size() && current.back() > a[i]) continue;

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
