#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(1, 15);
    int K = rnd.next(1, 100);
    
    vector<string> numbers;
    for (int i = 1; i <= N; ++i) {
        numbers.push_back(to_string(i));
    }
    
    shuffle(numbers.begin(), numbers.end());
    
    cout << N << endl;
    for (const string& num : numbers) {
        cout << num << endl;
    }
    cout << K << endl;
    
    return 0;
}
