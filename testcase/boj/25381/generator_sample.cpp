#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char weightedChar(const vector<pair<char, int>>& weights) {
    int total = 0;
    for (const auto& entry : weights) total += entry.second;

    int pick = rnd.next(1, total);
    for (const auto& entry : weights) {
        pick -= entry.second;
        if (pick <= 0) return entry.first;
    }
    return weights.back().first;
}

string randomString(int n, const vector<pair<char, int>>& weights) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += weightedChar(weights);
    return s;
}

string repeatedBlocks(int n) {
    vector<string> blocks = {"A", "B", "C", "AB", "BC", "ABC", "CBA", "AABB", "BBCC"};
    string s;
    while ((int)s.size() < n) s += rnd.any(blocks);
    s.resize(n);
    return s;
}

string alternatingPattern(int n) {
    vector<string> patterns = {"AB", "BC", "AC", "ABC", "CBA", "ABB", "BBC"};
    string pattern = rnd.any(patterns);
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += pattern[i % pattern.size()];
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(250, 500);
    } else {
        n = rnd.next(1, 30);
    }

    string s;
    if (mode == 0) {
        s = randomString(n, {{'A', 1}, {'B', 1}, {'C', 1}});
    } else if (mode == 1) {
        s = randomString(n, {{'A', 4}, {'B', 2}, {'C', 1}});
    } else if (mode == 2) {
        s = randomString(n, {{'A', 1}, {'B', 4}, {'C', 2}});
    } else if (mode == 3) {
        s = randomString(n, {{'A', 1}, {'B', 3}});
    } else if (mode == 4) {
        s = repeatedBlocks(n);
    } else if (mode == 5) {
        s = alternatingPattern(n);
    } else {
        int a = rnd.next(0, n);
        int b = rnd.next(0, n - a);
        int c = n - a - b;
        s = string(a, 'A') + string(b, 'B') + string(c, 'C');
        if (rnd.next(0, 1)) reverse(s.begin(), s.end());
    }

    println(s);
    return 0;
}
