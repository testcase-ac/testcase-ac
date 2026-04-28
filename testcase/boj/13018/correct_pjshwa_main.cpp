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
  k = n - k;

  if (k == 0) {
    cout << "Impossible";
    return 0;
  }

  if (n == 1) cout << 1;
  else if (n == 2) {
    if (k == 1) cout << "1 2";
    else cout << "2 1";
  }
  else {
    if (n & 1) {
      if (k & 1) {
        cout << "1 "; k--;
        for (int i = 2; i <= n; i += 2) {
          if (k) {
            cout << i + 1 << ' ' << i << ' ';
            k -= 2;
          }
          else cout << i << ' ' << i + 1 << ' ';
        }
      }
      else {
        cout << "2 1 "; k -= 2;
        for (int i = 3; i < n; i += 2) {
          if (k) {
            cout << i + 1 << ' ' << i << ' ';
            k -= 2;
          }
          else cout << i << ' ' << i + 1 << ' ';
        }
        cout << n;
      }
    }
    else {
      if (k & 1) {
        cout << "1 "; k--;
        for (int i = 2; i < n; i += 2) {
          if (k) {
            cout << i + 1 << ' ' << i << ' ';
            k -= 2;
          }
          else cout << i << ' ' << i + 1 << ' ';
        }
        cout << n;
      }
      else {
        cout << n << ' '; k -= 2;
        for (int i = 2; i < n; i += 2) {
          if (k) {
            cout << i + 1 << ' ' << i << ' ';
            k -= 2;
          }
          else cout << i << ' ' << i + 1 << ' ';
        }
        cout << 1;
      }
    }
  }

}
