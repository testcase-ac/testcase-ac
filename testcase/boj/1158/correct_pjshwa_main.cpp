#include <cstdio>

class Person {

private:
	int content;
public:
	Person* next;

	Person(int content){
		this->content = content;
	}
	void printcontent(){
		printf("%d", content);
	}
};

int main(){
	int n, m;
	scanf("%d%d", &n, &m);

	Person* base = new Person(0);
	Person* it = base;

	for(int i = 0; i < n; i++){
		it->next = new Person(i + 1);
		it = it->next;
	}

	it->next = base->next;

	int traverse = 0;
	it = base;
	printf("<");
	do{
		if(traverse) printf(", ");
		traverse++;
		for(int i = 0; i < m - 1; i++){
			it = it->next;
		}
		it->next->printcontent();
		it->next = it->next->next;
	} while(traverse < n);
	printf(">");
}