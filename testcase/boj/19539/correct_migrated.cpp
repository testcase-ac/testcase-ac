#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main() {
    char* p = (char*)mmap(0, 640000, PROT_READ, MAP_SHARED, 0, 0);
	auto readInt = [&]() {
		int ret = 0;
        for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
		return ret;
	};
    
	int n = readInt(), t1 = 0, t2 = 0;
	for (int i = 0; i < n; i++) {
        int t = readInt();
		t1 += t >> 1, t2 += t & 1;
	}
	cout << (t1 >= t2 && (t1 - t2) % 3 == 0 ? "YES" : "NO") << '\n';
}
