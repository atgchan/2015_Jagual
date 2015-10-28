#include <iostream>

void insertionSort(int *arr, int length)
{
	int subIdx = 0, key;
	/*
		Initialization
		arr[0]부터 arr[0]까지는 단 한 개의 원소만 존재함으로 정렬되어있고 loop invariant는 TURE이다.
	*/
	for (int idx = 0; idx < length; idx++)
	{
		/*
			Maintenance
			idx가 0이면 subIdx>=0의 조건을 만족하지 못해 그냥 통과.
			idx가 1이면 arr[1]의 값을 가지고 arr[0]의 값과 비교, 더 작다면 둘의 위치가 바뀐다. 0~1의 값은 정렬되어있음.
			idx가 k이면 arr[k]의 값을 가지고 arr[k-1]부터 arr[0]까지 순차적으로 비교하며 key보다 더 작은 값을 찾을 때 까지 배열을 한칸 씩 미루면서 비교하다가 찾으면 그 자리에 들어간다.
			따라서 arr[k-1]까지의 값은 이미 정렬되어있고, arr[k]가 삽입된 이후에도 값은 여전히 정렬되어있다.
		*/
		key = arr[idx];
		subIdx = idx - 1;

		while (subIdx >= 0 && arr[subIdx] > key)
		{
			arr[subIdx + 1] = arr[subIdx];
			subIdx--;
		}
		arr[subIdx + 1] = key;
	}
	/*
		Termination
		종료 시점은 idx == length일 때
		비교는 idx가 length -1 이 될때 까지 이루어졌다.
		종료 시점에서 비교하지 않은 원소의 개수는 0개이고, 0부터 length-1 까지의 원소들은 배열에 존재하던 원소들이고 정렬되어있다.
		결과적으로 알고리즘은 correct하다.
	*/
}

void printArr(int* arr, int length)
{
	std::cout << "[ ";
	for (int i = 0; i < length; i++)
	{
		std::cout << arr[i];
		if (i < length - 1)
			std::cout << ", ";
	}
	std::cout << " ]" << std::endl;
}

int isSorted(int *arr, int length)
{
	for (int i = 1; i < length; i++)
	{
		if (arr[i] < arr[i - 1])
			return 0;
	}
	return 1;
}

void main()
{
	/*개수가 0개인 상황 테스트*/
	int arr1[1] = {};
	std::cout << "정렬 전 : ";
	printArr(arr1, 0);
	insertionSort(arr1, 0);
	std::cout << "정렬 후 : ";
	printArr(arr1, 0);
	std::cout << "결과 : " << isSorted(arr1, 0) << std::endl;

	/*개수가 1개인 상황 테스트*/
	int arr2[1] = { 4 };
	std::cout << "정렬 전 : ";
	printArr(arr2, 1);
	insertionSort(arr2, 1);
	std::cout << "정렬 후 : ";
	printArr(arr2, 1);
	std::cout << "결과 : " << isSorted(arr2, 1) << std::endl;

	/*개수가 2개인 상황 + 감소순 테스트*/
	int arr3[2] = { 4, 1 };
	std::cout << "정렬 전 : ";
	printArr(arr3, 2);
	insertionSort(arr3, 2);
	std::cout << "정렬 후 : ";
	printArr(arr3, 2);
	std::cout << "결과 : " << isSorted(arr3, 2) << std::endl;

	/*개수가 20개인 상황 + 랜덤 + 동일한 숫자 테스트*/
	int arr4[20] = { 4, 4, 4, 4, 4, 3, 3, 5, 7, 9, 1, 3, 6, 0, 6, 3, 2, 6, 8, 3 };
	std::cout << "정렬 전 : ";
	printArr(arr4, 20);
	insertionSort(arr4, 20);
	std::cout << "정렬 후 : ";
	printArr(arr4, 20);
	std::cout << "결과 : " << isSorted(arr4, 20) << std::endl;

	getchar();
}