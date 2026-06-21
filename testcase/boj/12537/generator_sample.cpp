#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string segment(int length, char color) {
    return to_string(length) + color;
}

vector<string> makeCase(int mode) {
    vector<string> segments;

    if (mode == 0) {
        int count = rnd.next(1, 8);
        char color = rnd.any(string("BR"));
        for (int i = 0; i < count; ++i) {
            segments.push_back(segment(rnd.next(1, 100), color));
        }
    } else if (mode == 1) {
        int pairs = rnd.next(1, 6);
        for (int i = 0; i < pairs; ++i) {
            segments.push_back(segment(rnd.next(1, 100), 'B'));
            segments.push_back(segment(rnd.next(1, 100), 'R'));
        }
    } else if (mode == 2) {
        int blue = rnd.next(1, 4);
        int red = rnd.next(blue + 1, blue + 8);
        if (rnd.next(2) == 0) {
            swap(blue, red);
        }
        for (int i = 0; i < blue; ++i) {
            segments.push_back(segment(rnd.next(1, 100), 'B'));
        }
        for (int i = 0; i < red; ++i) {
            segments.push_back(segment(rnd.next(1, 100), 'R'));
        }
    } else if (mode == 3) {
        int count = rnd.next(2, 10);
        for (int i = 0; i < count; ++i) {
            int length = rnd.next(100) < 60 ? 1 : rnd.next(2, 5);
            char color = i % 2 == 0 ? 'B' : 'R';
            segments.push_back(segment(length, color));
        }
    } else {
        int count = rnd.next(12, 30);
        int low = rnd.next(1, 40);
        int high = rnd.next(low, 100);
        for (int i = 0; i < count; ++i) {
            char color = rnd.next(100) < 45 ? 'B' : 'R';
            segments.push_back(segment(rnd.next(low, high), color));
        }
    }

    shuffle(segments.begin(), segments.end());
    return segments;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = 5;
    println(testCases);
    for (int t = 0; t < testCases; ++t) {
        vector<string> segments = makeCase(t);
        println(static_cast<int>(segments.size()));
        println(segments);
    }

    return 0;
}
