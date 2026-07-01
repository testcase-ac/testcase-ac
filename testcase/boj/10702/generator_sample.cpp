#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string formationString(const vector<int>& counts) {
    return toString(counts[0]) + "-" + toString(counts[1]) + "-" + toString(counts[2]);
}

vector<int> randomFormation(int mode) {
    if (mode == 0) {
        int line = rnd.next(0, 2);
        vector<int> counts(3, 0);
        counts[line] = 10;
        return counts;
    }

    if (mode == 1) {
        int first = rnd.next(0, 10);
        int second = rnd.next(0, 10 - first);
        vector<int> counts = {first, second, 10 - first - second};
        shuffle(counts.begin(), counts.end());
        return counts;
    }

    int a = rnd.next(1, 8);
    int b = rnd.next(1, 9 - a);
    vector<int> counts = {a, b, 10 - a - b};
    shuffle(counts.begin(), counts.end());
    return counts;
}

string randomLineSet(int mode) {
    static const vector<string> specialists = {"O", "V", "N"};
    static const vector<string> pairs = {"OV", "VO", "ON", "NO", "VN", "NV"};
    static const vector<string> triples = {"OVN", "ONV", "VON", "VNO", "NOV", "NVO"};

    if (mode == 0) return rnd.any(specialists);
    if (mode == 1) return rnd.next(0, 3) == 0 ? rnd.any(specialists) : rnd.any(pairs);
    if (mode == 2) return rnd.next(0, 3) == 0 ? rnd.any(triples) : rnd.any(pairs);
    return rnd.next(0, 4) == 0 ? rnd.any(triples) : rnd.any(specialists);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int formationMode = rnd.next(0, 2);
    int n = rnd.next(1, 10);
    int m = rnd.next(10, 22);

    println(n);
    for (int i = 0; i < n; ++i) {
        println(formationString(randomFormation((formationMode + i) % 3)));
    }

    println(m);
    for (int i = 0; i < m; ++i) {
        println(randomLineSet(mode));
    }

    return 0;
}
