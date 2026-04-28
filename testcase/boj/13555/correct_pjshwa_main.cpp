#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e6, MOD = 5e6;
int arr[MAX + 1], tree[50][MAX + 1];
 
void update(int y, int x, int val) {
  while (x <= MAX) {
    tree[y][x] = (tree[y][x] + val) % MOD;
    x += x & -x;
  }
}

int sum(int y, int x) {
  int sum = 0;
  while (x > 0) {
    sum = (sum + tree[y][x]) % MOD;
    x -= x & -x;
  }

  return sum;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  vector<pair<int, int>> v;
  v.resize(n);

  for (int i = 0; i < n; i++) cin >> v[i].first, v[i].second = -i;
  sort(v.begin(), v.end());

  for (int i = 0; i < n; i++) {
    auto[av, ai] = v[i];

    ll qr = 1;
    for (int j = 0; j < k; j++) {
      update(j, -ai + 1, qr);
      qr = sum(j, -ai);
    }
  }

  cout << sum(k - 1, n);
}
