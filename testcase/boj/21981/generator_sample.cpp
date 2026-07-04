#include "testlib.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const int kDay = 24 * 60 * 60;

string formatTime(int seconds) {
    seconds %= kDay;
    if (seconds < 0) {
        seconds += kDay;
    }

    int hour = seconds / 3600;
    int minute = seconds / 60 % 60;
    int second = seconds % 60;

    stringstream out;
    out << setw(2) << setfill('0') << hour << ':'
        << setw(2) << setfill('0') << minute << ':'
        << setw(2) << setfill('0') << second;
    return out.str();
}

long long randomDelta() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return rnd.any(vector<long long>{-1000000000LL, -86400LL, -1LL, 0LL, 1LL, 86400LL, 1000000000LL});
    }
    if (mode == 1) {
        return rnd.next(-20, 20);
    }
    if (mode == 2) {
        return rnd.next(-2000, 2000);
    }
    return rnd.next(-1000000000, 1000000000);
}

void printCase(const vector<int>& times, const vector<long long>& deltas) {
    println((int)times.size());

    for (int i = 0; i < (int)times.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << formatTime(times[i]);
    }
    cout << '\n';

    for (int i = 0; i < (int)deltas.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << deltas[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(4, 8);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        int n = rnd.next(2, 12);
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(20, 60);
        }

        vector<int> times(n);
        vector<long long> deltas(n);
        int mode = rnd.next(0, 5);

        if (mode == 0) {
            long long commonDelta = randomDelta();
            for (int i = 0; i < n; ++i) {
                times[i] = rnd.next(0, kDay - 1);
                deltas[i] = commonDelta;
            }
        } else if (mode == 1) {
            int commonTime = rnd.next(0, kDay - 1);
            for (int i = 0; i < n; ++i) {
                times[i] = commonTime;
                deltas[i] = randomDelta();
            }
        } else if (mode == 2) {
            int syncAfter = rnd.next(0, kDay - 1);
            int syncTime = rnd.next(0, kDay - 1);
            for (int i = 0; i < n; ++i) {
                deltas[i] = randomDelta();
                times[i] = (syncTime - (int)((deltas[i] % kDay) * syncAfter % kDay) + kDay) % kDay;
            }
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) {
                times[i] = (i * (kDay / n) + rnd.next(0, 120)) % kDay;
                deltas[i] = rnd.any(vector<long long>{-1LL, 0LL, 1LL, 2LL, 3600LL, 86400LL});
            }
            shuffle(times.begin(), times.end());
            shuffle(deltas.begin(), deltas.end());
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                int nearMidnight = rnd.any(vector<int>{0, 1, 2, kDay - 3, kDay - 2, kDay - 1});
                times[i] = (nearMidnight + rnd.next(0, 15)) % kDay;
                deltas[i] = randomDelta();
            }
        } else {
            int baseTime = rnd.next(0, kDay - 1);
            long long baseDelta = randomDelta();
            for (int i = 0; i < n; ++i) {
                times[i] = (baseTime + rnd.next(-300, 300) + kDay) % kDay;
                deltas[i] = baseDelta + rnd.next(-5, 5);
                if (deltas[i] < -1000000000LL) {
                    deltas[i] = -1000000000LL;
                }
                if (deltas[i] > 1000000000LL) {
                    deltas[i] = 1000000000LL;
                }
            }
        }

        printCase(times, deltas);
    }

    return 0;
}
