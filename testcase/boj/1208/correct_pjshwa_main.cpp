#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[40], n, s;
long long res;
unordered_map<int, int, custom_hash> cnt;

void msum(int i, int sum) {
  if (i == n / 2) cnt[sum]++;
  else {
    msum(i + 1, sum);
    msum(i + 1, sum + a[i]);
  }
}

void fsum(int i, int sum) {
  if (i == n) res += cnt[s - sum];
  else {
    fsum(i + 1, sum);
    fsum(i + 1, sum + a[i]);
  }
}

int main() {
  fast_io();

  cin >> n >> s;
  for (int i = 0; i < n; i++) cin >> a[i];

  msum(0, 0);
  fsum(n / 2, 0);

  cout << (s ? res : res - 1);
}
