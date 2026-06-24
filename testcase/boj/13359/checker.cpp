#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readProbability(InStream& stream, const char* name) {
  double value = stream.readDouble(0.0, 1.0, name);
  if (!stream.seekEof()) {
    stream.quitf(_wa, "extra output after %s", name);
  }
  return value;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  double jury = readProbability(ans, "jury probability");
  double participant = readProbability(ouf, "participant probability");

  double error = fabs(participant - jury);
  if (error > EPS) {
    quitf(_wa, "expected %.12f, found %.12f, absolute error %.12f",
          jury, participant, error);
  }

  quitf(_ok, "answer %.12f is within absolute error %.12f", participant, EPS);
}
