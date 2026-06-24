#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct Output {
    long long distance;
};

int noteValue(const string& note) {
    int base = -1;
    if (note[0] == 'C') base = 0;
    if (note[0] == 'D') base = 2;
    if (note[0] == 'E') base = 4;
    if (note[0] == 'F') base = 5;
    if (note[0] == 'G') base = 7;
    if (note[0] == 'A') base = 9;
    if (note[0] == 'B') base = 11;
    int octave = note[1] - '0';
    int value = octave * 12 + base;
    if (note.size() == 3) {
        ++value;
    }
    return value;
}

Output readOutput(InStream& stream, int n, int initialLeft, int initialRight, const vector<int>& notes) {
    long long claimed = stream.readLong(0, 1000000000000000000LL, "total distance");
    stream.readEoln();

    int left = initialLeft;
    int right = initialRight;
    long long actual = 0;

    for (int i = 0; i < n; ++i) {
        int hand = stream.readInt(1, 2, format("hand[%d]", i + 1).c_str());
        int note = notes[i];
        if (hand == 1) {
            actual += abs(left - note);
            left = note;
        } else {
            actual += abs(right - note);
            right = note;
        }
    }

    stream.readEoln();
    stream.readEof();

    if (claimed != actual) {
        stream.quitf(_wa, "claimed distance %lld does not match sequence distance %lld", claimed, actual);
    }

    return {claimed};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int initialLeft = noteValue(inf.readToken());
    int initialRight = noteValue(inf.readToken());
    int n = inf.readInt();
    vector<int> notes(n);
    for (int i = 0; i < n; ++i) {
        notes[i] = noteValue(inf.readToken());
    }

    Output jury = readOutput(ans, n, initialLeft, initialRight, notes);
    Output participant = readOutput(ouf, n, initialLeft, initialRight, notes);

    if (participant.distance < jury.distance) {
        quitf(_fail, "participant found better answer: jury=%lld participant=%lld", jury.distance, participant.distance);
    }
    if (participant.distance > jury.distance) {
        quitf(_wa, "jury has better answer: jury=%lld participant=%lld", jury.distance, participant.distance);
    }

    quitf(_ok, "answer=%lld", participant.distance);
}
