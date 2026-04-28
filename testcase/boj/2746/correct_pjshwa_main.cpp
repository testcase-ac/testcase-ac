#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
ll A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  ll ans = 0;

  // Case 1: remove last 2 elements
  {
    ll sum = 0;
    for (int i = 0; i < N - 3; ++i) sum += A[i];
    if (sum == A[N - 3]) ++ans;
  }

  // Case 2: remove last element and one in the front
  {
    ll sum = 0;
    for (int i = 0; i < N - 2; ++i) sum += A[i];
    for (int i = 0; i < N - 2; ++i) {
      if (sum - A[i] == A[N - 2]) ++ans;
    }
  }

  // Case 3: remove 2 elements in the front
  {
    map<ll, int> cnt; ll sum = 0, acc = 0;
    for (int i = 0; i < N - 1; ++i) {
      ++cnt[A[i]];
      sum += A[i];
    }
    for (int i = 0; i < N - 1; ++i) {
      ll need = sum - A[N - 1] - A[i];
      --cnt[A[i]];
      acc += cnt[need];
      ++cnt[A[i]];
    }
    ans += acc / 2;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
