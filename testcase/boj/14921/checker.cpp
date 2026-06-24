#include "testlib.h"
#include <cstdlib>
using namespace std;

struct Answer {
    long long value;
    long long objective;
};

Answer readAnswer(InStream& stream) {
    long long value = stream.readLong(-200000000LL, 200000000LL, "B");
    stream.readEoln();
    stream.readEof();
    return {value, llabs(value)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.objective > jury.objective) {
        quitf(_wa,
              "participant answer is farther from zero: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }

    if (participant.objective < jury.objective) {
        quitf(_fail,
              "participant answer is closer to zero than jury answer: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }

    quitf(_ok, "answer has optimal absolute value %lld", participant.objective);
}
