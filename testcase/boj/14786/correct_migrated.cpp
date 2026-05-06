#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x, int A, int B, int C) {
    return A * x + B * sin(x) - C;
}

int main() {
    int A, B, C;
    cin >> A >> B >> C;

    double left = 0, right = 1000000;
    double x;

    while (right - left > 1e-10) {
        double mid = (left + right) / 2;
        if (f(mid, A, B, C) > 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    x=(left + right)/2;
    cout << fixed << setprecision(15) << x << endl;
}
