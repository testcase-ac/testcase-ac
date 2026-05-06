#include <iostream>
#include <random>
using namespace std;

int main() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis_w(2, 1000);
	uniform_int_distribution<> dis_h(2, 1000);

	int w = dis_w(gen);
	int h = dis_h(gen);

	uniform_int_distribution<> dis_x(1, w - 1);
	uniform_int_distribution<> dis_y(1, h - 1);

	int x = dis_x(gen);
	int y = dis_y(gen);

	cout << x << " " << y << " " << w << " " << h << endl;
}
