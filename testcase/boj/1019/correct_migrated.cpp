#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void countDigits(int N, vector<int>& result) {
    long long factor = 1;
    while (factor <= N) {
        long long lowerNumbers = N - (N / factor) * factor;
        long long currentDigit = (N / factor) % 10;
        long long higherNumbers = N / (factor * 10);
        
        for (int i = 0; i <= 9; i++) {
            if (i < currentDigit) {
                result[i] += (higherNumbers + 1) * factor;
            } else if (i == currentDigit) {
                result[i] += higherNumbers * factor + lowerNumbers + 1;
            } else {
                result[i] += higherNumbers * factor;
            }
        }

        factor *= 10;
    }
}

int main() {
    int N;
    cin >> N;
    
    vector<int> result(10, 0);
    
    countDigits(N, result);
    for(int j = 0; j <= int(log10(N)); j++) {
        result[0] -= int(pow(10, j));
    }
    for (int i = 0; i < 10; i++) {
        cout << result[i] << " ";
    }
}
