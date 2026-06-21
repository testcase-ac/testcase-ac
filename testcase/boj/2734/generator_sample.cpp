#include "testlib.h"

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    cout << t << '\n';

    cout << fixed << setprecision(1);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = 1;
        } else if (mode == 1) {
            n = 10;
        } else {
            n = rnd.next(2, 10);
        }

        double start;
        int startMode = rnd.next(0, 3);
        if (startMode == 0) {
            start = rnd.next(-20, 20);
        } else if (startMode == 1) {
            start = rnd.next(-1000, 1000) / 10.0;
        } else {
            start = rnd.next(0, 50) / 10.0;
        }

        vector<double> x(n);
        x[0] = start;
        for (int i = 1; i < n; ++i) {
            double gap;
            if (mode == 1) {
                gap = 2.0;
            } else if (mode == 2) {
                gap = 3.4;
            } else if (mode == 3) {
                gap = (i % 2 == 0 ? 2.0 : 3.4);
            } else if (mode == 4) {
                gap = rnd.next(20, 34) / 10.0;
            } else {
                gap = rnd.any(vector<double>{2.0, 2.1, 2.7, 3.3, 3.4});
            }
            x[i] = x[i - 1] + gap;
        }

        cout << n;
        for (double value : x) {
            cout << ' ' << value;
        }
        cout << '\n';
    }

    return 0;
}
