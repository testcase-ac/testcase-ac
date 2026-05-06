#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> t_dis(1, 5);
    uniform_int_distribution<> r_dis(1, 8);
    uniform_int_distribution<> len_dis(1, 10);
    string qr_alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$%*+-./:";
    uniform_int_distribution<> char_dis(0, qr_alphanumeric.size() - 1);
    int T = t_dis(gen);
    cout << T << endl;
    for (int t = 0; t < T; ++t) {
        int R = r_dis(gen);
        int len = len_dis(gen);
        string S = "";
        for (int i = 0; i < len; ++i) {
            S += qr_alphanumeric[char_dis(gen)];
        } cout << R << " " << S << endl;
    } return 0;
}
