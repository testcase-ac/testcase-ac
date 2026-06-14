#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomAnswers(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next(1, 5);
    }
    return a;
}

vector<int> patternedAnswers(int n, int period) {
    vector<int> a(n);
    int offset = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        a[i] = (offset + i % period) % 5 + 1;
    }
    return a;
}

vector<int> shiftedRight(const vector<int>& answer, int p) {
    int n = answer.size();
    vector<int> omr(n);
    omr[p] = rnd.next(1, 5);
    for (int i = p + 1; i < n; ++i) {
        omr[i] = answer[i - 1];
    }
    for (int i = 0; i < p; ++i) {
        omr[i] = answer[i];
    }
    return omr;
}

vector<int> shiftedLeft(const vector<int>& answer, int p) {
    int n = answer.size();
    vector<int> omr(n);
    for (int i = 0; i < p; ++i) {
        omr[i] = answer[i];
    }
    for (int i = p; i + 1 < n; ++i) {
        omr[i] = answer[i + 1];
    }
    omr[n - 1] = rnd.next(1, 5);
    return omr;
}

void addNoise(vector<int>& a, int changes) {
    int n = a.size();
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());
    for (int i = 0; i < changes; ++i) {
        int pos = order[i];
        int old = a[pos];
        a[pos] = rnd.next(1, 4);
        if (a[pos] >= old) {
            ++a[pos];
        }
    }
}

void printCase(int n, int k, const vector<int>& answer, const vector<int>& omr) {
    println(n, k);
    println(answer);
    println(omr);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 5) {
        n = 20;
    } else if (mode == 6) {
        n = rnd.next(5, 7);
    } else {
        n = rnd.next(5, 20);
    }
    int k = rnd.next(0, 3);

    vector<int> answer;
    vector<int> omr;

    if (mode == 0) {
        answer = randomAnswers(n);
        omr = randomAnswers(n);
        k = 0;
    } else if (mode == 1) {
        answer = randomAnswers(n);
        omr = answer;
    } else if (mode == 2) {
        answer = patternedAnswers(n, rnd.next(2, 5));
        int p = rnd.next(0, n - 2);
        omr = shiftedRight(answer, p);
        k = max(k, 1);
    } else if (mode == 3) {
        answer = patternedAnswers(n, rnd.next(2, 5));
        int p = rnd.next(0, n - 2);
        omr = shiftedLeft(answer, p);
        k = max(k, 1);
    } else if (mode == 4) {
        answer = randomAnswers(n);
        int p = rnd.next(0, n - 2);
        omr = rnd.next(0, 1) ? shiftedRight(answer, p) : shiftedLeft(answer, p);
        addNoise(omr, rnd.next(1, min(3, n)));
        k = rnd.next(1, 3);
    } else if (mode == 5) {
        answer = patternedAnswers(n, 5);
        omr = randomAnswers(n);
        k = 3;
    } else {
        answer = patternedAnswers(n, 2);
        omr = answer;
        addNoise(omr, rnd.next(1, n));
    }

    printCase(n, k, answer, omr);
    return 0;
}
