#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int D[MAX];

void solve() {
  int N, L, A, B; cin >> N >> L >> A >> B;
  for (int i = 0; i < N; i++) cin >> D[i];

  deque<pii> M;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    x = (x - 1) / B + 1;
    M.emplace_back(D[i], x);
  }
  sort(M.begin(), M.end());

  int pos = 0, mmove = 0;
  auto movable = [&]() {
    for (auto [d, x] : M) {
      int rh = d - mmove - pos - 2;
      if (rh > A) break;
      if (rh < x) return false;
    }
    return true;
  };
  auto failed = [&]() {
    return !M.empty() && M.front().first - mmove <= pos;
  };

  int ans = 0;
  while (pos < L) {
    if (failed()) return cout << "-1\n", void();

    if (movable()) pos++;
    else {
      // 모기약 분사
      stack<pii> tmp;
      while (!M.empty()) {
        auto [d, x] = M.front();
        if (d - mmove - pos <= A) {
          tmp.emplace(d, x - 1);
          M.pop_front();
        }
        else break;
      }

      while (!tmp.empty()) {
        auto [d, x] = tmp.top(); tmp.pop();
        if (x) M.emplace_front(d, x);
      }
    }
    ans++; mmove++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
