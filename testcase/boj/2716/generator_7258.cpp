#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string genTree(int n) {
    if (n == 1) return "[]";
    int bias2 = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int leftCount = rnd.wnext(n - 1, bias2) + 1;
    int rightCount = n - 1 - leftCount;
    string l = genTree(leftCount);
    string r = rightCount > 0 ? genTree(rightCount) : "";
    if (rightCount > 0 && rnd.next(0, 1) == 1) swap(l, r);
    return "[" + l + r + "]";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int bias = rnd.any(vector<int>{-2, -1, 0, 1, 2});
        int nodes = rnd.wnext(24, bias) + 1;  // up to 25 nodes, depth ≤25
        string s = genTree(nodes);
        println(s);
    }
    return 0;
}
