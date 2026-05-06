#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> char_dis(0, 61);

    char random_char;
    int rand_index = char_dis(gen);
    if (rand_index < 26) {
        random_char = 'a' + rand_index;
    } else if (rand_index < 52) {
        random_char = 'A' + (rand_index - 26);
    } else {
        random_char = '0' + (rand_index - 52);
    }

    cout << random_char << endl;
    return 0;
}
