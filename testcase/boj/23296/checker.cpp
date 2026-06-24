#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<int> dest;

struct Answer {
    int count;
};

Answer readAnswer(InStream& stream) {
    int count = stream.readInt(0, 2 * n, "button count");

    vector<int> sequence(count);
    for (int i = 0; i < count; ++i) {
        sequence[i] = stream.readInt(1, n, format("button[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after button sequence");
    }

    vector<char> delivered(n + 1, false);
    int deliveredCount = 0;
    int current = 1;
    for (int i = 0; i < count; ++i) {
        int next = sequence[i];
        if (!delivered[current] && dest[current] == next) {
            delivered[current] = true;
            ++deliveredCount;
        }
        current = next;
    }

    if (deliveredCount != n) {
        for (int floor = 1; floor <= n; ++floor) {
            if (!delivered[floor]) {
                stream.quitf(_wa, "person on floor %d is not delivered", floor);
            }
        }
    }

    return {count};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    dest.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        dest[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count > jury.count) {
        quitf(_wa,
              "participant uses more button presses than jury: participant=%d jury=%d",
              participant.count,
              jury.count);
    }
    if (participant.count < jury.count) {
        quitf(_fail,
              "participant found a shorter valid sequence: participant=%d jury=%d",
              participant.count,
              jury.count);
    }

    quitf(_ok, "button count %d", participant.count);
}
