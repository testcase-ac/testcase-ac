#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    vector<string> days;
};

Answer readAnswer(InStream& stream) {
    vector<string> days(7);
    for (int day = 0; day < 7; ++day) {
        days[day] = stream.readToken("[AB]+", format("day[%d]", day + 1).c_str());
        if ((int)days[day].size() != n) {
            stream.quitf(_wa,
                         "day %d has length %d, expected %d",
                         day + 1,
                         (int)days[day].size(),
                         n);
        }

        bool hasA = false;
        bool hasB = false;
        for (char team : days[day]) {
            hasA = hasA || team == 'A';
            hasB = hasB || team == 'B';
        }
        if (!hasA || !hasB) {
            stream.quitf(_wa, "day %d does not contain both teams", day + 1);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after seven days");
    }

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            bool separated = false;
            for (int day = 0; day < 7; ++day) {
                if (days[day][first] != days[day][second]) {
                    separated = true;
                    break;
                }
            }
            if (!separated) {
                stream.quitf(_wa,
                             "monkeys %d and %d are never on opposite teams",
                             first + 1,
                             second + 1);
            }
        }
    }

    return {days};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid schedule for %d monkeys", n);
}
