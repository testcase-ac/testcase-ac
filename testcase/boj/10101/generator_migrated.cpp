#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 3);

    int case_type = dist(gen);

    int a, b, c;
    if (case_type == 0) {
        a = b = c = 60;
    } else if (case_type == 1) {
        a = 60;
        uniform_int_distribution<> angle_dist(1, 89);
        b = angle_dist(gen);
        c = 180 - a - b;
    } else if (case_type == 2) {
        uniform_int_distribution<> angle_dist(1, 178);
        do {
            a = angle_dist(gen);
            b = angle_dist(gen);
            c = 180 - a - b;
        } while (a == b || b == c || a == c || c <= 0);
    } else { // Error
        uniform_int_distribution<> angle_dist(1, 179);
        a = angle_dist(gen);
        b = angle_dist(gen);
        c = angle_dist(gen);
        while (a + b + c == 180) {
            a = angle_dist(gen);
            b = angle_dist(gen);
            c = angle_dist(gen);
        }
    }
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
}
