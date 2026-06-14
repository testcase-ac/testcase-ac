#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeAlternating(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += alphabet[i % int(alphabet.size())];
    return s;
}

string makeBlocks(const vector<int>& counts, const string& colors) {
    string s;
    for (int i = 0; i < int(colors.size()); ++i) {
        s += string(counts[i], colors[i]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 8);
        string colors = "RGY";
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += rnd.any(colors);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        string colors = rnd.next(2) == 0 ? "RG" : "GY";
        s = makeAlternating(n, colors);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        string colors = "RGY";
        shuffle(colors.begin(), colors.end());
        s = makeAlternating(n, colors);
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        int dominant = rnd.next((n + 1) / 2, n);
        string colors = "RGY";
        shuffle(colors.begin(), colors.end());
        vector<int> counts(3);
        counts[0] = dominant;
        int rest = n - dominant;
        counts[1] = rnd.next(0, rest);
        counts[2] = rest - counts[1];
        s = makeBlocks(counts, colors);
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        string colors = "RGY";
        shuffle(colors.begin(), colors.end());
        vector<int> counts(3, n / 3);
        for (int i = 0; i < n % 3; ++i) ++counts[i];
        s = makeBlocks(counts, colors);
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        string colors = "RGY";
        vector<int> counts(3);
        counts[0] = rnd.next(0, n);
        counts[1] = rnd.next(0, n - counts[0]);
        counts[2] = n - counts[0] - counts[1];
        shuffle(colors.begin(), colors.end());
        s = makeBlocks(counts, colors);
        shuffle(s.begin(), s.end());
    } else if (mode == 6) {
        n = rnd.next(31, 120);
        string colors = "RGY";
        s.reserve(n);
        char last = 0;
        for (int i = 0; i < n; ++i) {
            char c = rnd.any(colors);
            if (rnd.next(0, 99) < 70 && last != 0) c = last;
            s += c;
            last = c;
        }
    } else {
        n = 400;
        string colors = "RGY";
        shuffle(colors.begin(), colors.end());
        vector<int> counts = {rnd.next(150, 220), rnd.next(80, 140), 0};
        counts[2] = n - counts[0] - counts[1];
        s = makeBlocks(counts, colors);
        if (rnd.next(2) == 0) shuffle(s.begin(), s.end());
    }

    println(n);
    println(s);
    return 0;
}
