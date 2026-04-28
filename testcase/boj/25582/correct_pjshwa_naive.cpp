#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 4000;
bool pp[MAX][MAX], pw[MAX][MAX];

bool point_refl(int a, int b) {
  if (a == -1 && b == -1) return true;
  if (a == 'p' && b == 'd') return true;
  if (a == 'd' && b == 'p') return true;
  if (a == 'b' && b == 'q') return true;
  if (a == 'q' && b == 'b') return true;
  if (a == 'u' && b == 'n') return true;
  if (a == 'n' && b == 'u') return true;
  if (a == 's' && b == 's') return true;
  if (a == 'z' && b == 'z') return true;
  if (a == 'l' && b == 'l') return true;
  if (a == 'o' && b == 'o') return true;
  if (a == 'x' && b == 'x') return true;
  return false;
}

bool window_refl(int a, int b) {
  if (a == -1 && b == -1) return true;
  if (a == 'p' && b == 'q') return true;
  if (a == 'q' && b == 'p') return true;
  if (a == 'b' && b == 'd') return true;
  if (a == 'd' && b == 'b') return true;
  if (a == 'i' && b == 'i') return true;
  if (a == 'm' && b == 'm') return true;
  if (a == 'v' && b == 'v') return true;
  if (a == 'w' && b == 'w') return true;
  if (a == 'l' && b == 'l') return true;
  if (a == 'o' && b == 'o') return true;
  if (a == 'x' && b == 'x') return true;
  return false;
}

void solve() {
  string S;
  cin >> S;
  int n = S.size();

  int ans1 = 0, ans2 = 0;
  for (int i = 0; i < n; i++) pp[i][i] = point_refl(S[i], S[i]);
  for (int i = 0; i < n - 1; i++) {
    pp[i][i + 1] = point_refl(S[i], S[i + 1]);
  }
  for (int diff = 2; diff < n; diff++) {
    for (int i = 0; i < n - diff; i++) {
      int j = i + diff;
      pp[i][j] = (point_refl(S[i], S[j]) && pp[i + 1][j - 1]);
    }
  }
  for (int i = 0; i < n; i++) for (int j = i; j < n; j++) {
    if (pp[i][j]) ans1 = max(ans1, j - i + 1);
  }

  for (int i = 0; i < n; i++) pw[i][i] = window_refl(S[i], S[i]);
  for (int i = 0; i < n - 1; i++) {
    pw[i][i + 1] = window_refl(S[i], S[i + 1]);
  }
  for (int diff = 2; diff < n; diff++) {
    for (int i = 0; i < n - diff; i++) {
      int j = i + diff;
      pw[i][j] = (window_refl(S[i], S[j]) && pw[i + 1][j - 1]);
    }
  }
  for (int i = 0; i < n; i++) for (int j = i; j < n; j++) {
    if (pw[i][j]) ans2 = max(ans2, j - i + 1);
  }

  int ans = max(ans1, ans2);
  if (ans == 0) cout << "NOANSWER\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
