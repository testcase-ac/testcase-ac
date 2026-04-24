#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Rod {
    vector<int> children;
    int lasers;
};

string build(int u, const vector<Rod>& rods) {
    vector<string> parts;
    for (int v : rods[u].children) {
        parts.push_back(build(v, rods));
    }
    for (int i = 0; i < rods[u].lasers; i++) {
        parts.push_back("()");
    }
    shuffle(parts.begin(), parts.end());
    string res = "(";
    for (auto &t : parts) res += t;
    res += ")";
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of rods (nested intervals)
    int R = rnd.next(1, 5);
    vector<Rod> rods(R+1);

    // sample max lasers per rod for diversity
    int maxL = rnd.next(1, 4);
    for (int i = 1; i <= R; i++) {
        rods[i].lasers = rnd.next(1, maxL);
    }

    // build a random tree: rod 1 is root (outermost)
    for (int i = 2; i <= R; i++) {
        int p = rnd.next(1, i-1);
        rods[p].children.push_back(i);
    }

    // generate the parentheses string
    string s = build(1, rods);

    // output
    printf("%s\n", s.c_str());
    return 0;
}
