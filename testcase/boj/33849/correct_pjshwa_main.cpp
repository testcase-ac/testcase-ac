#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
ll A[MAXN], B[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> B[i];
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll nom = A[0], den = B[0];
  for (int i = 0; i < N; ++i) {
    ll a = A[i], b = B[i];
    if (nom * b < den * a) nom = a, den = b;
  }

  ll g = __gcd(nom, den);
  nom /= g; den /= g;
  cout << nom << ' ' << den << '\n';

  int streak = 0, max_streak = 0;
  for (int i = 0; i < N; ++i) {
    if (A[i] * den == B[i] * nom) ++streak;
    else streak = 0;
    max_streak = max(max_streak, streak);
  }
  cout << max_streak << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
