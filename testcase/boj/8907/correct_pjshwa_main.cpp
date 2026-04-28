#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e3;
int cnt[MAX];
int main() {
  fast_io();

  int t, n, s, si;
  cin >> t;

  while (t--) {
    memset(cnt, 0, sizeof(cnt));
    cin >> n;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        cin >> si;
        cnt[i] += si;
        cnt[j] += si;
      }
    }

    s = 0;
    for (int i = 0; i < n; i++) s += cnt[i] * (n - 1 - cnt[i]);
    cout << n * (n - 1) * (n - 2) / 6 - s / 2 << '\n';
  }
}
