#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of strings
    vector<int> possibleN = {1, 3, 5, 10, 20};
    int N = rnd.any(possibleN);

    // Edge lengths to force boundary cases
    vector<int> edgeLens = {1, 5, 6, 9, 10, 20};

    println(N);
    for (int i = 0; i < N; i++) {
        int l;
        // 20% chance to pick a boundary length, else uniform
        if (rnd.next(0, 4) == 0) {
            l = rnd.any(edgeLens);
        } else {
            l = rnd.next(1, 20);
        }
        string s;
        s.reserve(l);
        for (int j = 0; j < l; j++) {
            int kind = rnd.next(0, 2);
            if (kind == 0) {
                // digit
                s.push_back(char('0' + rnd.next(0, 9)));
            } else if (kind == 1) {
                // lowercase
                s.push_back(char('a' + rnd.next(0, 25)));
            } else {
                // uppercase
                s.push_back(char('A' + rnd.next(0, 25)));
            }
        }
        println(s);
    }
    return 0;
}
