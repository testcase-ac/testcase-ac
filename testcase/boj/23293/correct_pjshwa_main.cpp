#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int area_by_player[MAX + 1];
unordered_map<int, int> items_by_player[MAX + 1];

set<int> fraud, ban;

int main() {
  fast_io();

  int t, n;
  cin >> t >> n;
  for (int i = 1; i <= n; i++) area_by_player[i] = 1;

  for (int i = 1; i <= t; i++) {
    int l, p, a1, a2;
    string op;
    cin >> l >> p >> op;
    if (op == "M") {
      cin >> a1;
      area_by_player[p] = a1;
    }
    if (op == "F") {
      cin >> a1;
      if (area_by_player[p] != a1) fraud.insert(l);
      items_by_player[p][a1]++;
    }
    if (op == "C") {
      cin >> a1 >> a2;
      if (!(items_by_player[p][a1] && items_by_player[p][a2])) fraud.insert(l);
      if (items_by_player[p][a1]) items_by_player[p][a1]--;
      if (items_by_player[p][a2]) items_by_player[p][a2]--;
    }
    if (op == "A") {
      cin >> a1;
      if (area_by_player[p] != area_by_player[a1]) {
        fraud.insert(l);
        ban.insert(p);
      }
    }
  }

  cout << fraud.size() << '\n';
  if (fraud.size()) {
    for (auto i : fraud) cout << i << ' ';
    cout << '\n';
  }
  cout << ban.size() << '\n';
  if (ban.size()) {
    for (auto i : ban) cout << i << ' ';
    cout << '\n';
  }
}
