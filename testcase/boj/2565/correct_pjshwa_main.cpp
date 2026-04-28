#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

pii wires[100000];
int main() {
  fast_io();

  int n, next;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> wires[i].first >> wires[i].second;
  sort(wires, wires + n);

  vector<int> lis_vector;
  lis_vector.push_back(-(1e9 + 1));
  for (int i = 0; i < n; i++) {
    next = wires[i].second;

    if (next > lis_vector.back()) lis_vector.push_back(next);
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
      *it = next;
    }
  }

  cout << n - lis_vector.size() + 1 << '\n';
}
