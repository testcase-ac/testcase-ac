#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
int a[MAX];

bool is_arith(multiset<int>& s) {
  if (s.size() <= 2) return true;
  int o = *s.begin(), d = *next(s.begin()) - o;

  bool f = true;
  for (int x : s) {
    if (f) {
      f = false;
      continue;
    }
    if (x - o != d) return false;
    o = x;
  }

  return true;
}

void solve() {
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> a[i];
  sort(a, a + N);

  int d = a[1] - a[0];
  if (d == 0) return cout << "No\n", void();

  map<int, int> t;
  for (int i = 0; i < N; i++) t[a[i]]++;

  multiset<int> m1{a[0]}, m2;
  int x = a[0] + d;
  while (t[x] > 0) {
    m1.insert(x);
    t[x]--;
    x += d;
  }

  for (auto [k, v] : t) {
    for (int i = 0; i < v; i++) m2.insert(k);
  }

  if (is_arith(m1) && is_arith(m2)) return cout << "Yes\n", void();

  auto l = m1.rbegin();
  m2.insert(*l);
  m1.erase(prev(m1.end()));

  if (is_arith(m1) && is_arith(m2)) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
