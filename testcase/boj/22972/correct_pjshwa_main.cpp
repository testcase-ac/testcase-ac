#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

multiset<int> ds, cs;
int n;

void dfs() {
  if (cs.size() == n) {
    for (int c : cs) cout << c << ' ';
    exit(0);
  }

  int c1 = *ds.rbegin(), c2 = *cs.rbegin() - *ds.rbegin();
  for (int nc : {c1, c2}){
    bool able = true;
    auto v = ds;
    for (int c : cs) {
      auto it = v.find(abs(nc - c));
      if (it == v.end()) {
        able = false;
        break;
      }
      else v.erase(it);
    }

    if (able) {
      swap(v, ds);
      cs.insert(nc);
      dfs();
      cs.erase(nc);
      swap(v, ds);
    }
  }

}

int main() {
  fast_io();

  int d;
  cin >> n;
  for (int i = 0; i < n * (n - 1) / 2; i++) {
    cin >> d;
    ds.insert(d);
  }
  cs.insert(0);
  dfs();
}
