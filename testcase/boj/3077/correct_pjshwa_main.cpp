#include <bits/stdc++.h>
using namespace std;

string answers[2500];
int main() {
  int n;
  cin >> n;

  string war;
  map<string, int> wars;
  for (int i = 0; i < n; i++) {
    cin >> war;
    wars[war] = i;
  }

  int corrects = 0;
  for (int i = 0; i < n; i++) cin >> answers[i];
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (wars[answers[i]] < wars[answers[j]]) corrects++;
    }
  }
    
  cout << corrects << '/' << n * (n - 1) / 2 << '\n';
}
