#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

char randomLiteral(int trueWeight) {
    return rnd.next(1, 100) <= trueWeight ? 'T' : 'F';
}

string makeExpr(int depth, int maxDepth, int trueWeight, int branchBias) {
    if (depth >= maxDepth) {
        return string(1, randomLiteral(trueWeight));
    }

    int children;
    if (rnd.next(1, 100) <= branchBias) {
        children = rnd.next(3, 7);
    } else {
        children = rnd.next(1, 3);
    }

    string result = "(";
    for (int i = 0; i < children; ++i) {
        bool forceSubtree = i == 0 && depth + 1 < maxDepth;
        bool useSubtree = forceSubtree || rnd.next(1, 100) <= 45;
        if (useSubtree) {
            result += makeExpr(depth + 1, maxDepth, trueWeight, branchBias);
        } else {
            result += randomLiteral(trueWeight);
        }
    }
    result += ")";
    return result;
}

string makeFlatCase(int n, int trueWeight) {
    string result = "(";
    for (int i = 0; i < n; ++i) {
        result += randomLiteral(trueWeight);
    }
    result += ")";
    return result;
}

string makeChainCase(int depth, int trueWeight) {
    string result;
    for (int i = 0; i < depth; ++i) {
        result += "(";
    }
    result += randomLiteral(trueWeight);
    for (int i = 0; i < depth; ++i) {
        result += ")";
    }
    return result;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 9);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 4);
        int trueWeight = rnd.next(15, 85);

        if (mode == 0) {
            println(makeFlatCase(rnd.next(1, 12), trueWeight));
        } else if (mode == 1) {
            println(makeChainCase(rnd.next(1, 9), trueWeight));
        } else {
            int maxDepth = rnd.next(2, mode == 2 ? 4 : 7);
            int branchBias = mode == 3 ? rnd.next(45, 85) : rnd.next(10, 45);
            println(makeExpr(0, maxDepth, trueWeight, branchBias));
        }
    }

    println("()");
    return 0;
}
