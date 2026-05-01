#include "testlib.h"
#include <string>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int maxDepth = rnd.next(1, 5);
        double probWrap = rnd.next();
        auto gen = [&](auto self, int depth) -> string {
            int maxCnt = rnd.wnext(4, 1) + 1; // more weight on smaller counts
            int cnt = rnd.next(1, maxCnt);
            string s;
            for (int i = 0; i < cnt; i++) {
                if (depth < maxDepth && rnd.next() < probWrap) {
                    s += "(" + self(self, depth + 1) + ")";
                } else {
                    s += "()";
                }
            }
            return s;
        };
        string A = gen(gen, 0);
        string B;
        if (rnd.next() < 0.2) {
            B = A; // some equal cases
        } else {
            B = gen(gen, 0);
        }
        println(A);
        println(B);
    }
    return 0;
}
