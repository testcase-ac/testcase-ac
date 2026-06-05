#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

const int MIN_MONTH = 0;
const int MAX_MONTH = (9999 - 2000) * 12 + 11;

string formatMonth(int monthIndex) {
    int year = 2000 + monthIndex / 12;
    int month = monthIndex % 12 + 1;
    string result = to_string(year) + "-";
    if (month < 10) result += "0";
    result += to_string(month);
    return result;
}

pair<int, int> randomInterval(int lo, int hi) {
    int start = rnd.next(lo, hi);
    int end = rnd.next(start, hi);
    return {start, end};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> intervals;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        int center = rnd.next(MIN_MONTH, MAX_MONTH);
        for (int i = 0; i < n; ++i) {
            int start = max(MIN_MONTH, center - rnd.next(0, 24));
            int end = min(MAX_MONTH, center + rnd.next(0, 24));
            intervals.push_back({start, end});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        int base = rnd.next(MIN_MONTH, MAX_MONTH);
        for (int i = 0; i < n; ++i) {
            int shift = rnd.next(-6, 6);
            int month = min(MAX_MONTH, max(MIN_MONTH, base + shift));
            intervals.push_back({month, month});
        }
    } else if (mode == 2) {
        int n = rnd.next(4, 30);
        int startBase = rnd.next(MIN_MONTH, MAX_MONTH - 120);
        for (int i = 0; i < n; ++i) {
            int start = min(MAX_MONTH, startBase + i * rnd.next(0, 3));
            int length = rnd.next(0, 60);
            intervals.push_back({start, min(MAX_MONTH, start + length)});
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 18);
        intervals.push_back({MIN_MONTH, MIN_MONTH});
        intervals.push_back({MAX_MONTH, MAX_MONTH});
        intervals.push_back({MIN_MONTH, MAX_MONTH});
        while ((int)intervals.size() < n) {
            int side = rnd.next(0, 1);
            int lo = side == 0 ? MIN_MONTH : max(MIN_MONTH, MAX_MONTH - 120);
            int hi = side == 0 ? min(MAX_MONTH, MIN_MONTH + 120) : MAX_MONTH;
            intervals.push_back(randomInterval(lo, hi));
        }
    } else if (mode == 4) {
        int n = rnd.next(6, 24);
        int a = rnd.next(MIN_MONTH, MAX_MONTH - 240);
        int b = a + rnd.next(12, 120);
        for (int i = 0; i < n; ++i) {
            int anchor = i % 2 == 0 ? a : b;
            int start = max(MIN_MONTH, anchor - rnd.next(0, 8));
            int end = min(MAX_MONTH, anchor + rnd.next(0, 8));
            intervals.push_back({start, end});
        }
    } else {
        int n = rnd.next(10, 60);
        int lo = rnd.next(MIN_MONTH, MAX_MONTH - 360);
        int hi = lo + rnd.next(120, 360);
        for (int i = 0; i < n; ++i) {
            intervals.push_back(randomInterval(lo, hi));
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println((int)intervals.size());
    for (auto [start, end] : intervals) {
        println(formatMonth(start), formatMonth(end));
    }

    return 0;
}
