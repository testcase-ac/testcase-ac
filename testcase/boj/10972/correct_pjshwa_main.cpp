#include <cstdio>
#include <algorithm>

const int MAX_INT = 2000000000;

bool next_permutation(int size, int* array){

	// from the right, search for first index that has smaller element in front
	// if not found return nullptr
	// else, swap the location of the two + sort all elements in the right asc

	int smaller_element_index = -1;
	int smallest_element_on_rs = MAX_INT;
	int smallest_element_on_rs_index = -1;

	for(int i = size - 1; i > 0; i--){
		if (array[i] > array[i-1]){
			smaller_element_index = i - 1;
			break;
		}
	}

	// printf("%d\n", array[smaller_element_index]);

	for(int i = smaller_element_index + 1; i < size; i++){
		if (smallest_element_on_rs > array[i] && array[i] > array[smaller_element_index]){
			smallest_element_on_rs = array[i];
			smallest_element_on_rs_index = i;
		}
	}

	if(smaller_element_index == -1){
		return false;
	}

	// swap smaller_element_index - 1 and the smallest of right

	int temp = array[smaller_element_index];
	array[smaller_element_index] = smallest_element_on_rs;
	array[smallest_element_on_rs_index] = temp;

	std::sort(array + smaller_element_index + 1, array + size);

	return true;

}

int main(){
	int n;
	scanf("%d", &n);

	int array[n];

	for(int i = 0; i < n; i++){
		scanf("%d", &array[i]);
	}

	bool result = next_permutation(n, array);

	if (!result){
		printf("-1\n");
		return 0;
	}

	for(int i = 0; i < n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}