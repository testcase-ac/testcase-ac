#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int adj[250][250];
int adj2[250][250];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> adj[i][j];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        adj2[i][j] += adj[i][k] * adj[k][j];
      }
    }
  }

  ll cnt = 0, s;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      s = adj2[i][j];
      cnt += s * (s - 1);
    }
  }

  cout << cnt << '\n';
}
