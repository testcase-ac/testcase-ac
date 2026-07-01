#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string repeatChar(char c, int count) {
    return string(count, c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string groups = "ABC";
    int mode = rnd.next(0, 5);
    string seats;

    if (mode == 0) {
        seats = repeatChar(rnd.any(groups), rnd.next(1, 40));
    } else if (mode == 1) {
        vector<char> order(groups.begin(), groups.end());
        shuffle(order.begin(), order.end());

        for (char c : order) {
            int len = rnd.next(0, 15);
            if (len > 0) seats += repeatChar(c, len);
        }
        if (seats.empty()) seats = repeatChar(rnd.any(groups), rnd.next(1, 5));
    } else if (mode == 2) {
        int n = rnd.next(2, 60);
        int offset = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            seats += groups[(i + offset) % 3];
        }
    } else if (mode == 3) {
        vector<char> order(groups.begin(), groups.end());
        shuffle(order.begin(), order.end());

        for (char c : order) {
            int len = rnd.next(1, 12);
            for (int i = 0; i < len; ++i) {
                if (rnd.next(0, 99) < 25) {
                    seats += rnd.any(groups);
                } else {
                    seats += c;
                }
            }
        }
    } else {
        int n = rnd.next(1, 60);
        int maxGroup = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            seats += groups[rnd.next(0, maxGroup)];
        }
    }

    if (rnd.next(0, 1) == 1) {
        rotate(seats.begin(), seats.begin() + rnd.next(0, static_cast<int>(seats.size()) - 1), seats.end());
    }

    println(seats);
    return 0;
}
