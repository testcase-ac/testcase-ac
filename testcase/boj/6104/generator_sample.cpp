#include "testlib.h"
#include <vector>

using namespace std;

int ratingWithResidue(int residue, int f) {
    int maxK = (100000 - residue) / f;
    if (residue == 0) {
        return f * rnd.next(1, 100000 / f);
    }
    return residue + f * rnd.next(0, maxK);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int f;
    vector<int> ratings;

    if (mode == 0) {
        n = rnd.next(1, 8);
        f = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            ratings.push_back(rnd.next(1, 30));
        }
    } else if (mode == 1) {
        f = rnd.next(2, 25);
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            int residue = (i % 2 == 0 ? 0 : rnd.next(1, f - 1));
            ratings.push_back(ratingWithResidue(residue, f));
        }
    } else if (mode == 2) {
        f = rnd.next(2, 50);
        n = rnd.next(3, 30);
        int a = rnd.next(1, f - 1);
        int b = f - a;
        for (int i = 0; i < n; ++i) {
            int residue = (i % 3 == 0 ? a : (i % 3 == 1 ? b : rnd.next(0, f - 1)));
            ratings.push_back(ratingWithResidue(residue, f));
        }
    } else if (mode == 3) {
        f = rnd.next(20, 1000);
        n = rnd.next(15, 55);
        int limitedResidues = rnd.next(1, min(f, 8));
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(0, limitedResidues - 1);
            ratings.push_back(ratingWithResidue(residue, f));
        }
    } else if (mode == 4) {
        f = rnd.next(900, 1000);
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            ratings.push_back(rnd.next(99900, 100000));
        }
    } else {
        f = 1;
        n = rnd.next(1, 35);
        for (int i = 0; i < n; ++i) {
            ratings.push_back(rnd.next(1, 100000));
        }
    }

    shuffle(ratings.begin(), ratings.end());

    println(n, f);
    for (int rating : ratings) {
        println(rating);
    }

    return 0;
}
