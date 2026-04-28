#include <iostream>
#include <queue>
#include <tuple>

#define ll long long
using namespace std;

ll a, b;
queue<pair<ll, ll> > bfs;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  cin >> a >> b;
  bfs.push({ a, 1 });

  ll v, cnt;
  bool found = false;
  while (!bfs.empty()) {
    tie(v, cnt) = bfs.front();
    bfs.pop();

    if (v == b) {
      found = true;
      break;
    }
    else if (v > b) continue;

    bfs.push({ v * 10 + 1, cnt + 1 });
    bfs.push({ v << 1, cnt + 1 });
  }
  
  cout << (found ? cnt : -1) << '\n';
  
  return 0;
}
