#include <iostream>
#include <bitset>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bitset<1 << 25> bs;

int main() {
  fast_io();

  int n;
  while (cin >> n) {
    if (bs[n]) continue;
    cout << n << ' ';
    bs[n] = 1;
  }
}
