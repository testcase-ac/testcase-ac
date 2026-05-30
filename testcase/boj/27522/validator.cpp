#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int parseTime(const string& value) {
    int minute = value[0] - '0';
    int second = (value[2] - '0') * 10 + (value[3] - '0');
    int millisecond = (value[5] - '0') * 100 + (value[6] - '0') * 10 + (value[7] - '0');
    return (minute * 60 + second) * 1000 + millisecond;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<int> seenTimes;
    int redCount = 0;
    int blueCount = 0;

    for (int i = 0; i < 8; i++) {
        string time = inf.readToken("[0-9]:[0-5][0-9]:[0-9][0-9][0-9]", "time");
        int total = parseTime(time);
        ensuref(total >= 1, "finish time must be at least 0:00:001");
        ensuref(seenTimes.insert(total).second, "finish times must be distinct");

        inf.readSpace();

        char team = inf.readToken("[RB]", "team")[0];
        if (team == 'R') {
            redCount++;
        } else {
            blueCount++;
        }

        inf.readEoln();
    }

    ensuref(redCount == 4, "there must be exactly 4 red racers");
    ensuref(blueCount == 4, "there must be exactly 4 blue racers");

    inf.readEof();
}
