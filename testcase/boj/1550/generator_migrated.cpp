#include <iostream>
#include <random>

using namespace std;

string random_hex() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> len_dist(1, 6);
	uniform_int_distribution<> dist(0, 15);

	int len = len_dist(gen);
	string hex_chars = "0123456789ABCDEF";
	string res = "";
	
	for (int i = 0; i < len; i++) {
		res += hex_chars[dist(gen)];
	}
	return res;
}
int main() {
	cout << random_hex() << endl;
	return 0;
}
