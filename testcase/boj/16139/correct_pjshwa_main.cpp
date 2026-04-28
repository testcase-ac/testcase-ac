#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int arr[26][200001];
int main() {
  fast_io();

  string s;
  cin >> s;

  int cp, sz = s.size();
  for (char c = 'a'; c <= 'z'; c++) {
    cp = 0;
    for (int i = 0; i < sz; i++) {
      if (s[i] == c) cp++;
      arr[c - 'a'][i] = cp;
    }
  }

  int n, li, ri;
  char qc;

  cin >> n;
  while (n--) {
    cin >> qc >> li >> ri;
    if (li) cout << arr[qc - 'a'][ri] - arr[qc - 'a'][li - 1];
    else cout << arr[qc - 'a'][ri];
    cout << '\n';
  }
}
