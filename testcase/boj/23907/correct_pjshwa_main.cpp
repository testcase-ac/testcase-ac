#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MAXV = 2e7, BIAS = 1e7;
int A[MAX], T[MAXV + 1];
vector<int> sqs;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  memset(T, 0, sizeof(T));
  T[BIAS] = 1;

  ll run = 0, ans = 0;
  for (int i = 0; i < N; i++) {
    run += A[i];
    for (int sq : sqs) {
      if (run - sq + BIAS >= 0 && run - sq + BIAS <= MAXV) ans += T[run - sq + BIAS];
    }
    T[run + BIAS]++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i * i <= MAXV; i++) sqs.push_back(i * i);
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}