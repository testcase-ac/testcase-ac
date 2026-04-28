#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

pii tests[(int)1e5];
int main() {
  fast_io();

  int n, m, s;
  cin >> n >> m >> s;

  int xi, yi;
  for (int i = 0; i < n; i++) {
    cin >> xi >> yi;
    tests[i] = {xi, yi};
  }
  sort(tests, tests + n);

  if (m <= tests[0].first) {
    cout << "0\n";
    return 0;
  }

  for (int i = 0; i < n - 1; i++) {
    if (m <= tests[i + 1].first - tests[i].first - tests[i].second) {
      cout << tests[i].first + tests[i].second << '\n';
      return 0;
    }
  }

  if (m <= s - tests[n - 1].first - tests[n - 1].second) {
    cout << tests[n - 1].first + tests[n - 1].second << '\n';
  }
  else cout << "-1\n";
}
