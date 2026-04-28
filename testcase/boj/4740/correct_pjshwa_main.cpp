#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  while (1) {
    string S;
    getline(cin, S);
    if (S == "***") break;

    reverse(S.begin(), S.end());
    cout << S << '\n';
  }

}
