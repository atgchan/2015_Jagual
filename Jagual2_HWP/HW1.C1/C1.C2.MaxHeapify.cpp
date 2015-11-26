#include <cstdlib>
#include <iostream>
#include <ctime>
#include <limits>

typedef struct heap
{
	int size;
	int *element;
} heap_t;

void MaxHeapify(heap_t* heap, int pos)
{
	int largest;
	int left = 2 * pos;
	int right = 2 * pos + 1;

	if (left <= heap->size && heap->element[left] > heap->element[pos])
	{
		largest = left;
	}
	else
	{
		largest = pos;
	}

	if (right <= heap->size && heap->element[right] > heap->element[largest])
	{
		largest = right;
	}
	
	if (largest != pos)
	{
		int tmp = heap->element[largest];
		heap->element[largest] = heap->element[pos];
		heap->element[pos] = tmp;
		MaxHeapify(heap, largest);
	}
}

void BuildMaxHeap(heap_t* heap)
{
	for (int i = heap->size / 2; i >= 1; i--)
	{
		MaxHeapify(heap, i);
	}
}

void MakeSampleHeap(heap_t* heap, int n)
{
	heap->size = 0;
	std::srand(std::time(0));
	for (int i = 1; i <= n; i++)
	{
		heap->element[i] = std::rand() % 100;
		heap->size++;
	}
}

bool IsMaxHeap(heap_t* heap)
{
	for (int i = 1; i <= heap->size; i++)
	{
		if (i * 2 >= heap->size && (heap->element[i] < heap->element[i * 2]))
		{
			return false;
		}
		if (i * 2 + 1 >= heap->size && (heap->element[i] < heap->element[i * 2 + 1]))
		{
			return false;
		}
	}
	return true;
}

void PrintHeap(heap_t* heap)
{
	for (int i = 1; i <= heap->size; i++)
	{
		std::cout << heap->element[i] << ", ";
	}
	std::cout << std::endl;
}

int ExtractMax(heap_t* heap)
{
	int tmp = heap->element[1];
	heap->element[1] = heap->element[heap->size];
	heap->element[heap->size] = tmp;
	int maxValue = heap->element[heap->size];
	--heap->size;
	MaxHeapify(heap, 1);
	return maxValue;
}

void HeapIncreaseKey(heap_t* heap, int key)
{
	if (key / 2 < 1)
	{
		return;
	}
	else if (heap->element[key] > heap->element[key / 2])
	{
		int tmp = heap->element[key];
		heap->element[key] = heap->element[key / 2];
		heap->element[key / 2] = tmp;
	}
	HeapIncreaseKey(heap, key / 2);
}

void MaxHeapInsert(heap_t* heap, int key)
{
	++heap->size;
	heap->element[heap->size] = key;//std::numeric_limits<int>::min();
	HeapIncreaseKey(heap, heap->size);
}

void TestHeapify(int size)
{
	int arr[100] = {};
	heap_t heap1;
	heap1.element = arr;
	MakeSampleHeap(&heap1, size);
	PrintHeap(&heap1);
	BuildMaxHeap(&heap1);
	if (IsMaxHeap(&heap1))
	{
		PrintHeap(&heap1);
	}

	std::cout << "최대값을 제거합니다.." << std::endl;
	int maxValue = ExtractMax(&heap1);
	PrintHeap(&heap1);

	std::cout << "값을 추가합니다.. 50" << std::endl;
	MaxHeapInsert(&heap1, 50);
	PrintHeap(&heap1);
}

int main()
{
	TestHeapify(10);

	getchar();
}