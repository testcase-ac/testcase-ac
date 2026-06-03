#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

string rangeItem(int low, int high) {
    if (low == high && rnd.next(0, 3) == 0) {
        return to_string(low);
    }
    return to_string(low) + "-" + to_string(high);
}

string singlePage(int page) {
    return to_string(page);
}

string joinRanges(const vector<string>& items) {
    string line;
    for (int i = 0; i < (int)items.size(); ++i) {
        if (i > 0) {
            line += ',';
        }
        line += items[i];
    }
    return line;
}

int nearbyPage(int n) {
    int upper = max(n + 30, 30);
    if (rnd.next(0, 4) == 0) {
        return rnd.next(n + 1, upper);
    }
    return rnd.next(1, upper);
}

string randomExpression(int n, int mode) {
    vector<string> items;
    int count = rnd.next(4, 14);

    if (mode == 0) {
        int center = rnd.next(1, n);
        for (int i = 0; i < count; ++i) {
            int low = max(1, center - rnd.next(0, 8));
            int high = min(n + rnd.next(0, 12), center + rnd.next(0, 10));
            items.push_back(rangeItem(low, high));
        }
    } else if (mode == 1) {
        for (int i = 0; i < count; ++i) {
            int high = rnd.next(1, max(n, 1) + 25);
            int low = high + rnd.next(1, 20);
            items.push_back(rangeItem(low, high));
        }
        items.push_back(singlePage(rnd.next(1, n)));
    } else if (mode == 2) {
        for (int i = 0; i < count; ++i) {
            int low = rnd.next(1, max(1, n - 3));
            int high = rnd.next(n, n + 60);
            items.push_back(rangeItem(low, high));
        }
    } else {
        int base = rnd.next(1, n);
        for (int i = 0; i < count; ++i) {
            if (rnd.next(0, 1) == 0) {
                items.push_back(singlePage(base));
            } else {
                int low = nearbyPage(n);
                int high = nearbyPage(n);
                if (rnd.next(0, 2) != 0 && low > high) {
                    swap(low, high);
                }
                items.push_back(rangeItem(low, high));
            }
        }
    }

    shuffle(items.begin(), items.end());
    string line = joinRanges(items);
    while ((int)line.size() > 1000) {
        items.pop_back();
        line = joinRanges(items);
    }
    return line;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(3, 8);
    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(0, 3);
        int n;
        if (tc == 0) {
            n = rnd.next(1, 5);
        } else if (tc == 1) {
            n = rnd.next(950, 1000);
        } else {
            n = rnd.next(1, 1000);
        }

        println(n);
        println(randomExpression(n, mode));
    }
    println(0);

    return 0;
}
