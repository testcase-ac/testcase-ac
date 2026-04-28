#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll LO, HI;
__int128_t fib[101];

void solve() {
  cout << "Range " << LO << " to " << HI << ":\n";

  bool found = false;
  for (int i = 0; i <= 100; i++) {
    if (fib[i] < LO || fib[i] > HI) continue;
    found = true;

    cout << "Fib(" << i << ") = " << (ll)fib[i] << ", lg ";
    if (i == 0) cout << "does not exist\n";
    else cout << "is " << fixed << setprecision(6) << log2(fib[i]) << '\n';

    if (fib[i] <= 1) cout << "No prime factors\n";
    else {
      cout << "Prime factors: ";
      if (i <= 80) {
        ll n = fib[i];
        for (ll i = 2; i * i <= n; i++) {
          while (n % i == 0) {
            cout << i << ' ';
            n /= i;
          }
        }
        if (n > 1) cout << n;
        cout << '\n';
      }
      else if (i == 81) cout << "2 17 53 109 2269 4373 19441\n";
      else if (i == 82) cout << "2789 59369 370248451\n";
      else if (i == 83) cout << "99194853094755497\n";
      else if (i == 84) cout << "2 2 2 2 3 3 13 29 83 211 281 421 1427\n";
      else if (i == 85) cout << "5 1597 9521 3415914041\n";
      else if (i == 86) cout << "6709 144481 433494437\n";
      else if (i == 87) cout << "2 173 514229 3821263937\n";
      else if (i == 88) cout << "3 7 43 89 199 263 307 881 967\n";
      else if (i == 89) cout << "1069 1665088321800481\n";
      else if (i == 90) cout << "2 2 2 5 11 17 19 31 61 181 541 109441\n";
      else if (i == 91) cout << "13 13 233 741469 159607993\n";
      else if (i == 92) cout << "3 139 461 4969 28657 275449\n";
    }
  }

  if (!found) cout << "No Fibonacci numbers in the range\n";
}

int main() {
  fast_io();

  fib[0] = 0, fib[1] = 1;
  for (int i = 2; i <= 100; i++) fib[i] = fib[i - 1] + fib[i - 2];

  while (cin >> hex >> LO >> HI) {
    if (LO >= HI) break;
    solve();
    cout << '\n';
  }
}
