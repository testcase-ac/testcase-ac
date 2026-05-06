#include <iostream>
#include <random>
#include <string>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> len_dis(2, 15);
    uniform_int_distribution<> char_dis(0, 25);

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int len = len_dis(gen);
    string word = "";

    for (int i = 0; i < len; ++i) {
        word += alphabet[char_dis(gen)];
    } cout << word << endl;
    return 0;
}
