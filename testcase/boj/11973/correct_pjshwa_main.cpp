#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000;
int hay[MAX], n, k;

bool covered(int r) {
  int cnt = 0, sp = 0, sval = hay[sp];
  while (1) {
    cnt++;
    while (sp < n && hay[sp] <= sval + 2 * r) sp++;
    if (sp == n) break;

    sval = hay[sp];
  }
  return cnt <= k;
}

int main() {
  fast_io();

  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> hay[i];
  sort(hay, hay + n);

  int left = 1, right = 5e8;
  int mid = (left + right) / 2;

  while (left < right) {
    if (covered(mid)) right = mid;
    else left = mid + 1;

    mid = (left + right) / 2;
  }

  cout << mid << '\n';
}
