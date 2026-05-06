#include <iostream>
#include <string>
using namespace std;

string addLargeNumbers(const string& a, const string& b) {
    string result = "";
    int carry = 0;
    int i = a.length() - 1, j = b.length() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? a[i--] - '0' : 0;
        int digitB = (j >= 0) ? b[j--] - '0' : 0;
        int sum = digitA + digitB + carry;
        result = char((sum % 10) + '0') + result;
        carry = sum / 10;
    }

    return result;
}
int main() {
    string a, b;
    cin >> a >> b;
    cout << addLargeNumbers(a, b) << endl;
}
