#include "combo.h"
#include <vector>

std::string guess_sequence(int N) {
  // What is the first letter?
  std::string S(1, 'A');
  if (press("AB") > 0) {
    if (press("A") > 0) S[0] = 'A';
    else S[0] = 'B';
  }
  else {
    if (press("X") > 0) S[0] = 'X';
    else S[0] = 'Y';
  }
  if (N == 1) return S;

  std::vector<char> C;
  for (char c : std::string("ABXY")) {
    if (c != S[0]) C.push_back(c);
  }

  // Check remaining letters in one pass
  for (int i = 2; i <= N - 1; i++) {
    std::string Q = "";
    for (int j = 0; j < 3; j++) {
      std::string Q1 = S + C[0] + C[j];
      Q += Q1;
    }
    Q += S + C[1];

    int res = press(Q);
    if (res == i + 1) S += C[0];
    if (res == i + 0) S += C[1];
    if (res == i - 1) S += C[2];
  }

  if (press(S + C[0] + S + C[1]) == N) {
    if (press(S + C[0]) == N) S += C[0];
    else S += C[1];
  }
  else S += C[2];

  return S;
}
