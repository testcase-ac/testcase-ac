#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomLetters(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        if (rnd.next(2) == 0) {
            s += char('A' + rnd.next(26));
        } else {
            s += char('a' + rnd.next(26));
        }
    }
    return s;
}

string randomCheeseName() {
    return randomLetters(rnd.next(1, 12)) + "Cheese";
}

string randomNearMiss() {
    vector<string> suffixes = {"cheese", "CHEESE", "Cheesa", "Chees", "CheeseCake"};
    if (rnd.next(3) == 0) {
        return "Cheese" + randomLetters(rnd.next(1, 8));
    }
    return randomLetters(rnd.next(1, 12)) + rnd.any(suffixes);
}

string randomPlainName() {
    string s = randomLetters(rnd.next(1, 16));
    if (s.size() >= 6 && s.substr(s.size() - 6) == "Cheese") {
        s.back() = 'x';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 1;
    vector<string> toppings;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 10);
    } else if (mode == 2) {
        n = rnd.next(4, 12);
    } else if (mode == 3) {
        n = rnd.next(8, 25);
    } else {
        n = rnd.next(30, 100);
    }

    int distinctCheeseTarget = 0;
    if (mode == 1) {
        distinctCheeseTarget = rnd.next(4, min(n, 7));
    } else if (mode == 2) {
        distinctCheeseTarget = rnd.next(1, min(n, 3));
    } else if (mode == 3) {
        distinctCheeseTarget = rnd.next(0, min(n, 5));
    } else {
        distinctCheeseTarget = rnd.next(0, min(n, 4));
    }

    vector<string> cheeseNames;
    for (int i = 0; i < distinctCheeseTarget; ++i) {
        string name;
        do {
            name = randomCheeseName();
        } while (find(cheeseNames.begin(), cheeseNames.end(), name) != cheeseNames.end());
        cheeseNames.push_back(name);
        toppings.push_back(name);
    }

    while ((int)toppings.size() < n) {
        int choice = rnd.next(100);
        if (!cheeseNames.empty() && choice < 35) {
            toppings.push_back(rnd.any(cheeseNames));
        } else if (choice < 70) {
            toppings.push_back(randomNearMiss());
        } else {
            toppings.push_back(randomPlainName());
        }
    }

    shuffle(toppings.begin(), toppings.end());

    println(n);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << toppings[i];
    }
    cout << '\n';

    return 0;
}
