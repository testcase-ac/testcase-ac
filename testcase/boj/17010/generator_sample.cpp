#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const string digits = "0123456789";
    const string punctuation = "!@#$%^&*()-_=+[]{};:',.<>/?|\\";
    const string symbols = letters + digits + punctuation;

    int mode = rnd.next(0, 4);
    int L;
    if (mode == 0) {
        L = 1;
    } else if (mode == 1) {
        L = rnd.next(2, 6);
    } else if (mode == 2) {
        L = rnd.next(7, 20);
    } else {
        L = rnd.next(21, 40);
    }

    vector<int> counts;
    vector<char> chars;
    for (int i = 0; i < L; ++i) {
        int N;
        if (i == 0 && mode == 0) {
            N = rnd.any(vector<int>{1, 79});
        } else if (rnd.next(0, 4) == 0) {
            N = rnd.any(vector<int>{1, 2, 78, 79});
        } else if (mode == 3) {
            N = rnd.next(50, 79);
        } else {
            N = rnd.next(1, 79);
        }

        char symbol;
        if (mode == 1 && i > 0 && rnd.next(0, 2) == 0) {
            symbol = chars.back();
        } else if (mode == 2 && rnd.next(0, 3) == 0) {
            symbol = rnd.any(punctuation);
        } else {
            symbol = rnd.any(symbols);
        }

        counts.push_back(N);
        chars.push_back(symbol);
    }

    println(L);
    for (int i = 0; i < L; ++i) {
        println(counts[i], chars[i]);
    }

    return 0;
}
