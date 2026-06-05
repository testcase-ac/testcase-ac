#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

string formatTime(long long scaled) {
    long long integerPart = scaled / 10000;
    long long fractionalPart = scaled % 10000;
    if (fractionalPart == 0 && rnd.next(2) == 0) {
        return to_string(integerPart);
    }

    string fractional = to_string(fractionalPart + 10000).substr(1);
    int width = rnd.next(1, 4);
    while (width > 1 && fractional[width - 1] == '0' && rnd.next(2) == 0) {
        --width;
    }
    return to_string(integerPart) + "." + fractional.substr(0, width);
}

void printCase(long long timeScaled, vector<long long> x, vector<long long> v) {
    vector<int> order(x.size());
    for (int i = 0; i < int(order.size()); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    println(int(x.size()), formatTime(timeScaled));
    for (int i = 0; i < int(order.size()); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << x[order[i]];
    }
    cout << '\n';
    for (int i = 0; i < int(order.size()); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << v[order[i]];
    }
    cout << '\n';
}

void singleStudent() {
    long long timeScaled = rnd.next(1, 1000000) * 10000LL + rnd.next(0, 9999);
    printCase(timeScaled, {rnd.next(1, 1000000000)}, {rnd.next(1, 1000000000)});
}

void guaranteedMeeting() {
    int n = rnd.next(2, 18);
    long long time = rnd.next(1, 20);
    long long meeting = rnd.next(50, 1000000);
    vector<long long> x(n), v(n);

    for (int i = 0; i < n; ++i) {
        v[i] = rnd.next(1, 30);
        long long maxDistance = time * v[i];
        long long delta = rnd.next(-maxDistance, maxDistance);
        x[i] = max(1LL, min(1000000000LL, meeting + delta));
    }

    printCase(time * 10000LL + rnd.next(0, 9999), x, v);
}

void impossiblePair() {
    int n = rnd.next(2, 16);
    long long time = rnd.next(1, 12);
    long long leftSpeed = rnd.next(1, 20);
    long long rightSpeed = rnd.next(1, 20);
    long long gap = time * (leftSpeed + rightSpeed) + rnd.next(1, 20);

    vector<long long> x = {rnd.next(1, 1000000), 0};
    x[1] = x[0] + gap;
    vector<long long> v = {leftSpeed, rightSpeed};

    for (int i = 2; i < n; ++i) {
        x.push_back(rnd.next(x[0], x[1]));
        v.push_back(rnd.next(1, 25));
    }

    printCase(time * 10000LL, x, v);
}

void boundaryTouching() {
    int n = rnd.next(2, 14);
    long long time = rnd.next(1, 15);
    long long leftSpeed = rnd.next(1, 25);
    long long rightSpeed = rnd.next(1, 25);
    long long left = rnd.next(1, 1000000);
    long long right = left + time * (leftSpeed + rightSpeed);

    vector<long long> x = {left, right};
    vector<long long> v = {leftSpeed, rightSpeed};
    long long meet = left + time * leftSpeed;

    for (int i = 2; i < n; ++i) {
        long long speed = rnd.next(1, 25);
        long long delta = rnd.next(-time * speed, time * speed);
        x.push_back(max(1LL, min(1000000000LL, meet + delta)));
        v.push_back(speed);
    }

    printCase(time * 10000LL, x, v);
}

void largeValues() {
    int n = rnd.next(2, 20);
    long long time = rnd.next(999900000, 1000000000);
    vector<long long> x(n), v(n);

    for (int i = 0; i < n; ++i) {
        x[i] = rnd.next(1, 1000000000);
        v[i] = rnd.next(1, 1000000000);
    }

    printCase(time * 10000LL, x, v);
}

void fractionalTime() {
    int n = rnd.next(2, 18);
    long long timeScaled = rnd.next(10000, 200000);
    vector<long long> x(n), v(n);

    long long base = rnd.next(1, 1000000);
    for (int i = 0; i < n; ++i) {
        x[i] = base + rnd.next(0, 100);
        v[i] = rnd.next(1, 100);
    }

    printCase(timeScaled, x, v);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    if (mode == 0) {
        singleStudent();
    } else if (mode == 1) {
        guaranteedMeeting();
    } else if (mode == 2) {
        impossiblePair();
    } else if (mode == 3) {
        boundaryTouching();
    } else if (mode == 4) {
        largeValues();
    } else {
        fractionalTime();
    }

    return 0;
}
