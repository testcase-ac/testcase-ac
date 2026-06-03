#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomMask(int mode) {
    string mask(12, 'N');

    if (mode == 0) {
        mask = string(12, 'Y');
    } else if (mode == 1) {
        int category = rnd.next(12);
        mask[category] = 'Y';
    } else if (mode == 2) {
        int lo = rnd.next(0, 5);
        int hi = rnd.next(lo, 5);
        for (int i = lo; i <= hi; ++i) mask[i] = 'Y';
    } else if (mode == 3) {
        vector<int> special = {6, 7, 8, 9, 10, 11};
        shuffle(special.begin(), special.end());
        int take = rnd.next(1, 4);
        for (int i = 0; i < take; ++i) mask[special[i]] = 'Y';
    } else {
        for (int i = 0; i < 12; ++i) {
            if (rnd.next(100) < 45) mask[i] = 'Y';
        }
        if (mask.find('Y') == string::npos) mask[rnd.next(12)] = 'Y';
    }

    return mask;
}

vector<int> randomDice(int mode) {
    vector<int> dice(3);

    if (mode == 0) {
        int value = rnd.next(1, 6);
        dice = {value, value, value};
    } else if (mode == 1) {
        int value = rnd.next(1, 6);
        int other = rnd.next(1, 6);
        dice = {value, value, other};
    } else if (mode == 2) {
        vector<int> straight = rnd.next(2) == 0 ? vector<int>{1, 2, 3, 4, 5} : vector<int>{2, 3, 4, 5, 6};
        shuffle(straight.begin(), straight.end());
        dice = {straight[0], straight[1], straight[2]};
    } else if (mode == 3) {
        int start = rnd.next(1, 4);
        dice = {start, start + 1, start + 2};
    } else {
        for (int& die : dice) die = rnd.next(1, 6);
    }

    shuffle(dice.begin(), dice.end());
    return dice;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int maskMode = rnd.next(5);
    int diceMode = rnd.next(5);

    string mask = randomMask(maskMode);
    vector<int> dice = randomDice(diceMode);

    println(mask);
    println(dice);

    return 0;
}
