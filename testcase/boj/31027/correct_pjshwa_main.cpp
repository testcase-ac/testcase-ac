#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[2][MAXN];

void solve() {
  int N; cin >> N;

  ll sum = 0;
  for (int i = 0; i < N; i++) cin >> A[0][i], sum += A[0][i];
  for (int i = 0; i < N; i++) cin >> A[1][i], sum += A[1][i];

  int H = N / 2;
  if (N & 1) {
    ll as1 = 0, as2 = 0, as3 = 0;
    for (int i = 0; i < H; i++) as1 += A[0][i] + A[1][i];
    for (int i = 0; i <= H; i++) as2 += A[0][i] + A[1][i];
    for (int i = 0; i < N; i++) as3 += A[0][i];
    
    ll ascore = max(as1, min(as2, as3));
    ll bscore = sum - ascore;
    cout << ascore << " " << bscore << "\n";
  }
  else {
    ll bs1 = 0, bs2 = 0, bs3 = 0;
    for (int i = 0; i < H - 1; i++) bs1 += A[0][N - 1 - i] + A[1][N - 1 - i];
    for (int i = 0; i < H; i++) bs2 += A[0][N - 1 - i] + A[1][N - 1 - i];
    for (int i = 0; i < N; i++) bs3 += A[1][i];

    ll bscore = max(bs1, min(bs2, bs3));
    ll ascore = sum - bscore;
    cout << ascore << " " << bscore << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
