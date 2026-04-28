#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 20;
const int MASK = (1 << 20) - 1;

ll F[MAX], A[MAX];
int N, K;

ll solve_and() {
  memset(F, 0, sizeof(F));

  vector<int> B;
  for (int i = 0; i < N; i++) {
    if ((A[i] & K) == K) B.push_back(A[i] - K);
  }
  for (int e : B) F[e]++;

  // SOS DP
  for (int i = 0; i < 20; i++) for (int x = 0; x < (1 << 20); x++) {
    if (x & (1 << i)) F[x] += F[x ^ (1 << i)];
  }

  ll ans = 0;
  for (int e : B) {
    ans += F[e ^ MASK];
    if (e == 0) ans--;
  }
  return ans / 2;
}

ll solve_or() {
  memset(F, 0, sizeof(F));

  int oK = K ^ MASK;

  vector<int> B;
  for (int i = 0; i < N; i++) {
    int e = A[i] ^ MASK;
    if ((e & oK) == oK) B.push_back(e - oK);
  }
  for (int e : B) F[e]++;

  // SOS DP
  for (int i = 0; i < 20; i++) for (int x = 0; x < (1 << 20); x++) {
    if (x & (1 << i)) F[x] += F[x ^ (1 << i)];
  }

  ll ans = 0;
  for (int e : B) {
    ans += F[e ^ MASK];
    if (e == 0) ans--;
  }
  return ans / 2;
}

ll solve_xor() {
  memset(F, 0, sizeof(F));
  for (int i = 0; i < N; i++) F[A[i]]++;

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    ans += F[A[i] ^ K];
    if (K == 0) ans--;
  }
  return ans / 2;
}

void solve() {
  cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i];
  cout << solve_and() << ' ' << solve_or() << ' ' << solve_xor() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
