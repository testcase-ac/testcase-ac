#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int T, K, Ki;
  long long A, B, S;
  cin >> T;

  priority_queue<long long> pq;
  while (T--) {
    cin >> K;
    for (int i = 0; i < K; i++) {
      cin >> Ki;
      pq.push(-Ki);
    }

    S = 0;
    while (1) {
      A = -pq.top(); pq.pop();
      B = -pq.top(); pq.pop();
      S += (A + B);
      if (pq.empty()) break;

      pq.push(-(A + B));
    }

    cout << S << '\n';
  }
}
