#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Segment = pair<long long, int>;

long long randomCount(int mode) {
    if (mode == 0) return rnd.next(1LL, 20LL);
    if (mode == 1) return rnd.next(1LL, 1000000LL);
    return rnd.next(9999999999999900LL, 10000000000000000LL);
}

vector<int> typePool(int maxType, int size) {
    vector<int> types;
    for (int i = 1; i <= maxType; ++i) {
        types.push_back(i);
    }
    shuffle(types.begin(), types.end());
    types.resize(size);
    sort(types.begin(), types.end());
    return types;
}

vector<Segment> makeLine(int length, const vector<int>& preferredTypes, int countMode, int pattern) {
    vector<Segment> line;
    int lastType = -1;

    for (int i = 0; i < length; ++i) {
        int type;
        if (pattern == 0) {
            type = preferredTypes[i % preferredTypes.size()];
        } else if (pattern == 1) {
            type = preferredTypes[(length - 1 - i) % preferredTypes.size()];
        } else if (pattern == 2 && i % 4 == 3) {
            type = rnd.next(1, 100);
        } else {
            type = rnd.any(preferredTypes);
        }

        if (preferredTypes.size() > 1) {
            for (int tries = 0; tries < 8 && type == lastType; ++tries) {
                type = rnd.any(preferredTypes);
            }
        }

        line.push_back({randomCount(countMode), type});
        lastType = type;
    }

    return line;
}

void printLine(const vector<Segment>& line) {
    for (int i = 0; i < (int)line.size(); ++i) {
        if (i) putchar(' ');
        printf("%lld %d", line[i].first, line[i].second);
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(4, 9);
    println(tests);

    for (int tc = 0; tc < tests; ++tc) {
        int n;
        int m;
        if (tc == 0) {
            n = 1;
            m = 1;
        } else if (tc == 1) {
            n = rnd.next(2, 4);
            m = rnd.next(5, 8);
        } else {
            n = rnd.next(1, 12);
            m = rnd.next(1, 12);
        }

        int poolSize = rnd.next(1, min(8, max(n, m) + 2));
        vector<int> types = typePool(100, poolSize);
        int countMode = (tc % 3 == 0 ? 2 : rnd.next(0, 2));
        int patternA = rnd.next(0, 3);
        int patternB = rnd.next(0, 3);

        vector<Segment> boxes = makeLine(n, types, countMode, patternA);
        vector<Segment> toys = makeLine(m, types, countMode, patternB);

        if (tc == 0 && rnd.next(0, 1)) {
            toys[0].second = boxes[0].second == 100 ? 99 : boxes[0].second + 1;
        }
        if (tc == 1 && !types.empty()) {
            for (int i = 0; i < n; ++i) {
                boxes[i].second = types[i % types.size()];
            }
            for (int i = 0; i < m; ++i) {
                toys[i].second = types[(m - 1 - i) % types.size()];
            }
        }

        println(n, m);
        printLine(boxes);
        printLine(toys);
    }

    return 0;
}
