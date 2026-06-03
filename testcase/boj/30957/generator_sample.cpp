#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string buildString(int b, int s, int a) {
    string answers;
    answers.append(b, 'B');
    answers.append(s, 'S');
    answers.append(a, 'A');
    shuffle(answers.begin(), answers.end());
    return answers;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int b = 0, s = 0, a = 0;

    if (mode == 0) {
        vector<char> letters = {'B', 'S', 'A'};
        char winner = rnd.any(letters);
        int other1 = rnd.next(0, 12);
        int other2 = rnd.next(0, 12);
        int win = max(other1, other2) + rnd.next(1, 8);
        if (winner == 'B') {
            b = win;
            s = other1;
            a = other2;
        } else if (winner == 'S') {
            b = other1;
            s = win;
            a = other2;
        } else {
            b = other1;
            s = other2;
            a = win;
        }
    } else if (mode == 1) {
        int top = rnd.next(1, 15);
        int low = rnd.next(0, top - 1);
        int pair = rnd.next(0, 2);
        if (pair == 0) {
            b = s = top;
            a = low;
        } else if (pair == 1) {
            b = a = top;
            s = low;
        } else {
            s = a = top;
            b = low;
        }
    } else if (mode == 2) {
        int each = rnd.next(1, 10);
        b = s = a = each;
    } else if (mode == 3) {
        int n = rnd.next(1, 30);
        vector<char> letters = {'B', 'S', 'A'};
        char only = rnd.any(letters);
        if (only == 'B') b = n;
        if (only == 'S') s = n;
        if (only == 'A') a = n;
    } else if (mode == 4) {
        int n = rnd.next(20, 120);
        b = rnd.next(0, n);
        s = rnd.next(0, n - b);
        a = n - b - s;
        if (b + s + a == 0) b = 1;
    } else if (mode == 5) {
        int n = rnd.next(90000, 100000);
        b = rnd.next(0, n);
        s = rnd.next(0, n - b);
        a = n - b - s;
    } else {
        int n = rnd.next(2, 50);
        vector<int> weights = {rnd.next(1, 10), rnd.next(1, 10), rnd.next(1, 10)};
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(1, weights[0] + weights[1] + weights[2]);
            if (pick <= weights[0]) ++b;
            else if (pick <= weights[0] + weights[1]) ++s;
            else ++a;
        }
    }

    string answers = buildString(b, s, a);
    println((int)answers.size());
    println(answers);

    return 0;
}
