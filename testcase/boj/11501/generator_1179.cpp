#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int T = rnd.next(1, 2); // Generate 1 to 3 test cases
    cout << T << endl;
    
    for (int t = 0; t < T; t++) {
        int n = rnd.next(2, 10); // Each test case has 2 to 10 days
        cout << n << endl;
        
        vector<int> prices;
        for (int i = 0; i < n; i++) {
            prices.push_back(rnd.next(1, 20)); // Prices between 1 and 10000
        }
        
        // Output prices separated by spaces
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                cout << ' ';
            }
            cout << prices[i];
        }
        cout << endl;
    }
    
    return 0;
}
