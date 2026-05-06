#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

typedef complex<double> base;

void fft(vector<base> &a, bool inv) {
    int n = (int) a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? M_PI / i : -M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n *= 2;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    for (int i = 0; i < n - 1; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    while (result.size() > 1 && result.back() == 0) result.pop_back();
    return result;
}

int main() {
    string A, B;
    cin >> A >> B;

    vector<int> a(A.size()), b(B.size());
    for (int i = 0; i < A.size(); i++) a[A.size() - 1 - i] = A[i] - '0';
    for (int i = 0; i < B.size(); i++) b[B.size() - 1 - i] = B[i] - '0';

    vector<int> result = multiply(a, b);

    for (auto it = result.rbegin(); it != result.rend(); it++) cout << *it;
    cout << endl;
}
