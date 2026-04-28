#include <iostream>
#include <string>
using namespace std;

int main() {
  int sz;
  string s;

  cin >> s;
  sz = s.size();
  bool one_letter = true;

  for (int i = 0; i < sz - 1; i++) {
    if (s[i] != s[i + 1]) one_letter = false;
  }

  if (one_letter) cout << "-1\n";
  else {
    bool palindrome = true;
    for (int i = 0; i < sz / 2 + 1; i++) {
      if (s[i] != s[sz - 1 - i]) {
        palindrome = false;
        break;
      }
    }

    cout << (palindrome ? sz - 1 : sz) << '\n';
  }
}
