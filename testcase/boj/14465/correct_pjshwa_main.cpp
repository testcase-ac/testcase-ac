#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool tfbroken[MAX];

int main() {
  fast_io();

  int n, k, b, x;
  cin >> n >> k >> b;
  while (b--) {
    cin >> x;
    tfbroken[x - 1] = true;
  }

  int min_fix, cur_fix = 0;
  for (int i = 0; i < k; i++) {
    if (tfbroken[i]) cur_fix++;
  }
  min_fix = cur_fix;

  for (int i = k; i < n; i++) {
    if (tfbroken[i]) cur_fix++;
    if (tfbroken[i - k]) cur_fix--;
    min_fix = min(min_fix, cur_fix);
  }

  cout << min_fix << '\n';
}
