#include "testlib.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    vector<double> values;
    values.reserve(n);

    vector<double> anchors = {1.0, 2.0, 6.0, 12.5, 34.0, 128.0, 1024.0};

    int mode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        double a;
        if (mode == 0 && i < static_cast<int>(anchors.size())) {
            a = anchors[i];
        } else if (mode == 1) {
            a = rnd.next(1, 1024);
        } else if (mode == 2) {
            int whole = rnd.next(1, 1023);
            int tenth = rnd.next(0, 9);
            a = whole + tenth / 10.0;
        } else if (mode == 3) {
            int hundredths = rnd.next(100, 102400);
            a = hundredths / 100.0;
        } else {
            a = rnd.next(1.0, 1024.0);
        }
        values.push_back(a);
    }

    shuffle(values.begin(), values.end());

    cout << n << '\n';
    cout << fixed << setprecision(6);
    for (double a : values) {
        cout << a << '\n';
    }

    return 0;
}
