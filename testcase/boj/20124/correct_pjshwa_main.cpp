#include <bits/stdc++.h>
#define psi pair<string, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

psi ppl[(int)1e5];
int main() {
  fast_io();

  int n;
  cin >> n;

  string name;
  int votes;
  for (int i = 0; i < n; i++) {
    cin >> name >> votes;
    ppl[i] = {name, votes};
  }
  sort(
    ppl,
    ppl + n,
    [](psi& p1, psi& p2) {
      return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
    }
  );

  cout << ppl[0].first << '\n';
}
