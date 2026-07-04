#include "testlib.h"

#include <array>
#include <vector>
using namespace std;

using Triple = array<int, 3>;

Triple shuffledTriple(int a, int b, int c) {
    Triple triple = {a, b, c};
    shuffle(triple.begin(), triple.end());
    return triple;
}

Triple equilateral() {
    int side = rnd.next(1, 1000);
    return Triple{side, side, side};
}

Triple isosceles() {
    int equalSide = rnd.next(2, 1000);
    int other = rnd.next(1, 1000);
    while (other == equalSide || 2 * min(equalSide, other) <= max(equalSide, other)) {
        other = rnd.next(1, 1000);
    }
    return shuffledTriple(equalSide, equalSide, other);
}

Triple scalene() {
    int a = rnd.next(1, 998);
    int b = rnd.next(a + 1, 999);
    int cLo = b + 1;
    int cHi = min(1000, a + b - 1);
    if (cLo > cHi) return scalene();
    return shuffledTriple(a, b, rnd.next(cLo, cHi));
}

Triple invalid() {
    int a = rnd.next(1, 500);
    int b = rnd.next(1, 500);
    int c = rnd.next(min(1000, a + b), 1000);
    return shuffledTriple(a, b, c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Triple> triples;
    int mode = rnd.next(0, 4);
    int n = rnd.next(6, 18);

    triples.push_back(Triple{1000, 1000, 1000});
    triples.push_back(shuffledTriple(1, 1, 2));
    triples.push_back(shuffledTriple(499, 500, 999));
    triples.push_back(shuffledTriple(998, 999, 1000));

    for (int i = 0; i < n; ++i) {
        int kind = (mode + i + rnd.next(0, 3)) % 4;
        if (kind == 0) {
            triples.push_back(equilateral());
        } else if (kind == 1) {
            triples.push_back(isosceles());
        } else if (kind == 2) {
            triples.push_back(scalene());
        } else {
            triples.push_back(invalid());
        }
    }

    shuffle(triples.begin(), triples.end());
    for (const Triple& triple : triples) {
        println(triple[0], triple[1], triple[2]);
    }
    println(0, 0, 0);

    return 0;
}
