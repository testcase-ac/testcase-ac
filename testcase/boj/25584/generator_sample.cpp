#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

const array<int, 4> SHIFT_HOURS = {4, 6, 4, 10};

using Week = array<array<string, 7>, 4>;

vector<string> makeNames(int count) {
    vector<string> names;
    for (int i = 0; i < count; ++i) {
        string name;
        int x = i;
        do {
            name.push_back(char('a' + x % 26));
            x /= 26;
        } while (x > 0);
        names.push_back(name);
    }
    return names;
}

Week emptyWeek() {
    Week week;
    for (int shift = 0; shift < 4; ++shift) {
        for (int day = 0; day < 7; ++day) {
            week[shift][day] = "-";
        }
    }
    return week;
}

void printWeek(const Week& week) {
    for (int shift = 0; shift < 4; ++shift) {
        for (int day = 0; day < 7; ++day) {
            if (day > 0) {
                cout << ' ';
            }
            cout << week[shift][day];
        }
        cout << '\n';
    }
}

int pickWorkerByLightShift(const vector<string>& names) {
    int shift = rnd.next(0, 2);
    if (shift == 2) {
        shift = 0;
    }
    return shift % int(names.size());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 12 : 6);
    int workerCount = rnd.next(1, mode == 3 ? 18 : 10);
    if (mode == 1) {
        workerCount = rnd.next(4, 8);
    } else if (mode == 2) {
        workerCount = rnd.next(2, 5);
    }

    vector<string> names = makeNames(workerCount);

    cout << n << '\n';
    for (int weekIndex = 0; weekIndex < n; ++weekIndex) {
        Week week = emptyWeek();

        if (mode == 0) {
            int activeDays = rnd.next(0, 3);
            vector<int> days = {0, 1, 2, 3, 4, 5, 6};
            shuffle(days.begin(), days.end());
            for (int i = 0; i < activeDays; ++i) {
                int day = days[i];
                for (int shift = 0; shift < 4; ++shift) {
                    week[shift][day] = names[rnd.next(workerCount)];
                }
            }
        } else if (mode == 1) {
            int offset = rnd.next(workerCount);
            for (int day = 0; day < 7; ++day) {
                if (rnd.next(0, 9) == 0) {
                    continue;
                }
                for (int shift = 0; shift < 4; ++shift) {
                    week[shift][day] = names[(offset + weekIndex + day + shift) % workerCount];
                }
            }
        } else if (mode == 2) {
            string heavy = names[rnd.next(workerCount)];
            for (int day = 0; day < 7; ++day) {
                if (rnd.next(0, 4) == 0) {
                    continue;
                }
                week[3][day] = heavy;
                for (int shift = 0; shift < 3; ++shift) {
                    if (rnd.next(0, 2) == 0) {
                        week[shift][day] = heavy;
                    } else {
                        week[shift][day] = names[pickWorkerByLightShift(names)];
                    }
                }
            }
        } else if (mode == 3) {
            for (int day = 0; day < 7; ++day) {
                if (rnd.next(0, 1) == 0) {
                    continue;
                }
                for (int shift = 0; shift < 4; ++shift) {
                    week[shift][day] = names[rnd.wnext(workerCount, -1)];
                }
            }
        } else {
            int activeDays = rnd.next(1, 7);
            for (int day = 0; day < activeDays; ++day) {
                int base = (weekIndex * 7 + day) % workerCount;
                for (int shift = 0; shift < 4; ++shift) {
                    int worker = (base + shift + rnd.next(0, 1)) % workerCount;
                    week[shift][day] = names[worker];
                }
            }
        }

        printWeek(week);
    }

    return 0;
}
