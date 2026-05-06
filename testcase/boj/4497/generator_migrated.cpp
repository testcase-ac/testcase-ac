#include <iostream>
#include <random>
#include <string>

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 5);
    uniform_int_distribution<> len_dis(1, 50);
    uniform_int_distribution<> t_dis(1, 10);

    char L_color = 'W';
    char D_color = 'O';
    char B_color = 'R';
    char U_color = 'B';
    char F_color = 'G';
    char R_color = 'Y';

    char colors[] = {'W', 'O', 'R', 'B', 'G', 'Y'};

    int t = t_dis(gen);
    cout << t << endl;

    for (int test_case = 0; test_case < t; test_case++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? L_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? D_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? B_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? U_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? F_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? R_color : colors[dis(gen)]) << ' ';
            }
            cout << endl;
        }
        string random_string = "";
        int len = len_dis(gen);
        for (int i = 0; i < len; i++) {
            random_string += colors[dis(gen)];
        }
        cout << random_string << endl;
    }

    return 0;
}
