#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;

    list<char> ls;
    list<char>::iterator lsi = ls.begin();

    int sz = s.size();
    for (int i = 0; i < sz; i++) {
      if (s[i] == '<') {
        if (lsi != ls.begin()) lsi--;
      }
      else if (s[i] == '>') {
        if (lsi != ls.end()) lsi++;
      }
      else if (s[i] == '-') {
        if (lsi != ls.begin()) {
          lsi--;
          ls.erase(lsi++);
        }
      }
      else ls.insert(lsi, s[i]);
    }

    lsi = ls.begin();
    while (lsi != ls.end()) cout << *(lsi++);
    cout << '\n';
  }
}
