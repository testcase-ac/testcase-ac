#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string makeName(int contest, int team, int style) {
    static const vector<string> base = {
        "Alpha", "bravo Squad", "Charlie 7", "delta Force", "Echo Team",
        "Foxtrot", "Gamma Rays", "hotel crew", "India", "Juliet Club"};

    string name = base[(team + style) % static_cast<int>(base.size())];
    if (style == 1 && team % 3 == 0) {
        name += " " + to_string(contest);
    } else if (style == 2 && team % 4 == 0) {
        name = "Team " + to_string(contest) + " " + to_string(team + 1);
    } else if (style == 3 && team % 2 == 0) {
        name = string(1, static_cast<char>('A' + (team % 26))) + " mixed Case";
    }
    return name;
}

vector<int> solvedMaskForMode(int mode, int p, int team) {
    vector<int> solved(p, 0);
    if (mode == 0) {
        for (int i = 0; i < p; ++i) {
            solved[i] = rnd.next(0, 1);
        }
    } else if (mode == 1) {
        int target = team % (p + 1);
        vector<int> order(p);
        for (int i = 0; i < p; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < target; ++i) {
            solved[order[i]] = 1;
        }
    } else if (mode == 2) {
        for (int i = 0; i < p; ++i) {
            solved[i] = ((i + team) % 3 == 0);
        }
    } else {
        int target = rnd.next(0, p);
        vector<int> order(p);
        for (int i = 0; i < p; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < target; ++i) {
            solved[order[i]] = 1;
        }
    }
    return solved;
}

string makeRecord(bool solved, int problem, int team, int mode) {
    int submissions = solved ? rnd.next(1, 8) : rnd.next(0, 5);
    if (!solved && rnd.next(0, 3) == 0) {
        submissions = 0;
    }

    if (!solved) {
        return to_string(submissions) + "/-";
    }

    int time;
    if (mode == 0) {
        time = rnd.next(0, 300);
    } else if (mode == 1) {
        time = (team * 17 + problem * 13 + rnd.next(0, 20)) % 301;
    } else if (mode == 2) {
        time = rnd.any(vector<int>{0, 1, 59, 60, 119, 180, 299, 300});
    } else {
        time = rnd.next(0, 1000);
    }
    return to_string(submissions) + "/" + to_string(time);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int contests = rnd.next(1, 4);
    for (int contest = 1; contest <= contests; ++contest) {
        int mode = rnd.next(0, 3);
        int p = rnd.next(1, 8);
        int t = rnd.next(1, 12);

        println(p);

        vector<int> points(p);
        for (int i = 0; i < p; ++i) {
            if (mode == 1) {
                points[i] = rnd.any(vector<int>{1, 2, 3, 5, 10});
            } else if (mode == 2) {
                points[i] = (i % 2 == 0) ? rnd.next(1, 4) : rnd.next(5, 20);
            } else {
                points[i] = rnd.next(1, 50);
            }
        }
        println(points);
        println(t);

        int nameStyle = rnd.next(0, 3);
        for (int team = 0; team < t; ++team) {
            vector<int> solved = solvedMaskForMode(mode, p, team);
            string line = makeName(contest, team, nameStyle);
            for (int problem = 0; problem < p; ++problem) {
                line += ",";
                line += makeRecord(solved[problem] != 0, problem, team, mode);
            }
            println(line);
        }
    }

    println(0);
    return 0;
}
