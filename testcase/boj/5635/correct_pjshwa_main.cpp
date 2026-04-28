#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<pair<int, string>> v;
  for (int i = 0; i < n; i++) {
    string name;
    int d, m, y;
    cin >> name >> d >> m >> y;
    v.push_back({y * 1000 + m * 60 + d, name});
  }
  sort(v.begin(), v.end());

  cout << v.back().second << '\n';
  cout << v[0].second << '\n';
}
