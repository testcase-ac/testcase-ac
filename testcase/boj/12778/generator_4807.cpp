#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: between 1 and 10
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Problem type: C for char->num, N for num->char
        char tp = rnd.next(0, 1) == 0 ? 'C' : 'N';
        // Number of items: between 1 and 10
        int M = rnd.next(1, 10);
        println(M, tp);
        vector<string> items;
        items.reserve(M);
        for (int i = 0; i < M; i++) {
            double r = rnd.next();
            if (tp == 'C') {
                // generate a letter
                int x;
                if (r < 0.2) {
                    // bias to early alphabet
                    x = rnd.next(0, 2);
                } else if (r < 0.4) {
                    // bias to late alphabet
                    x = rnd.next(23, 25);
                } else {
                    // uniform
                    x = rnd.next(0, 25);
                }
                char c = char('A' + x);
                items.push_back(string(1, c));
            } else {
                // generate a number 1..26
                int num;
                if (r < 0.2) {
                    num = rnd.next(1, 3);
                } else if (r < 0.4) {
                    num = rnd.next(24, 26);
                } else {
                    num = rnd.next(1, 26);
                }
                items.push_back(to_string(num));
            }
        }
        // print items on one line
        println(items);
    }
    return 0;
}
