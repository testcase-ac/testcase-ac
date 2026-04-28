#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  deque<int> OA(N);
  for (int i = 0; i < N; i++) cin >> OA[i];
  sort(OA.begin(), OA.end());

  ll ans = 0;
  {
    auto A = OA; ll cur = 0;
    int B1 = A.back(), B2 = A.back(); A.pop_back();

    bool f = true;
    while (A.size() >= 2) {
      int A1, A2;
      if (f) {
        A1 = A.front(); A.pop_front();
        A2 = A.front(); A.pop_front();
      }
      else {
        A1 = A.back(); A.pop_back();
        A2 = A.back(); A.pop_back();
      }
      cur += max(abs(B1 - A1) + abs(B2 - A2), abs(B1 - A2) + abs(B2 - A1));
      B1 = A1; B2 = A2;
      f = !f;
    }

    if (A.size() == 1) {
      int A1 = A.front();
      cur += max(abs(B1 - A1), abs(B2 - A1));
    }
    ans = max(ans, cur);
  }
  {
    auto A = OA; ll cur = 0;
    int B1 = A.front(), B2 = A.front(); A.pop_front();

    bool f = true;
    while (A.size() >= 2) {
      int A1, A2;
      if (f) {
        A1 = A.back(); A.pop_back();
        A2 = A.back(); A.pop_back();
      }
      else {
        A1 = A.front(); A.pop_front();
        A2 = A.front(); A.pop_front();
      }
      cur += max(abs(B1 - A1) + abs(B2 - A2), abs(B1 - A2) + abs(B2 - A1));
      B1 = A1; B2 = A2;
      f = !f;
    }

    if (A.size() == 1) {
      int A1 = A.front();
      cur += max(abs(B1 - A1), abs(B2 - A1));
    }
    ans = max(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
