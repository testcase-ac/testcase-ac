#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) cout << "0 ";
    cout << "1 ";
    for (int j = 0; j < 14; j++) cout << "0 ";
    cout << "0\n";
  }

  for (int j = 0; j < 14; j++) cout << "3375 ";
  cout << "0 ";
  for (int j = 0; j < 14; j++) cout << "15 ";
  cout << "15\n";

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 14; j++) cout << "0 ";
    cout << "225 ";
    for (int j = 0; j < 14; j++) cout << "0 ";
    cout << "0\n";
  }
}
