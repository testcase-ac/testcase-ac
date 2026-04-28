#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

int N;
void solve() {
  vector<tii> current;

  for (int i = 0; i < N; ++i) {
    string op; cin >> op;
    if (op == "W") {
      int I, S, last = 0; cin >> I >> S;
      vector<tii> pushed;
      for (auto& [ox, os, _] : current) {
        if (S == 0) break;
        int add = min(S, ox - last);
        if (add) {
          pushed.emplace_back(last, add, I);
          S -= add;
        }
        last = ox + os;
      }
      if (S > 0) pushed.emplace_back(last, S, I);

      // push all to current
      for (auto& [x, s, I] : pushed) current.emplace_back(x, s, I);
      sort(current.begin(), current.end());
    }
    if (op == "D") {
      int I; cin >> I;

      vector<tii> ncurrent;
      for (auto& [x, s, i] : current) {
        if (i != I) ncurrent.emplace_back(x, s, i);
      }
      swap(current, ncurrent);
    }
    if (op == "R") {
      int P, f = -1; cin >> P;
      for (auto& [x, s, I] : current) {
        if (P >= x && P < x + s) f = I;
      }
      cout << f << '\n';
    }

    // cout << "pushed = ";
    // for (auto& [I, V] : pushed) {
    //   cout << I << ": ";
    //   for (auto& [x, s] : V) cout << '(' << x << ", " << s << ") ";
    //   cout << '\n';
    // }
    // cout << "current = ";
    // for (auto& [x, s, I] : current) cout << '(' << x << ", " << s << ", " << I << ") ";
    // cout << '\n';
  }
}

int main() {
  fast_io();

  int f = 1;
  while (cin >> N) {
    if (N == 0) break;
    if (f) f = 0;
    else cout << '\n';
    solve();
  }
}
