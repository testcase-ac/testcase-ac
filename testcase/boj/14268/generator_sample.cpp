#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 15);
    int m = rnd.next(2, 30);

    vector<int> parent(n + 1);
    parent[1] = -1;

    if (mode == 0) {
        for (int employee = 2; employee <= n; ++employee) {
            parent[employee] = employee - 1;
        }
    } else if (mode == 1) {
        for (int employee = 2; employee <= n; ++employee) {
            parent[employee] = 1;
        }
    } else if (mode == 2) {
        for (int employee = 2; employee <= n; ++employee) {
            parent[employee] = rnd.next(1, employee - 1);
        }
    } else if (mode == 3) {
        int width = rnd.next(1, max(1, n - 1));
        for (int employee = 2; employee <= n; ++employee) {
            if (employee <= width + 1) {
                parent[employee] = 1;
            } else {
                parent[employee] = rnd.next(2, employee - 1);
            }
        }
    } else {
        int handle = rnd.next(2, n);
        for (int employee = 2; employee <= n; ++employee) {
            if (employee <= handle) {
                parent[employee] = employee - 1;
            } else {
                parent[employee] = rnd.next(2, handle);
            }
        }
    }

    println(n, m);
    for (int employee = 1; employee <= n; ++employee) {
        if (employee > 1) {
            cout << ' ';
        }
        cout << parent[employee];
    }
    cout << '\n';

    for (int query = 0; query < m; ++query) {
        bool mustAsk = query == m - 1;
        bool ask = mustAsk || (query > 0 && rnd.next(0, 99) < 45);

        if (ask) {
            int employee;
            if (rnd.next(0, 2) == 0) {
                employee = rnd.next(1, min(n, 5));
            } else {
                employee = rnd.next(1, n);
            }
            println(2, employee);
            continue;
        }

        int employee;
        if (rnd.next(0, 2) == 0) {
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
        println(1, employee, weight);
    }

    return 0;
}
