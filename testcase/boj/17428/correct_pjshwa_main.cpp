#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll d[31][31];
int main() {
  fast_io();

  d[1][0] = 1;
  for (int i = 1; i <= 30; i++) {
    for (int j = i; j <= 30; j++) d[i][j] = d[i - 1][j] + d[i][j - 1];
  }

  ll N, K;
  cin >> N >> K;
  N >>= 1;
  K++;

  if (K > d[N][N + 1]) {
    cout << -1;
    return 0;
  }

  int i = N, j = N + 1;
  while (j > 1) {
    if(K <= d[i][j]) {
      cout << '(';
      i--;
    }
    else {
      cout << ')';
      K -= d[i][j--];
    }
  }
}
