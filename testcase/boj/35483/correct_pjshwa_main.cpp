#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e9;
vector<int> P;

bool is_p(int x) {
  return binary_search(P.begin(), P.end(), x);
}

void solve() {
  int N, ans = 0; cin >> N;
  for (int p1 : P) {
    if (p1 > N) break;
    int p2 = N - p1;
    ans += is_p(p2);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  auto push = [&](ll x) {
    if (x <= MAXN) P.push_back(x);
  };

  for (int j = 1; j <= 9; ++j) push(j);
  for (int i = 1; i <= 10000; ++i) {
    string u = to_string(i);
    push(stoll(u + u));
    for (int j = 0; j <= 9; ++j) {
      push(stoll(u + to_string(j) + u));
    }
  }
  sort(P.begin(), P.end());

  int t = 1;
  cin >> t;
  while (t--) solve();
}
