#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_pw2(int x) {
  return (x & (x - 1)) == 0;
}

const int MAX = 5e5;
bool vis[MAX + 1];
vector<int> A;

void insert(int v) {
  if (vis[v]) return;
  vis[v] = true;
  A.push_back(v);
}

void solve() {
  int N, K;
  cin >> N >> K;

  if (is_pw2(N) || is_pw2(N - 1) || K < 4) return cout << "-1\n", void();

  insert(1); insert(3); insert(2);
  while (A.back() + 4 <= N) insert(A.back() + 4);
  while (A.back() + 2 <= N) insert(A.back() + 2);
  while (A.back() + 1 <= N) insert(A.back() + 1);

  int it = N;
  while (it >= 2) {
    if (is_pw2(it - 1)) {
      insert(it - 1);
      insert(it);
      it -= 2;
    }
    else insert(it--);
  }
  A.push_back(1);

  int d = 0;
  for (int i = 1; i < A.size(); i++) {
    d += abs(A[i] - A[i - 1]);
    assert(A[i] & A[i - 1]);
  }

  cout << d << '\n';
  for (int e : A) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
