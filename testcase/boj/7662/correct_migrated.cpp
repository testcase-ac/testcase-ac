#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
// 백준에서 참조할 수 있는 코드 중 가장 빠릅니다.
template<typename T> class MinMaxHeap { // Symmetric Min-Max Heap
public:
	MinMaxHeap() : v(2) { v.reserve(1'000'100); }
	~MinMaxHeap() {}

	void Push(const T& val) {
		size_t cur = v.size(); v.push_back(val);
		while (cur > 3) {
			if (cur & 1 && v[cur - 1] > v[cur]) swap(v[cur - 1], v[cur]), cur--;
			if (v[cur] < v[cur / 4 * 2]) swap(v[cur], v[cur / 4 * 2]), cur = cur / 4 * 2;
			else if (v[cur] > v[cur / 4 * 2 + 1]) swap(v[cur], v[cur / 4 * 2 + 1]), cur = cur / 4 * 2 + 1;
			else break;
		}
		if (cur == 3 && v[2] > v[3]) swap(v[2], v[3]);
	}

	void PopMin() {
		assert(!Empty());
		size_t cur = 2, nxt; swap(v[cur], v.back()), v.pop_back();
		while (cur < v.size()) {
			if (cur + 1 < v.size() && v[cur] > v[cur + 1]) swap(v[cur], v[cur + 1]); nxt = 2 * cur;
			if (nxt >= v.size()) break;
			if (2 * (cur + 1) < v.size() && v[nxt] > v[2 * (cur + 1)]) nxt = 2 * (cur + 1);
			if (v[cur] > v[nxt]) swap(v[cur], v[nxt]), cur = nxt;
			else break;
		}
	}

	void PopMax() {
		assert(!Empty());
		if (v.size() == 3) { v.pop_back(); return; }
		size_t cur = 3, nxt; swap(v[cur], v.back()), v.pop_back();
		while (cur < v.size()) {
			if (v[cur - 1] > v[cur]) swap(v[cur - 1], v[cur]); nxt = 2 * (cur - 1) + 1;
			if (nxt >= v.size()) break;
			if (2 * cur + 1 < v.size() && v[nxt] < v[2 * cur + 1]) nxt = 2 * cur + 1;
			if (v[cur] < v[nxt]) swap(v[cur], v[nxt]), cur = nxt;
			else break;
		}
	}

	T& Min() { assert(!Empty()); return v[2]; }
	T& Max() { assert(!Empty()); return v.size() > 3 ? v[3] : v[2]; }
	size_t Size() { return v.size() - 2; }
	bool Empty() { return v.size() <= 2; }
    void Clear() { v.clear(); v.push_back(T{}), v.push_back(T{}); }

private:
	vector<T> v;
};

int main() {
    struct stat st; fstat(0, &st);
	char *p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
	auto ReadInt = [&]() {
		int ret = 0; char c = *p++, flag = 0;
        if (c == '-') c = *p++, flag = 1;
        for (; c & 16; ret = 10 * ret + (c & 15), c = *p++);
        return flag ? -ret : ret;
	};

	int N = ReadInt(); MinMaxHeap<int> PQ;
	while (N--) {
		int q = ReadInt(); PQ.Clear();
		while (q--) {
			char c = *p++; p++; int t = ReadInt();
			if (c == 'I') PQ.Push(t);
			else if (PQ.Size()) {
				if (t == -1) PQ.PopMin();
				else PQ.PopMax();
			}
		}
		if (PQ.Empty()) cout << "EMPTY" << '\n';
		else cout << PQ.Max() << ' ' << PQ.Min() << '\n';
	}
}
