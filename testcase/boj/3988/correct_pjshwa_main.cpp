#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int v[1'000'000];
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v, v + n);

  int ws = n - k;
  int mv = 1e9;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < ws - 2; i++) pq.push({abs(v[i] - v[i + 1]), i});

  for (int i = ws - 1; i < n; i++) {
    pq.push({abs(v[i] - v[i - 1]), i - 1});
    while (pq.top().second <= i - ws) pq.pop();
    mv = min(mv, pq.top().first + abs(v[i] - v[i - ws + 1]));
  }
  cout << mv << '\n';
}
