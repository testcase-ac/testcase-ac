#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<vector<int>> available;

struct Answer {
    int count;
    vector<int> schedule;
};

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(0, n, "count");

    vector<int> schedule(5);
    int selected = 0;
    for (int i = 0; i < 5; ++i) {
        schedule[i] = stream.readInt(0, 1, format("schedule[%d]", i + 1).c_str());
        selected += schedule[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after schedule");
    }

    if (selected != 2) {
        stream.quitf(_wa, "schedule must select exactly 2 days, found %d", selected);
    }

    int actual = 0;
    for (int student = 0; student < n; ++student) {
        bool canAttend = true;
        for (int day = 0; day < 5; ++day) {
            if (schedule[day] && !available[student][day]) {
                canAttend = false;
                break;
            }
        }
        if (canAttend) {
            ++actual;
        }
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed count %d does not match schedule count %d", claimed, actual);
    }

    return {actual, schedule};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    available.assign(n, vector<int>(5));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) {
            available[i][j] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count < jury.count) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d", jury.count, participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d", jury.count, participant.count);
    }

    quitf(_ok, "answer=%d", participant.count);
}
