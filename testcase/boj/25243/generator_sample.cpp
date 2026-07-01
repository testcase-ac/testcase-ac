#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string formatTime(int minutes) {
    minutes %= 24 * 60;
    stringstream out;
    out << setfill('0') << setw(2) << minutes / 60 << ':' << setw(2) << minutes % 60;
    return out.str();
}

vector<int> uniqueSortedTimes(int count, int low, int high) {
    set<int> chosen;
    while ((int)chosen.size() < count) {
        chosen.insert(rnd.next(low, high));
    }
    return vector<int>(chosen.begin(), chosen.end());
}

vector<int> denseTimes(int count, int base, int maxStep) {
    vector<int> times;
    times.push_back(base);
    for (int i = 1; i < count; ++i) {
        times.push_back(times.back() + rnd.next(1, maxStep));
    }
    return times;
}

vector<int> trainNumbers(int count, int first) {
    vector<int> numbers;
    for (int i = 0; i < count; ++i) {
        numbers.push_back(first + 2 * i);
    }
    return numbers;
}

void printDirection(const vector<int>& numbers, const vector<int>& times) {
    for (int i = 0; i < (int)numbers.size(); ++i) {
        cout << numbers[i] << ' ' << formatTime(times[i]) << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int c;
    int h;
    vector<int> downTimes;
    vector<int> upTimes;

    if (mode == 0) {
        c = rnd.next(1, 4);
        h = rnd.next(1, 4);
        int shared = rnd.next(5 * 60, 21 * 60);
        downTimes = denseTimes(c, shared, 12);
        upTimes = denseTimes(h, shared, 12);
    } else if (mode == 1) {
        c = rnd.next(6, 14);
        h = rnd.next(6, 14);
        int base = rnd.next(0, 60);
        downTimes = denseTimes(c, base, 4);
        upTimes = denseTimes(h, base + rnd.next(0, 3), 4);
    } else if (mode == 2) {
        c = rnd.next(1, 6);
        h = rnd.next(1, 6);
        int latestStart = 23 * 60 + 59 - max(c, h);
        int base = rnd.next(22 * 60, latestStart);
        downTimes = denseTimes(c, base, 1);
        upTimes = denseTimes(h, base + rnd.next(0, 1), 1);
    } else if (mode == 3) {
        c = 20;
        h = 20;
        downTimes = denseTimes(c, rnd.next(0, 30), rnd.next(3, 8));
        upTimes = denseTimes(h, downTimes[0] + rnd.next(0, 2), rnd.next(3, 8));
    } else {
        c = rnd.next(1, 20);
        h = rnd.next(1, 20);
        downTimes = uniqueSortedTimes(c, 0, 23 * 60 + 59);
        upTimes = uniqueSortedTimes(h, 0, 23 * 60 + 59);
    }

    vector<int> downNumbers = trainNumbers(c, 701);
    vector<int> upNumbers = trainNumbers(h, 702);

    cout << c << ' ' << h << '\n';
    printDirection(downNumbers, downTimes);
    printDirection(upNumbers, upTimes);

    return 0;
}
