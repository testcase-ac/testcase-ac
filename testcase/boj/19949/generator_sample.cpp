#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> answer(10);
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int value = rnd.next(1, 5);
        for (int& x : answer) x = value;
    } else if (mode == 1) {
        int first = rnd.next(1, 5);
        int second = rnd.next(1, 5);
        while (second == first) second = rnd.next(1, 5);
        for (int i = 0; i < 10; ++i) answer[i] = (i % 2 == 0 ? first : second);
    } else if (mode == 2) {
        int start = rnd.next(1, 5);
        int step = rnd.next(1, 4);
        for (int i = 0; i < 10; ++i) answer[i] = (start + i * step - 1) % 5 + 1;
    } else if (mode == 3) {
        int blocks = rnd.next(2, 5);
        int at = 0;
        for (int b = 0; b < blocks; ++b) {
            int remaining = 10 - at;
            int len = (b + 1 == blocks) ? remaining : rnd.next(1, remaining - (blocks - b - 1));
            int value = rnd.next(1, 5);
            for (int i = 0; i < len; ++i) answer[at++] = value;
        }
    } else {
        for (int& x : answer) x = rnd.next(1, 5);
    }

    println(answer);
    return 0;
}
