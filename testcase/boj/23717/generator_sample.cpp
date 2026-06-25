#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char colorFromMask(int mask) {
    static const string colorByMask = "URYOBPGA";
    return colorByMask[mask];
}

string randomFromAlphabet(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string blockyString(int n, const string& alphabet) {
    string s;
    while ((int)s.size() < n) {
        char c = rnd.any(alphabet);
        int len = rnd.next(1, min(6, n - (int)s.size()));
        s.append(len, c);
    }
    return s;
}

string alternatingString(int n) {
    string a = rnd.any(vector<string>{"RY", "RB", "YB", "OA", "PG", "GU", "URYBOPGA"});
    string s;
    s.reserve(n);
    int offset = rnd.next((int)a.size());
    for (int i = 0; i < n; ++i) {
        s.push_back(a[(i + offset) % (int)a.size()]);
    }
    return s;
}

string simulatedStrokes(int n) {
    vector<int> mask(n, 0);
    int strokes = rnd.next(1, min(12, 3 * n));
    for (int i = 0; i < strokes; ++i) {
        int color = 1 << rnd.next(3);
        int l = rnd.next(n);
        int r = rnd.next(l, n - 1);
        for (int j = l; j <= r; ++j) {
            mask[j] |= color;
        }
    }

    string s;
    s.reserve(n);
    for (int value : mask) {
        s.push_back(colorFromMask(value));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    println(t);

    const string allColors = "URYBOPGA";
    const string primaryAndGreen = "YBG";
    const string composites = "OPGA";

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 28);
        string p;

        if (mode == 0) {
            p = randomFromAlphabet(n, allColors);
        } else if (mode == 1) {
            p = blockyString(n, rnd.next(2) == 0 ? primaryAndGreen : allColors);
        } else if (mode == 2) {
            p = alternatingString(n);
        } else if (mode == 3) {
            p = simulatedStrokes(n);
        } else {
            p = randomFromAlphabet(n, composites);
        }

        println(n);
        println(p);
    }

    return 0;
}
