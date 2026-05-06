#include <bits/stdc++.h>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,100);
    string input = "";
    int len = dist(gen) % 100 + 1;
    for (int i = 0; i < len; ++i) {
        char ch = (dist(gen) % 2 == 0) ? 'a' + dist(gen) % 26 : 'A' + dist(gen) % 26;
        input += ch;
    }
    cout << input;
}
