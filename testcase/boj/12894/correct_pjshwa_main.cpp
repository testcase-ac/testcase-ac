#include <iostream>
#include <string>
using namespace std;

string smallest(string s) {
  int sz = s.size();
  if (sz % 2 == 1) return s;
  string s1 = smallest(s.substr(0, sz / 2));
  string s2 = smallest(s.substr(sz / 2));
  if (s1 < s2) return s1 + s2;
  else return s2 + s1;
}

// bool equivalent(string a, string b) {
//   int sz = a.size();
//   if (sz % 2 == 1) return a == b;
//   else {
//     string a1 = a.substr(0, sz / 2);
//     string a2 = a.substr(sz / 2);
//     string b1 = b.substr(0, sz / 2);
//     string b2 = b.substr(sz / 2);

//     // T(n) = 4T(n / 2) + O(n), O(n^2) => TLE
//     // Should make at most 2 recursive calls to be O(n logn).
//     return (equivalent(a1, b1) && equivalent(a2, b2)) || (equivalent(a1, b2) && equivalent(a2, b1));
//   }
// }

int main() {
  string a, b;
  cin >> a >> b;
  cout << (smallest(a) == smallest(b) ? "YES\n" : "NO\n");
}
