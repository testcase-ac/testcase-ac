#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 0.50001;

int readDifficulty(InStream& stream) {
    int value = stream.readInt(0, 30, "difficulty");
    stream.readEoln();
    stream.readEof();
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int jury = readDifficulty(ans);
    int participant = readDifficulty(ouf);

    if (abs(participant - jury) > EPS) {
        quitf(_wa, "expected %d, found %d, difference %.5f exceeds %.5f",
              jury, participant, static_cast<double>(abs(participant - jury)),
              EPS);
    }

    quitf(_ok, "answer %d is within tolerance of jury answer %d", participant,
          jury);
}
