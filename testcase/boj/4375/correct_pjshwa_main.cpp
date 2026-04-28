#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  while (cin >> n) {
    int k = 1, iter = 1;
    while (k % n) {
      iter++;
      k = (k % n) * 10 + 1;
    }

    cout << iter << '\n';
  }
}
