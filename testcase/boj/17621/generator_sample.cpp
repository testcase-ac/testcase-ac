#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Block {
    int a;
    int b;
};

bool compatible(const Block& left, const Block& right, int n) {
    if (left.a == 0 || right.a == 0) return true;
    bool overlap = max(left.a, right.a) <= min(left.b, right.b);
    return (!overlap || (left.b == n) == (right.b == n)) &&
           left.b + 1 != right.a && right.b + 1 != left.a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    println(n, m);

    Block previous{0, 0};
    for (int column = 0; column < m; ++column) {
        vector<Block> candidates{{0, 0}};
        for (int a = 1; a <= n; ++a)
            for (int b = a; b <= n; ++b)
                if (compatible(previous, {a, b}, n))
                    candidates.push_back({a, b});

        Block current = rnd.any(candidates);
        println(current.a, current.b);
        previous = current;
    }
}
