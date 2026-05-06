#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> colors = {"w", "r", "g", "b", "o", "y"};

vector<vector<string>> generateCube() {
    vector<vector<string>> cube(6, vector<string>(9));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 5);
    
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 9; ++j) {
            cube[i][j] = colors[dis(gen)];
        }
    }
    return cube;
}

void printCube(const vector<vector<string>>& cube) {
    for (int i = 0; i < 3; ++i) {
        cout << "      ";
        for (int j = 0; j < 3; ++j) {
            cout << cube[4][i * 3 + j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << cube[0][i * 3 + j] << " ";
        }
        for (int j = 0; j < 3; ++j) {
            cout << cube[1][i * 3 + j] << " ";
        }
        for (int j = 0; j < 3; ++j) {
            cout << cube[2][i * 3 + j] << " ";
        }
        for (int j = 0; j < 3; ++j) {
            cout << cube[3][i * 3 + j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 3; ++i) {
        cout << "      ";
        for (int j = 0; j < 3; ++j) {
            cout << cube[5][i * 3 + j] << " ";
        }
        cout << endl;
    }
}

void generateMoves(int t) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disSide(0, 5);
    uniform_int_distribution<> disDirection(0, 1);

    for (int i = 0; i < t; ++i) {
        int side = disSide(gen);
        int direction = disDirection(gen) == 0 ? -1 : 1;
        cout << side << " " << direction << endl;
    }
}

int main() {
    srand(time(0));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);

    int t = dis(gen);
    cout << t << endl;

    for (int i = 0; i < t; ++i) {
        vector<vector<string>> cube = generateCube();
        printCube(cube);

        int numMoves = rand() % 5 + 1;
        cout << numMoves << endl;
        generateMoves(numMoves);
    }
    return 0;
}
