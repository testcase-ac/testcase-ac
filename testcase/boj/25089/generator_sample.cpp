#include "testlib.h"
#include <algorithm>
#include <array>
#include <numeric>
#include <vector>
using namespace std;

using Printer = array<int, 4>;
using Case = array<Printer, 3>;

const int LIMIT = 1000000;

vector<int> splitTotal(int total) {
    vector<int> cuts;
    for (int i = 0; i < 3; ++i) cuts.push_back(rnd.next(0, total));
    sort(cuts.begin(), cuts.end());

    vector<int> parts;
    parts.push_back(cuts[0]);
    parts.push_back(cuts[1] - cuts[0]);
    parts.push_back(cuts[2] - cuts[1]);
    parts.push_back(total - cuts[2]);
    shuffle(parts.begin(), parts.end());
    return parts;
}

Case fromCommonCaps(const vector<int>& caps, int slackMax) {
    Case tc;
    for (int printer = 0; printer < 3; ++printer) {
        for (int color = 0; color < 4; ++color) {
            int slack = rnd.next(0, slackMax);
            tc[printer][color] = min(LIMIT, caps[color] + slack);
        }
    }
    return tc;
}

Case makeCase(int mode) {
    if (mode == 0) {
        return Case{Printer{0, 0, 0, 0}, Printer{0, 0, 0, 0}, Printer{0, 0, 0, 0}};
    }

    if (mode == 1) {
        vector<int> caps = splitTotal(LIMIT);
        return fromCommonCaps(caps, 0);
    }

    if (mode == 2) {
        vector<int> caps = splitTotal(rnd.next(max(0, LIMIT - 20), LIMIT - 1));
        return fromCommonCaps(caps, rnd.next(0, 50));
    }

    if (mode == 3) {
        Case tc;
        for (int printer = 0; printer < 3; ++printer) {
            for (int color = 0; color < 4; ++color) {
                tc[printer][color] = rnd.next(700000, LIMIT);
            }
        }
        return tc;
    }

    if (mode == 4) {
        vector<int> caps = splitTotal(rnd.next(LIMIT, LIMIT + 200000));
        for (int& x : caps) x = min(x, LIMIT);
        return fromCommonCaps(caps, rnd.next(0, 200000));
    }

    Case tc;
    vector<int> base = splitTotal(rnd.next(LIMIT - 1000, LIMIT + 1000));
    for (int& x : base) x = min(x, LIMIT);

    for (int printer = 0; printer < 3; ++printer) {
        for (int color = 0; color < 4; ++color) {
            int value = min(LIMIT, base[color] + rnd.next(0, 300000));
            if (color == printer % 4) value = rnd.next(0, value);
            tc[printer][color] = value;
        }
    }
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 12);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        Case printers = makeCase(mode);
        for (const Printer& printer : printers) {
            println(printer[0], printer[1], printer[2], printer[3]);
        }
    }

    return 0;
}
