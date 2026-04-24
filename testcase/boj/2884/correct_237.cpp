#include <iostream>

using namespace std;

int main() {
	int h, m;
	cin >> h >> m;
	m -= 45;
	if(m < 0) {
		m += 60;
		h--;
	}
	if(h < 0)
		h += 24;
	printf("%d %d", h, m);

}
