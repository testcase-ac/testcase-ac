#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 15);
    int m = rnd.next(2, 25);

    vector<int> boss(n + 1);
    boss[1] = -1;

    if (mode == 0) {
        for (int employee = 2; employee <= n; ++employee) {
            boss[employee] = employee - 1;
        }
    } else if (mode == 1) {
        for (int employee = 2; employee <= n; ++employee) {
            boss[employee] = 1;
        }
    } else if (mode == 2) {
        for (int employee = 2; employee <= n; ++employee) {
            boss[employee] = rnd.next(1, employee - 1);
        }
    } else if (mode == 3) {
        int width = rnd.next(1, max(1, n - 1));
        for (int employee = 2; employee <= n; ++employee) {
            if (employee <= width + 1) {
                boss[employee] = 1;
            } else {
                boss[employee] = rnd.next(2, employee - 1);
            }
        }
    } else {
        int handle = rnd.next(2, n);
        for (int employee = 2; employee <= n; ++employee) {
            if (employee <= handle) {
                boss[employee] = employee - 1;
            } else {
                boss[employee] = rnd.next(2, handle);
            }
        }
    }

    println(n, m);
    for (int employee = 1; employee <= n; ++employee) {
        if (employee > 1) {
            cout << ' ';
        }
        cout << boss[employee];
    }
    cout << '\n';

    for (int query = 0; query < m; ++query) {
        int employee;
        if (query > 0 && rnd.next(0, 2) == 0) {
            employee = rnd.next(2, min(n, 5));
        } else {
            employee = rnd.next(2, n);
        }

        int weightMode = rnd.next(0, 3);
        int weight;
        if (weightMode == 0) {
            weight = 1;
        } else if (weightMode == 1) {
            weight = 1000;
        } else if (weightMode == 2) {
            weight = rnd.next(1, 20);
        } else {
            weight = rnd.next(1, 1000);
        }
        println(employee, weight);
    }

    return 0;
}
