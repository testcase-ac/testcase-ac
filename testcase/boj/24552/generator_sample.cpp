#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string nestedSequence(int pairs) {
    return string(pairs, '(') + string(pairs, ')');
}

string repeatedPairs(int pairs) {
    string s;
    for (int i = 0; i < pairs; ++i) {
        s += "()";
    }
    return s;
}

string randomBalancedSequence(int pairs, int bias) {
    string s;
    int opens = 0;
    int closes = 0;
    int balance = 0;

    while (opens < pairs || closes < pairs) {
        bool canOpen = opens < pairs;
        bool canClose = closes < pairs && balance > 0;
        bool takeOpen;

        if (!canClose) {
            takeOpen = true;
        } else if (!canOpen) {
            takeOpen = false;
        } else if (bias > 0) {
            takeOpen = rnd.next(100) < 65;
        } else if (bias < 0) {
            takeOpen = rnd.next(100) < 35;
        } else {
            takeOpen = rnd.next(2) == 0;
        }

        if (takeOpen) {
            s += '(';
            ++opens;
            ++balance;
        } else {
            s += ')';
            ++closes;
            --balance;
        }
    }

    return s;
}

string mixedSequence(int pairs) {
    vector<string> blocks;
    int remaining = pairs;
    while (remaining > 0) {
        int take = rnd.next(1, remaining);
        int mode = rnd.next(3);
        if (mode == 0) {
            blocks.push_back(repeatedPairs(take));
        } else if (mode == 1) {
            blocks.push_back(nestedSequence(take));
        } else {
            blocks.push_back(randomBalancedSequence(take, rnd.next(-1, 1)));
        }
        remaining -= take;
    }
    shuffle(blocks.begin(), blocks.end());

    string s;
    for (const string& block : blocks) {
        s += block;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pairs = rnd.next(1, 24);
    int mode = rnd.next(5);

    string s;
    if (mode == 0) {
        s = repeatedPairs(pairs);
    } else if (mode == 1) {
        s = nestedSequence(pairs);
    } else if (mode == 2) {
        s = randomBalancedSequence(pairs, 1);
    } else if (mode == 3) {
        s = randomBalancedSequence(pairs, -1);
    } else {
        s = mixedSequence(pairs);
    }

    char extra = rnd.next(2) == 0 ? '(' : ')';
    int position = rnd.next(0, (int)s.size());
    s.insert(s.begin() + position, extra);

    println(s);
    return 0;
}
