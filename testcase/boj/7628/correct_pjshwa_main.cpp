#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const char sig[4] = "RPS";

int rec(ll n) {
  if (n < 3) return n;

  ll pw = 1;
  while (pw * 3 <= n) pw *= 3;

  if (n / pw == 1) return (rec(n % pw) + 1) % 3;
  if (n / pw == 2) return (rec(n % pw) + 2) % 3;
}

void solve(ll n) {
  int ans = rec(n - 1) + 1;
  cout << sig[ans % 3] << '\n';
}

int main() {
  fast_io();

  while (1) {
    ll n;
    cin >> n;
    if (n == 0) break;

    solve(n);
  }
}
