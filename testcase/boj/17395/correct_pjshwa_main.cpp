#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll x0, n;
  cin >> x0 >> n;

  int ocnt = 0;
  ll x0d = x0;
  stack<int> binrep;
  while (x0d) {
    if (x0d & 1) {
      binrep.push(1);
      ocnt++;
    }
    else binrep.push(0);
    x0d /= 2;
  }

  if (n > ocnt) return cout << "-1\n", 0;
  while (--n) {
    while (binrep.top() == 0) binrep.pop();
    binrep.pop();
    x0 -= (1LL << binrep.size());
    cout << x0 << ' ';
  }
  cout << "0\n";
}
