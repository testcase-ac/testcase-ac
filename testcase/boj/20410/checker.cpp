#include "testlib.h"

using namespace std;

struct Answer {
    int a;
    int c;
};

int m, seedValue, x1, x2;

bool generatesSequence(const Answer& answer) {
    return (answer.a * seedValue + answer.c) % m == x1 &&
           (answer.a * x1 + answer.c) % m == x2;
}

Answer readAnswer(InStream& stream, TResult invalidResult) {
    int a = stream.readInt(0, m - 1, "a");
    int c = stream.readInt(0, m - 1, "c");
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after a and c");
    }

    Answer answer{a, c};
    if (!generatesSequence(answer)) {
        stream.quitf(invalidResult,
                     "a=%d, c=%d does not generate X_1=%d and X_2=%d",
                     a, c, x1, x2);
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    m = inf.readInt();
    seedValue = inf.readInt();
    x1 = inf.readInt();
    x2 = inf.readInt();

    readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    quitf(_ok, "valid parameters: a=%d, c=%d", participant.a, participant.c);
}
