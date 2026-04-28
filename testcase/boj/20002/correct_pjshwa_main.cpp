#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int farm[300][300];
int psum[301][301];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> farm[i][j];
  }

  memset(psum, 0, sizeof(psum));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + farm[i - 1][j - 1];
    }
  }

  int mx = -2e9;
  for (int k = 1; k <= n; k++) {
    for (int i = k; i <= n; i++) {
      for (int j = k; j <= n; j++) {
        mx = max(mx, psum[i][j] - psum[i - k][j] - psum[i][j - k] + psum[i - k][j - k]);
      }
    }
  }

  cout << mx << '\n';
}
