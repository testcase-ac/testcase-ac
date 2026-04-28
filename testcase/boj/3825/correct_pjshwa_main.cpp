#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
bool a[20001];

int main() {
  fast_io();

  for (int i = 1; i <= 300; i++) for (int j = 1; j <= 300; j++) {
    int s = i * i + j * j;
    if (s <= 20000) a[s] = true;
  }

  int t;
  cin >> t;
  while (t--) {
    int m, n;
    cin >> m >> n;

    bool found = false;
    int q = m * m + n * n;
    for (int i = 2; i * i <= q; i++) {
      if (q % i == 0) {
        if (a[i] || a[q / i]) {
          cout << "C\n";
          found = true;
          break;
        }
      }
    }

    if (!found) cout << "P\n";
  }
}
