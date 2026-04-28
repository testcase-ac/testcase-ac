#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int lp[MAXN + 1], A[MAXN];
vector<int> pr;

void solve() {
  int N, K, i = 0, j = 0, sum = 0; cin >> N >> K;
  for (; i < N && sum < K; ++i) {
    A[i] = pr[j++]; sum += N - j;
  }
  while (i < N) A[i++] = pr[j];
  while (sum > K) A[--i] *= 2, --sum;

  for (i = 0; i < N; ++i) cout << A[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
