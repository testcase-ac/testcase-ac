#include <iostream>
#include <algorithm>
using namespace std;

struct N
{
  int x, y;
  bool operator<(const N rhs) const {
    return y == rhs.y ? x < rhs.x : y < rhs.y;
  }
} pairs[100000];

int main(){
  int n, x, y;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    pairs[i].x = x;
    pairs[i].y = y;
  }

  sort(pairs, pairs + n);

  for (int i = 0; i < n; i++) {
    cout << pairs[i].x << ' ' << pairs[i].y << '\n';
  }
}
