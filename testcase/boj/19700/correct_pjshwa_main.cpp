#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, hi, ki;
  cin >> n;

  priority_queue<pair<int, int>> pqh;
  vector<int> counts;
  for (int i = 0; i < n; i++) {
    cin >> hi >> ki;
    pqh.push({hi, ki});
  }

  while (!pqh.empty()) {
    tie(hi, ki) = pqh.top();
    pqh.pop();

    auto it = upper_bound(counts.begin(), counts.end(), -ki);
    if (it == counts.end()) counts.push_back(-1);
    else (*it)--;
  }

  cout << counts.size();
}
