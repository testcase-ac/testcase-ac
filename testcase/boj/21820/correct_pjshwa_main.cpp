#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int c[MAX];
ll n, l;

bool hpossible(int h) {
  if (h > n) return false;

  ll cnt = 0;
  for (int i = 0; i < h; i++) cnt += max(0, h - c[i]);
  return h - c[h - 1] <= 1 && cnt <= l;
}

int main() {
  fast_io();

  cin >> n >> l;
  for (int i = 0; i < n; i++) cin >> c[i];
  sort(c, c + n);
  reverse(c, c + n);

  int left = 0, right = 1e9;
  int mid = (left + right) / 2;
  while (left < right) {
    if (hpossible(mid)) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid - 1 << '\n';
}
