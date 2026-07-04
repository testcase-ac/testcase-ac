#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static string makeNameFromCounts(vector<int> counts) {
    string s;
    for (int i = 0; i < (int)counts.size(); ++i) {
        s += string(counts[i], char('A' + i));
    }
    shuffle(s.begin(), s.end());
    return s;
}

static vector<int> splitHalfCounts(int halfLength, int letters) {
    vector<int> counts(letters, 0);
    for (int i = 0; i < halfLength; ++i) {
        ++counts[rnd.next(0, letters - 1)];
    }
    return counts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int length = rnd.next(1, 30);
    if (mode == 5) length = rnd.next(45, 50);

    vector<int> counts(26, 0);

    if (mode == 0) {
        // Tiny names exercise the length-1 lower bound and duplicate-only cases.
        length = rnd.next(1, 4);
        char c = char('A' + rnd.next(0, 25));
        println(string(length, c));
        return 0;
    }

    if (mode == 1 || mode == 5) {
        // Palindrome-possible: all even counts, or exactly one odd count.
        int letters = rnd.next(1, min(26, max(1, length)));
        vector<int> half = splitHalfCounts(length / 2, letters);
        for (int i = 0; i < letters; ++i) counts[i] = 2 * half[i];
        if (length % 2 == 1) ++counts[rnd.next(0, letters - 1)];
    } else if (mode == 2) {
        // Impossible with several odd-count letters.
        length = rnd.next(2, 30);
        int oddLetters = rnd.next(2, min(9, length));
        for (int i = 0; i < oddLetters; ++i) counts[i] = 1;
        int remaining = length - oddLetters;
        for (int i = 0; i < remaining / 2; ++i) {
            counts[rnd.next(0, oddLetters - 1)] += 2;
        }
        if (remaining % 2 == 1) ++counts[oddLetters];
    } else if (mode == 3) {
        // Many distinct letters catches solutions that mishandle lexicographic ordering.
        length = rnd.next(10, 26);
        for (int i = 0; i < length; ++i) counts[i] = 1;
    } else if (mode == 4) {
        // Skewed valid names place most copies on one letter and a small tail elsewhere.
        length = rnd.next(5, 30);
        int heavy = rnd.next(6, 25);
        int sideLetters = rnd.next(1, 6);
        int used = length % 2;
        counts[heavy] = used;
        for (int i = 0; i < sideLetters; ++i) {
            int add = 2 * rnd.next(0, 3);
            counts[i] += add;
            used += add;
        }
        if (used > length) {
            counts.assign(26, 0);
            counts[heavy] = length;
        } else {
            counts[heavy] += length - used;
        }
    } else {
        // Maximum-length valid case with all counts even.
        length = 50;
        for (int i = 0; i < 25; ++i) counts[i] = 2;
    }

    string name = makeNameFromCounts(counts);
    if (name.empty()) name = "A";
    if ((int)name.size() > 50) name.resize(50);
    println(name);
    return 0;
}
