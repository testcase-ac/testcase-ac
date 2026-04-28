#include <bits/stdc++.h>
#define ll long long
#define MOD int(1e9 + 7)
using namespace std;

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[2001][2001];
int main() {
  FastIO();

  int n, m;
  cin >> n >> m;
  for(int i = 0; i < n; i++) {
    cin >> board[i];
  }

  int cnt = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      char c = board[i][j];
      if (
        (i == 0 || board[i - 1][j] == c) && 
        (j == 0 || board[i][j - 1] == c) && 
        (i == n - 1 || board[i + 1][j] == c) && 
        (j == m - 1 || board[i][j + 1] == c)
      ) cnt++;
    }
  }
  
  cout << lpow(2, cnt, MOD) << '\n';
}
