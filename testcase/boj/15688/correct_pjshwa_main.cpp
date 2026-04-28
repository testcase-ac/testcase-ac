#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, s;
  cin >> n;
  priority_queue<int, vector<int>, greater<int>> pq;

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    cin >> s;
    pq.push(s);
  }

  for (int i = 0; i < n; i++) {
    cout << pq.top() << '\n';
    pq.pop();
  }

}
