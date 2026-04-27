/*
 * Official Solution (C++17)
 * Gyojun Youn
 */
#include <iostream>
using namespace std;

int N, Ans = 1;

int main() {
	cin >> N;
	while(1 < N) {
		N >>= 1;
		Ans <<= 1;
	}
	cout << Ans << endl;
	return 0;
}
