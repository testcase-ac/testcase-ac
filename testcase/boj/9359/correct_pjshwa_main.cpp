#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> prime_factors(int n) {
  vector<int> r;
  while (n % 2 == 0) {
    r.push_back(2);
    n >>= 1;
  }

  for (int i = 3;i <= sqrt(n); i = i + 2) {
    while (n % i == 0) {
      r.push_back(i);
      n /= i;
    }
  }

  if (n != 1) r.push_back(n);
  return r;
}

ll count_coprimes_upto(ll n, vector<int>& fs) {
  ll cnt = 0, sz = fs.size();
  int stk[20], stk_pointer;
  int multiplier;
  bool finished;

  // combinations
  for (int i = 1; i <= sz; i++) {
    multiplier = (i & 1) ? 1 : -1;
    stk_pointer = -1;
    stk[0] = 0;

    finished = false;
    while (!finished) {

      for (stk_pointer++; stk_pointer < i - 1; stk_pointer++) {
        stk[stk_pointer + 1] = stk[stk_pointer] + 1;
      }

      // stk[0]..stk[i - 1] contains the indexes
      // do work here
      int cv = 1;
      for (int j = 0; j < i; j++) cv *= fs[stk[j]];
      cnt += multiplier * (n / cv);

      do {
        if (stk_pointer == -1) {
          finished = true;
          break;
        }
        stk[stk_pointer--]++;
      } while (stk[stk_pointer + 1] + i == sz + stk_pointer + 2);
    }
  }

  return cnt;
}

int main() {
  fast_io();

  ll t, s, f, n;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> s >> f >> n;
    vector<int> fs = prime_factors(n);
    compress(fs);

    cout << "Case #" << i << ": ";
    cout << (f - s + 1) - (count_coprimes_upto(f, fs) - count_coprimes_upto(s - 1, fs));
    cout << '\n';
  }
}
