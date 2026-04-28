#include <bits/stdc++.h>
using namespace std;
 
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool isPalindrome(string s) {
  int sz = s.size();
  if (sz <= 1) return true;
  else return s[0] == s[sz - 1] && isPalindrome(s.substr(1, sz - 2));
}

int main(){
  fast_io();
 
  string s;
  cin >> s;
  int sz = s.size();

  for (int i = 0; i < sz; i++) {
    if (isPalindrome(s.substr(i))) {
      cout << sz + i;
      break;
    }
  }
}
