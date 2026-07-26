#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 10);
    println(testCount);
    for (int test = 0; test < testCount; ++test) {
        int maxLength = rnd.next(1, 24);
        int openPercent = rnd.next(0, 100);
        auto parentheses = [&](int length) {
            string value;
            while (length--)
                value += rnd.next(0, 99) < openPercent ? '(' : ')';
            return value;
        };

        string a = parentheses(rnd.next(1, maxLength));
        string b = rnd.next(4) == 0 ? a : parentheses(rnd.next(1, maxLength));
        println(a, b);
    }
}
