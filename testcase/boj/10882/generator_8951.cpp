#include "testlib.h"
using namespace std;

string offsetToString(int step) {
    string s = "UTC";
    if (step >= 0) {
        s += "+";
    } else {
        s += "-";
        step = -step;
    }
    int hour = step / 2;
    int half = step % 2;
    s += to_string(hour);
    if (half) s += ".5";
    return s;
}

string formatTime(int h, int m) {
    string res;
    if (h < 10) res += '0';
    res += to_string(h);
    res += ':';
    if (m < 10) res += '0';
    res += to_string(m);
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias towards small but sometimes larger
    int modeN = rnd.next(0, 3);
    int N;
    if (modeN == 0) N = 1;
    else if (modeN == 1) N = rnd.next(2, 5);
    else if (modeN == 2) N = rnd.next(6, 15);
    else N = rnd.next(16, 50);

    // Choose YJ's timezone offset (in half-hour steps, from -24 to 24)
    vector<int> interestingY = {0, 18, -10, 17, -17, 24, -24, 1, -1, 23, -23};
    int yjStep;
    if (rnd.next(0, 1) == 0) yjStep = rnd.any(interestingY);
    else yjStep = rnd.next(-24, 24);

    // Choose YJ's local meeting time
    int H, M;
    int modeT = rnd.next(0, 4);
    if (modeT == 0) {          // midnight
        H = 0; M = 0;
    } else if (modeT == 1) {   // last minute of day
        H = 23; M = 59;
    } else if (modeT == 2) {   // noon
        H = 12; M = 0;
    } else if (modeT == 3) {   // near wrap with half-hour relevance
        H = 23; M = 30;
    } else {                   // random, with bias to interesting minutes
        H = rnd.next(0, 23);
        if (rnd.next(0, 1) == 0) {
            vector<int> cand = {0, 15, 30, 45, 59};
            M = rnd.any(cand);
        } else {
            M = rnd.next(0, 59);
        }
    }

    // Generate coworker time zones
    vector<int> coworkers;
    if (N >= 1) coworkers.push_back(yjStep); // at least one same as YJ

    if (N >= 2) { // ensure at least one half-hour zone
        vector<int> halfSteps;
        for (int s = -24; s <= 24; ++s)
            if (abs(s) % 2 == 1)
                halfSteps.push_back(s);
        int half = rnd.any(halfSteps);
        coworkers.push_back(half);
    }

    if (N >= 3) coworkers.push_back(-24); // UTC-12
    if (N >= 4) coworkers.push_back(24);  // UTC+12

    while ((int)coworkers.size() < N) {
        coworkers.push_back(rnd.next(-24, 24));
    }

    shuffle(coworkers.begin(), coworkers.end());

    // Output
    println(N);
    string yjTimeStr = formatTime(H, M);
    string yjOffsetStr = offsetToString(yjStep);
    println(yjTimeStr, yjOffsetStr);
    for (int s : coworkers)
        println(offsetToString(s));

    return 0;
}
