#include <iostream>

void insertionSort(int *arr, int length)
{
	int subIdx = 0, key;
	for (int idx = 0; idx < length; idx++)
	{
		key = arr[idx];
		subIdx = idx - 1;

		while (subIdx >= 0 && arr[subIdx] > key)
		{
			arr[subIdx + 1] = arr[subIdx];
			subIdx--;
		}
		arr[subIdx + 1] = key;
	}
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

void main()
{
	/*개수가 0개인 상황 테스트*/
	int arr1[1] = {};
	std::cout << "정렬 전 : ";
	printArr(arr1, 0);
	insertionSort(arr1, 0);
	std::cout << "정렬 후 : ";
	printArr(arr1, 0);

	/*개수가 1개인 상황 테스트*/
	int arr2[1] = {4};
	std::cout << "정렬 전 : ";
	printArr(arr2, 1);
	insertionSort(arr2, 1);
	std::cout << "정렬 후 : ";
	printArr(arr2, 1);

	/*개수가 2개인 상황 + 감소순 테스트*/
	int arr3[2] = { 4, 1 };
	std::cout << "정렬 전 : ";
	printArr(arr3, 2);
	insertionSort(arr3, 2);
	std::cout << "정렬 후 : ";
	printArr(arr3, 2);

	/*개수가 20개인 상황 + 랜덤 + 동일한 숫자 테스트*/
	int arr4[20] = { 4,4,4,4,4,3,3,5,7,9,1,3,6,0,6,3,2,6,8,3 };
	std::cout << "정렬 전 : ";
	printArr(arr4, 20);
	insertionSort(arr4, 20);
	std::cout << "정렬 후 : ";
	printArr(arr4, 20);

	getchar();
}