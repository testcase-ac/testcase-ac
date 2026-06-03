#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string initials(int index, int style) {
    string result;

    if (style == 0) {
        result += char('A' + (index % 26));
    } else if (style == 1) {
        result += char('A' + (index % 26));
        result += char('A' + ((index / 26) % 26));
    } else {
        int value = index;
        for (int i = 0; i < 3; ++i) {
            result += char('A' + (value % 26));
            value /= 26;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 4) + 1;
    } else if (mode == 2) {
        n = 2 * rnd.next(3, 10) + 1;
    } else {
        n = 2 * rnd.next(5, 25) + 1;
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    int nameStyle = rnd.next(0, 2);
    int stepPattern = rnd.next(0, 4);
    int baseStep = rnd.next(1, 99);

    println(n);
    for (int i = 0; i < n; ++i) {
        int x;
        if (stepPattern == 0) {
            x = rnd.next(1, 99);
        } else if (stepPattern == 1) {
            x = 1 + (i % 5);
        } else if (stepPattern == 2) {
            x = baseStep;
        } else if (stepPattern == 3) {
            x = rnd.any(vector<int>{1, 2, 3, 50, 99});
        } else {
            x = 1 + ((i * baseStep + rnd.next(0, 8)) % 99);
        }

        println(initials(order[i], nameStyle), x);
    }

    return 0;
}
