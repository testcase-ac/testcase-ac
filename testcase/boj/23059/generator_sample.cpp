#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string makeName(int index) {
    string s;
    do {
        s.push_back(char('a' + index % 26));
        index /= 26;
    } while (index > 0);
    reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int itemCount = rnd.next(2, 12);
    vector<string> names;
    for (int i = 0; i < itemCount; ++i) {
        names.push_back(makeName(i));
    }

    vector<pair<string, string>> edges;

    if (mode == 0) {
        for (int i = 0; i + 1 < itemCount; ++i) {
            edges.emplace_back(names[i], names[i + 1]);
        }
    } else if (mode == 1) {
        for (int i = 0; i < itemCount; ++i) {
            for (int j = i + 1; j < itemCount; ++j) {
                if (rnd.next() < 0.35) {
                    edges.emplace_back(names[i], names[j]);
                }
            }
        }
        if (edges.empty()) {
            edges.emplace_back(names[0], names[1]);
        }
    } else if (mode == 2) {
        int center = rnd.next(0, itemCount - 1);
        for (int i = 0; i < itemCount; ++i) {
            if (i != center) {
                edges.emplace_back(names[center], names[i]);
            }
        }
    } else if (mode == 3) {
        int cycleSize = rnd.next(2, itemCount);
        for (int i = 0; i < cycleSize; ++i) {
            edges.emplace_back(names[i], names[(i + 1) % cycleSize]);
        }
        for (int i = cycleSize; i < itemCount; ++i) {
            edges.emplace_back(names[rnd.next(0, i - 1)], names[i]);
        }
    } else {
        int base = rnd.next(1, min(5, itemCount - 1));
        for (int i = 0; i < base; ++i) {
            edges.emplace_back(names[i], names[i + 1]);
        }
        int extra = rnd.next(1, 6);
        for (int i = 0; i < extra; ++i) {
            edges.push_back(rnd.any(edges));
        }
    }

    shuffle(edges.begin(), edges.end());

    println((int)edges.size());
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
