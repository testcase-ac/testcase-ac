#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> t_dis(1, 10);
    uniform_int_distribution<> len_dis(1, 20);
    uniform_int_distribution<> char_dis('A', 'Z');

    int T = t_dis(gen);
    cout << T << endl;

    for (int t = 0; t < T; ++t) {
        int len = len_dis(gen);
        string str = "";
        for (int i = 0; i < len; ++i) {
            char ch = char_dis(gen);
            str += ch;
        }
        cout << str << endl;
    }
    return 0;
}
