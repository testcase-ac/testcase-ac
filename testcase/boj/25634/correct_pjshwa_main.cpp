#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX];

void solve() {
  int N;
  cin >> N;

  ll sum = 0;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    if (x) {
      sum += A[i];
      A[i] = -A[i];
    }
  }

  ll max_so_far = -1e18, max_ending_here = 0;
  for (int i = 0; i < N; ++i) {
    max_ending_here = max_ending_here + A[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }

  cout << sum + max_so_far << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
