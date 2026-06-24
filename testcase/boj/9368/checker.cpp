#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

vector<double> readOutput(InStream& stream, int testCount) {
  vector<double> values;
  values.reserve(testCount);

  for (int tc = 1; tc <= testCount; ++tc) {
    values.push_back(stream.readReal(0.0, 1.0, format("answer[%d]", tc)));
  }

  if (!stream.seekEof()) {
    stream.quitf(_wa, "extra output after %d answers", testCount);
  }

  return values;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int testCount = inf.readInt();
  vector<double> jury = readOutput(ans, testCount);
  vector<double> participant = readOutput(ouf, testCount);

  for (int tc = 0; tc < testCount; ++tc) {
    if (!doubleCompare(jury[tc], participant[tc], EPS)) {
      quitf(_wa,
            "test case %d: expected %.12f, found %.12f, error %.12f",
            tc + 1,
            jury[tc],
            participant[tc],
            doubleDelta(jury[tc], participant[tc]));
    }
  }

  quitf(_ok, "%d answers are within tolerance", testCount);
}
