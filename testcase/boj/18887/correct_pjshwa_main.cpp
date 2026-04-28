#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Lecture { int sa, ea, sb, eb; };

set<pii> E;
bool overlaps(int s, int e) {
  auto its = E.upper_bound({s, 1});
  auto ite = E.lower_bound({e, -1});
  if (its != ite) return true;
  if (ite != E.end() && ite->second == -1) return true;
  return false;
}

void solve() {
  int n; cin >> n;
  vector<Lecture> A(n);
  priority_queue<tii, vector<tii>, greater<tii>> wait;
  for (int i = 0; i < n; i++) {
    int sa, ea, sb, eb; cin >> sa >> ea >> sb >> eb;
    A[i] = {sa, ea + 1, sb, eb + 1};
  }

  sort(A.begin(), A.end(), [](const Lecture& a, const Lecture& b) {
    return a.sa < b.sa;
  });
  for (auto& [sa, ea, sb, eb] : A) {
    while (!wait.empty() && get<0>(wait.top()) <= sa) {
      auto [_, s, e] = wait.top(); wait.pop();
      E.insert({s, 1}); E.insert({e, -1});
    }
    if (overlaps(sb, eb)) return cout << "NO\n", void();
    else wait.push({ea, sb, eb});
  }

  E.clear(); wait = priority_queue<tii, vector<tii>, greater<tii>>();
  sort(A.begin(), A.end(), [](const Lecture& a, const Lecture& b) {
    return a.sb < b.sb;
  });
  for (auto& [sa, ea, sb, eb] : A) {
    while (!wait.empty() && get<0>(wait.top()) <= sb) {
      auto [_, s, e] = wait.top(); wait.pop();
      E.insert({s, 1}); E.insert({e, -1});
    }
    if (overlaps(sa, ea)) return cout << "NO\n", void();
    else wait.push({eb, sa, ea});
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
