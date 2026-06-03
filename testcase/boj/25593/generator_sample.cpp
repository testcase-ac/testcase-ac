#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string workerName(int index) {
    string name;
    do {
        name.push_back(char('a' + index % 26));
        index /= 26;
    } while (index > 0);
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int hours[4] = {4, 6, 4, 10};
    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 6);

    vector<string> workers;
    int workerCount = rnd.next(1, 12);
    if (mode == 4) {
        n = rnd.next(3, 5);
        workerCount = rnd.next(80, 100);
    } else if (mode == 1) {
        workerCount = rnd.next(4, 10);
    } else if (mode == 2) {
        workerCount = rnd.next(2, 8);
    }

    for (int i = 0; i < workerCount; ++i) {
        workers.push_back(workerName(i));
    }
    shuffle(workers.begin(), workers.end());

    vector<vector<vector<string>>> schedule(n, vector<vector<string>>(4, vector<string>(7, "-")));
    if (mode != 0) {
        vector<int> totals(workerCount, 0);
        int serial = 0;

        for (int week = 0; week < n; ++week) {
            for (int day = 0; day < 7; ++day) {
                bool filled = true;
                if (mode == 3) {
                    filled = rnd.next(0, 99) < 70;
                } else if (mode == 4) {
                    filled = serial < workerCount || rnd.next(0, 99) < 65;
                }

                if (!filled) {
                    continue;
                }

                for (int shift = 0; shift < 4; ++shift) {
                    int who = 0;
                    if (mode == 1) {
                        who = (serial + shift + day) % workerCount;
                    } else if (mode == 2 && rnd.next(0, 99) < 65) {
                        who = 0;
                    } else if (mode == 4 && serial < workerCount) {
                        who = serial;
                    } else {
                        int best = rnd.next(0, workerCount - 1);
                        for (int tries = 0; tries < 3; ++tries) {
                            int candidate = rnd.next(0, workerCount - 1);
                            if (totals[candidate] < totals[best]) {
                                best = candidate;
                            }
                        }
                        who = best;
                    }

                    schedule[week][shift][day] = workers[who];
                    totals[who] += hours[shift];
                    ++serial;
                }
            }
        }
    }

    println(n);
    for (int week = 0; week < n; ++week) {
        for (int shift = 0; shift < 4; ++shift) {
            println(schedule[week][shift]);
        }
    }

    return 0;
}
