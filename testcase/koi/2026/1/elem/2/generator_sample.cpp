#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int mode = rnd.next(0, 3);
    string cards = "SRP";
    shuffle(cards.begin(), cards.end());

    string a;
    for (int i = 0; i < n; ++i) {
        if (mode == 0) a += cards[0];
        if (mode == 1) a += cards[i % 2];
        if (mode == 2) a += cards[i * 3 / n];
        if (mode == 3) a += cards[rnd.next(0, 2)];
    }

    println(n);
    println(a);
}
