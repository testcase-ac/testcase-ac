#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> makeNames(int n) {
    vector<string> names;
    for (char c = 'A'; c <= 'Z' && (int)names.size() < n; ++c) {
        names.push_back(string(1, c));
    }
    for (char c = 'a'; c <= 'z' && (int)names.size() < n; ++c) {
        names.push_back(string(1, c));
    }
    for (char a = 'A'; a <= 'Z' && (int)names.size() < n; ++a) {
        for (char b = 'a'; b <= 'z' && (int)names.size() < n; ++b) {
            names.push_back(string(1, a) + string(1, b));
        }
    }
    return names;
}

vector<string> makeSamChart(vector<string> chart, int mode) {
    int n = chart.size();

    if (mode == 0) {
        return chart;
    }
    if (mode == 1) {
        reverse(chart.begin(), chart.end());
        return chart;
    }
    if (mode == 2) {
        rotate(chart.begin(), chart.begin() + rnd.next(n), chart.end());
        return chart;
    }
    if (mode == 3) {
        for (int i = rnd.next(2); i + 1 < n; i += 2) {
            swap(chart[i], chart[i + 1]);
        }
        return chart;
    }
    if (mode == 4) {
        int l = rnd.next(n);
        int r = rnd.next(l, n - 1);
        reverse(chart.begin() + l, chart.begin() + r + 1);
        return chart;
    }

    shuffle(chart.begin(), chart.end());
    return chart;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 8);
    for (int tc = 0; tc < cases; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (rnd.next(100) < 75) {
            n = rnd.next(2, 12);
        } else {
            n = rnd.next(13, 40);
        }

        vector<string> frodo = makeNames(n);
        shuffle(frodo.begin(), frodo.end());

        int mode = (tc < 6 ? tc : rnd.next(0, 5));
        vector<string> sam = makeSamChart(frodo, mode);

        println(n);
        println(frodo);
        println(sam);
    }

    println(0);
    return 0;
}
