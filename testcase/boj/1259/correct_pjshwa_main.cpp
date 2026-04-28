#include <iostream>
#include <string>
using namespace std;

int main() {
  int sz;
  string s;

  while (1) {
    cin >> s;
    if (s == "0") break;

    sz = s.size();
    bool palindrome = true;
    for (int i = 0; i < sz / 2 + 1; i++) {
      if (s[i] != s[sz - 1 - i]) {
        palindrome = false;
        break;
      }
    }

    cout << (palindrome ? "yes\n" : "no\n");
  }
}
