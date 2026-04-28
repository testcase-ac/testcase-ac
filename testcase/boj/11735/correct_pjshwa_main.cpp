#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool r[1000001], c[1000001];
int main() {
  fast_io();

  ll n, q, rmc = 0, rmv = 0, cmc = 0, cmv = 0;
  cin >> n >> q;

  ll argint, default_v;
  while (q--) {
    string op, arg;
    cin >> op >> arg;
    argint = stoll(arg);
    default_v = argint * n + (n * (n + 1) / 2);

    if (op == "R") {
      if (r[argint]) cout << "0\n";
      else {
        cout << default_v - cmc * argint - cmv << '\n';
        r[argint] = true;
        rmc++;
        rmv += argint;
      }
    }
    else {
      if (c[argint]) cout << "0\n";
      else {
        cout << default_v - rmc * argint - rmv << '\n';
        c[argint] = true;
        cmc++;
        cmv += argint;
      }
    }
  }
}
