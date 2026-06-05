#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int chooseDifferent(int a, int b) {
    vector<int> choices;
    for (int pasta = 1; pasta <= 3; ++pasta) {
        if (pasta != a || pasta != b) {
            choices.push_back(pasta);
        }
    }
    return rnd.any(choices);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(3, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 25);
    } else if (mode == 2) {
        n = rnd.next(20, 50);
    } else {
        n = rnd.next(3, 30);
    }

    vector<int> plan(n + 1);
    for (int day = 1; day <= n; ++day) {
        if (day >= 3 && plan[day - 1] == plan[day - 2]) {
            plan[day] = chooseDifferent(plan[day - 1], plan[day - 2]);
        } else if (mode == 3 && day > 1 && rnd.next(100) < 60) {
            plan[day] = plan[day - 1];
        } else if (mode == 4) {
            plan[day] = (day - 1) % 3 + 1;
        } else {
            plan[day] = rnd.next(1, 3);
        }
    }

    int k;
    if (mode == 0) {
        k = rnd.next(1, n);
    } else if (mode == 1) {
        k = rnd.next(1, min(n, 5));
    } else if (mode == 2) {
        k = rnd.next(max(1, n / 2), n);
    } else if (mode == 3) {
        k = rnd.next(max(1, n - 8), n);
    } else {
        k = n;
    }

    vector<int> days;
    for (int day = 1; day <= n; ++day) {
        days.push_back(day);
    }
    shuffle(days.begin(), days.end());
    days.resize(k);

    println(n, k);
    for (int day : days) {
        println(day, plan[day]);
    }

    return 0;
}
