#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Segment {
    string type;
    int low;
    int high;
};

pair<int, int> rangeAround(int value, int maxSlack) {
    int left = rnd.next(0, min(value, maxSlack));
    int right = rnd.next(0, min(1000 - value, maxSlack));
    return {value - left, value + right};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(10, 20);
    }

    vector<string> types(n);
    int noneCount = 0;
    for (int i = 0; i < n; ++i) {
        int pick = rnd.next(0, 99);
        if (mode == 0 || pick < 35) {
            types[i] = "none";
            ++noneCount;
        } else if (pick < 68) {
            types[i] = "on";
        } else {
            types[i] = "off";
        }
    }
    if (noneCount == 0) {
        types[rnd.next(n)] = "none";
    }

    int flow = rnd.next(0, mode == 3 ? 35 : 20);
    int slack = rnd.next(0, mode == 4 ? 25 : 8);
    vector<Segment> segments;
    segments.reserve(n);

    for (const string& type : types) {
        if (type == "on") {
            int add = rnd.next(0, mode == 5 ? 50 : 15);
            auto range = rangeAround(add, slack);
            segments.push_back({type, range.first, range.second});
            flow += add;
        } else if (type == "off") {
            int sub = rnd.next(0, min(flow, mode == 5 ? 50 : 15));
            auto range = rangeAround(sub, slack);
            segments.push_back({type, range.first, range.second});
            flow -= sub;
        } else {
            auto range = rangeAround(flow, slack);
            segments.push_back({type, range.first, range.second});
        }
    }

    println(n);
    for (const Segment& segment : segments) {
        println(segment.type, segment.low, segment.high);
    }

    return 0;
}
