#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  vector<int> lis_vector;
  int n, next;
  while (cin >> n) {
    lis_vector.clear();
    lis_vector.push_back(-(1e9 + 1));

    for (int i = 0; i < n; i++) {
      cin >> next;

      if (next > lis_vector.back()) lis_vector.push_back(next);
      else {
        auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
        *it = next;
      }
    }

    cout << lis_vector.size() - 1 << '\n';
  }
}
