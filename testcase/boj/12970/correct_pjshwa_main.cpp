#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  int half = n / 2;
  if (half * (n - half) < k) cout << -1;
  else {
    int a_cnt = 0, diff;
    while (a_cnt * (n - a_cnt) < k) a_cnt++;
    if (a_cnt) {
      diff = a_cnt * (n - a_cnt) - k;
      for (int i = 0; i < a_cnt - 1; i++) cout << 'A';
      for (int i = 0; i < diff; i++) cout << 'B';
      cout << 'A';
      for (int i = 0; i < n - (a_cnt + diff); i++) cout << 'B';
    }
    else for (int i = 0; i < n; i++) cout << 'B';
  }
  cout << '\n';
}
