#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k, a_cnt, b_cnt, diff;
  cin >> n >> k;

  if (k == 0) {
    for (int i = 0; i < n; i++) cout << 'A';
    return 0;
  }

  int third = n / 3;
  int two_thirds = n - third;
  int o_third = two_thirds / 2;
  if (third * two_thirds + o_third * (two_thirds - o_third) < k) cout << -1;
  else if (third * two_thirds >= k) {
    // Use A, B only
    a_cnt = 0;
    while (a_cnt * (n - a_cnt) < k) a_cnt++;
    diff = a_cnt * (n - a_cnt) - k;
    for (int i = 0; i < a_cnt - 1; i++) cout << 'A';
    for (int i = 0; i < diff; i++) cout << 'B';
    cout << 'A';
    for (int i = 0; i < n - (a_cnt + diff); i++) cout << 'B';
  }
  else {
    // Use A, B, C
    for (int i = 0; i < third; i++) cout << 'A';
    k -= third * two_thirds;

    b_cnt = 0;
    while (b_cnt * (two_thirds - b_cnt) < k) b_cnt++;
    diff = b_cnt * (two_thirds - b_cnt) - k;
    for (int i = 0; i < b_cnt - 1; i++) cout << 'B';
    for (int i = 0; i < diff; i++) cout << 'C';
    cout << 'B';
    for (int i = 0; i < two_thirds - (b_cnt + diff); i++) cout << 'C';
  }
  cout << '\n';
}
