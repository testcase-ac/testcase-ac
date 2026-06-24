#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

struct Answer {
    double xAxisVolume;
    double yAxisVolume;
};

Answer readAnswer(InStream& stream, TResult extraOutcome) {
    Answer result;
    result.xAxisVolume = stream.readDouble();
    result.yAxisVolume = stream.readDouble();
    if (!stream.seekEof()) {
        quitf(extraOutcome, "extra output after two volume values");
    }
    return result;
}

void compareValue(const char* name, double jury, double participant) {
    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "%s differs - expected: '%.10f', found: '%.10f', error = '%.10f'",
              name, jury, participant, doubleDelta(jury, participant));
    }
}

int main(int argc, char* argv[]) {
    setName("compare two volume values, max absolute or relative error = %.10f", EPS);
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    compareValue("x-axis volume", jury.xAxisVolume, participant.xAxisVolume);
    compareValue("y-axis volume", jury.yAxisVolume, participant.yAxisVolume);

    quitf(_ok, "volumes are within tolerance");
}
