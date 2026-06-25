#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int dieSides(const string& die) {
    return stoi(die.substr(1));
}

void printCase(const vector<string>& dice, int x) {
    cout << dice.size();
    for (const string& die : dice) {
        cout << ' ' << die;
    }
    cout << ' ' << x << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> dieTypes = {"d4", "d6", "d8", "d10", "d12", "d20"};
    int caseCount = rnd.next(6, 18);

    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = rnd.next(0, 5);
        int d = rnd.next(1, 13);
        vector<string> dice;

        if (mode == 0) {
            string die = rnd.any(dieTypes);
            dice.assign(d, die);
        } else if (mode == 1) {
            d = rnd.next(1, 6);
            dice = dieTypes;
            shuffle(dice.begin(), dice.end());
            dice.resize(d);
        } else if (mode == 2) {
            d = 13;
            for (int i = 0; i < d; ++i) {
                dice.push_back(dieTypes[i % int(dieTypes.size())]);
            }
            shuffle(dice.begin(), dice.end());
        } else {
            for (int i = 0; i < d; ++i) {
                dice.push_back(rnd.any(dieTypes));
            }
        }

        int minSum = int(dice.size());
        int maxSum = 0;
        for (const string& die : dice) {
            maxSum += dieSides(die);
        }

        int targetMode = rnd.next(0, 6);
        int x;
        if (targetMode == 0) {
            x = 0;
        } else if (targetMode == 1) {
            x = minSum;
        } else if (targetMode == 2) {
            x = maxSum;
        } else if (targetMode == 3) {
            x = min(1000, maxSum + rnd.next(1, 20));
        } else if (targetMode == 4) {
            x = rnd.next(0, max(0, minSum - 1));
        } else {
            x = rnd.next(minSum, maxSum);
        }

        printCase(dice, x);
    }

    println(0);
    return 0;
}
