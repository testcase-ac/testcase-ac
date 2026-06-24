#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int n;
array<int, 3> requiredCount;

struct Claim {
  bool impossible;
  string schedule;
};

int employeeIndex(char c) {
  if (c == 'A') return 0;
  if (c == 'B') return 1;
  if (c == 'C') return 2;
  return -1;
}

Claim readClaim(InStream& stream) {
  string token = stream.readToken("[A-C\\-0-9]+", "answer");
  if (!stream.seekEof()) {
    stream.quitf(_wa, "extra output after answer");
  }

  if (token == "-1") {
    return {true, ""};
  }

  if ((int)token.size() != n) {
    stream.quitf(_wa, "schedule length is %d, expected %d", (int)token.size(), n);
  }

  array<int, 3> count = {0, 0, 0};
  for (int i = 0; i < n; ++i) {
    int idx = employeeIndex(token[i]);
    if (idx == -1) {
      stream.quitf(_wa, "invalid employee '%c' at position %d", token[i], i + 1);
    }
    ++count[idx];

    if (token[i] == 'B' && i > 0 && token[i - 1] == 'B') {
      stream.quitf(_wa, "employee B works on consecutive days ending at position %d", i + 1);
    }
    if (token[i] == 'C') {
      if (i > 0 && token[i - 1] == 'C') {
        stream.quitf(_wa, "employee C works after one rest day violation at position %d", i + 1);
      }
      if (i > 1 && token[i - 2] == 'C') {
        stream.quitf(_wa, "employee C works after two rest day violation at position %d", i + 1);
      }
    }
  }

  for (int i = 0; i < 3; ++i) {
    if (count[i] != requiredCount[i]) {
      stream.quitf(_wa,
                   "employee %c appears %d times, expected %d",
                   char('A' + i),
                   count[i],
                   requiredCount[i]);
    }
  }

  return {false, token};
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  string input = inf.readToken("[ABC]+", "S");
  if (!inf.seekEof()) {
    quitf(_fail, "extra data after input string");
  }

  n = (int)input.size();
  requiredCount = {0, 0, 0};
  for (char c : input) {
    ++requiredCount[employeeIndex(c)];
  }

  Claim jury = readClaim(ans);
  Claim participant = readClaim(ouf);

  if (jury.impossible) {
    if (participant.impossible) {
      quitf(_ok, "both outputs report impossible");
    }
    quitf(_fail, "participant found a valid schedule while jury reports impossible");
  }

  if (participant.impossible) {
    quitf(_wa, "participant reports impossible while jury provides a valid schedule");
  }

  quitf(_ok, "valid schedule");
}
