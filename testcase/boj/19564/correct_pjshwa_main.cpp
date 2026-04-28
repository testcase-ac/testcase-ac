#include <iostream>
#include <string>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  string s;
  cin >> s;
  int sz = s.size();
  int cnt = 1;

  for (int i = 0; i < sz - 1; i++) {
    if (s[i] >= s[i + 1]) cnt++;
  }

  cout << cnt << '\n';

}
