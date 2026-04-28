#include <bits/stdc++.h>
using namespace std;
 
int main(){
  int w1, h1, w2, h2, w3, h3;
  cin >> w1 >> h1 >> w2 >> h2 >> w3 >> h3;

  int answer = 0;
  if (
    h1 == h2 && h2 == h3 && w1 + w2 + w3 == h1 ||
    w1 == h2 && h2 == h3 && h1 + w2 + w3 == w1 ||
    h1 == w2 && w2 == h3 && w1 + h2 + w3 == h1 ||
    w1 == w2 && w2 == h3 && h1 + h2 + w3 == w1 ||
    h1 == h2 && h2 == w3 && w1 + w2 + h3 == h1 ||
    w1 == h2 && h2 == w3 && h1 + w2 + h3 == w1 ||
    h1 == w2 && w2 == w3 && w1 + h2 + h3 == h1 ||
    w1 == w2 && w2 == w3 && h1 + h2 + h3 == w1 ||
    h1 == h2 + h3 && w2 == w3 && w1 + w2 == h1 ||
    w1 == h2 + h3 && w2 == w3 && h1 + w2 == w1 ||
    h1 == w2 + h3 && h2 == w3 && w1 + h2 == h1 ||
    w1 == w2 + h3 && h2 == w3 && h1 + h2 == w1 ||
    h1 == h2 + w3 && w2 == h3 && w1 + w2 == h1 ||
    w1 == h2 + w3 && w2 == h3 && h1 + w2 == w1 ||
    h1 == w2 + w3 && h2 == h3 && w1 + h2 == h1 ||
    w1 == w2 + w3 && h2 == h3 && h1 + h2 == w1 ||
    h3 == h2 + h1 && w2 == w1 && w3 + w2 == h3 ||
    w3 == h2 + h1 && w2 == w1 && h3 + w2 == w3 ||
    h3 == w2 + h1 && h2 == w1 && w3 + h2 == h3 ||
    w3 == w2 + h1 && h2 == w1 && h3 + h2 == w3 ||
    h3 == h2 + w1 && w2 == h1 && w3 + w2 == h3 ||
    w3 == h2 + w1 && w2 == h1 && h3 + w2 == w3 ||
    h3 == w2 + w1 && h2 == h1 && w3 + h2 == h3 ||
    w3 == w2 + w1 && h2 == h1 && h3 + h2 == w3 ||
    h2 == h1 + h3 && w1 == w3 && w2 + w1 == h2 ||
    w2 == h1 + h3 && w1 == w3 && h2 + w1 == w2 ||
    h2 == w1 + h3 && h1 == w3 && w2 + h1 == h2 ||
    w2 == w1 + h3 && h1 == w3 && h2 + h1 == w2 ||
    h2 == h1 + w3 && w1 == h3 && w2 + w1 == h2 ||
    w2 == h1 + w3 && w1 == h3 && h2 + w1 == w2 ||
    h2 == w1 + w3 && h1 == h3 && w2 + h1 == h2 ||
    w2 == w1 + w3 && h1 == h3 && h2 + h1 == w2
  ) answer = 1;

  cout << answer << '\n';
}
