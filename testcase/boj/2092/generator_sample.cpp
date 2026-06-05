#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int T;
    int A;
    vector<int> values;

    if (mode == 0) {
        T = rnd.next(1, 5);
        A = rnd.next(1, 8);
        int dominant = rnd.next(1, T);
        for (int i = 0; i < A; ++i) {
            if (rnd.next(0, 99) < 70) {
                values.push_back(dominant);
            } else {
                values.push_back(rnd.next(1, T));
            }
        }
    } else if (mode == 1) {
        T = rnd.next(2, 12);
        int used = rnd.next(1, min(T, 6));
        vector<int> labels;
        for (int i = 1; i <= T; ++i) {
            labels.push_back(i);
        }
        shuffle(labels.begin(), labels.end());
        labels.resize(used);

        for (int label : labels) {
            int count = rnd.next(1, 5);
            for (int i = 0; i < count; ++i) {
                values.push_back(label);
            }
        }
        A = (int)values.size();
    } else if (mode == 2) {
        T = rnd.next(20, 200);
        A = rnd.next(2, 16);
        for (int i = 0; i < A; ++i) {
            values.push_back(rnd.next(1, T));
        }
    } else if (mode == 3) {
        T = rnd.next(1, 8);
        A = rnd.next(8, 24);
        for (int i = 0; i < A; ++i) {
            values.push_back(rnd.next(1, T));
        }
    } else if (mode == 4) {
        T = rnd.next(2, 10);
        A = T;
        for (int i = 1; i <= T; ++i) {
            values.push_back(i);
        }
    } else {
        T = rnd.next(1, 6);
        A = rnd.next(1, 20);
        int label = rnd.next(1, T);
        values.assign(A, label);
    }

    shuffle(values.begin(), values.end());

    int rangeMode = rnd.next(0, 4);
    int S;
    int B;
    if (rangeMode == 0) {
        S = 1;
        B = A;
    } else if (rangeMode == 1) {
        S = A;
        B = A;
    } else if (rangeMode == 2) {
        S = 1;
        B = rnd.next(1, A);
    } else if (rangeMode == 3) {
        S = rnd.next(1, A);
        B = A;
    } else {
        S = rnd.next(1, A);
        B = rnd.next(S, A);
    }

    println(T, A, S, B);
    println(values);

    return 0;
}
