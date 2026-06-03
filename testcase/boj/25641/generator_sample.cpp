#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string makeBalancedSuffix(int pairs, int mode) {
    string suffix;
    suffix.reserve(2 * pairs);

    if (mode == 0) {
        for (int i = 0; i < pairs; ++i) {
            suffix += "st";
        }
    } else if (mode == 1) {
        suffix.append(pairs, 's');
        suffix.append(pairs, 't');
    } else if (mode == 2) {
        suffix.append(pairs, 't');
        suffix.append(pairs, 's');
    } else {
        suffix.append(pairs, 's');
        suffix.append(pairs, 't');
        shuffle(suffix.begin(), suffix.end());
    }

    return suffix;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int suffixPairs;
    int prefixLength;

    if (mode == 0) {
        suffixPairs = 1;
        prefixLength = rnd.next(0, 3);
    } else if (mode == 1) {
        suffixPairs = rnd.next(1, 5);
        prefixLength = 0;
    } else if (mode == 2) {
        suffixPairs = rnd.next(1, 10);
        prefixLength = rnd.next(1, 12);
    } else if (mode == 3) {
        suffixPairs = rnd.next(8, 18);
        prefixLength = rnd.next(0, 20);
    } else if (mode == 4) {
        suffixPairs = rnd.next(20, 49);
        prefixLength = rnd.next(0, 100 - 2 * suffixPairs);
    } else {
        suffixPairs = rnd.next(1, 20);
        prefixLength = rnd.next(0, min(25, 100 - 2 * suffixPairs));
    }

    string skewer;
    skewer.reserve(prefixLength + 2 * suffixPairs);

    char heavy = rnd.next(0, 1) == 0 ? 's' : 't';
    for (int i = 0; i < prefixLength; ++i) {
        if (mode == 2) {
            skewer += heavy;
        } else {
            skewer += rnd.next(0, 99) < 70 ? heavy : (heavy == 's' ? 't' : 's');
        }
    }

    skewer += makeBalancedSuffix(suffixPairs, rnd.next(0, 3));

    println((int)skewer.size());
    println(skewer);

    return 0;
}
