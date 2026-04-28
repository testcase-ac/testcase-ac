#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  if (n == 2) {
    if (k == 0) cout << "YES\n..\n..\n";
    else if (k == 1) cout << "YES\n#.\n..\n";
    else cout << "NO\n";
    return 0;
  }

  if (k + n <= n * n) {
    cout << "YES\n";

    if (n & 1) {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i == j) cout << '.';
          else if (cnt < k) {
            cout << '#';
            cnt++;
          }
          else cout << '.';
        }
        cout << '\n';
      }
    }
    else {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i == n / 2 - 1) {
            if (i == j - 1) cout << '.';
            else if (cnt < k) {
              cout << '#';
              cnt++;
            }
            else cout << '.';
          }
          else if (i == n / 2) {
            if (i == j + 1) cout << '.';
            else if (cnt < k) {
              cout << '#';
              cnt++;
            }
            else cout << '.';
          }
          else {
            if (i == j) cout << '.';
            else if (cnt < k) {
              cout << '#';
              cnt++;
            }
            else cout << '.';
          }
        }
        cout << '\n';
      }

    }
  }
  else cout << "NO\n";
}
