#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll f[20];
int n;

void k_to_seq() {
  ll k;
  cin >> k;
  k--;

  set<int> used;
  for (int i = 1; i <= n; i++) {
    int quot = k / f[n - i];

    int nxt = 1;
    for (int j = 0; j <= quot; j++) {
      if (used.count(nxt)) j--;
      nxt++;
    }
    nxt--;

    cout << nxt << ' ';
    used.insert(nxt);
    k %= f[n - i];
  }

  cout << '\n';
}

void seq_to_k() {
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  ll k = 0;
  set<int> used;
  for (int i = 0; i < n; i++) {
    int kth = 0;
    for (int j = 1; j <= a[i]; j++) {
      if (!used.count(j)) kth++;
    }

    used.insert(a[i]);
    k += f[n - i - 1] * (kth - 1);
  }

  cout << k + 1 << '\n';
}

int main() {
  fast_io();

  f[0] = f[1] = 1;
  for (int i = 2; i < 20; i++) f[i] = f[i - 1] * i;

  int o;
  cin >> n >> o;
  if (o == 1) k_to_seq();
  else seq_to_k();
}
