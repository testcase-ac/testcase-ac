#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n, m, ai, a = 1;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> ai;
    a = (a * ai) % m;
  }
  cout << a << '\n';
}
