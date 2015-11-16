#include <iostream>

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

void CopyBlock(int* arr1, int* arr2, int* buffArr)
{
	int i = 0;
	while (arr1 + i != arr2)
	{
		buffArr[i] = arr1[i];
		i++;
	}
}

void Merge(int *arr, int *buffArr, int firstBegin, int firstLast, int secondLast)
{
	int idx, arr1Idx, arr2Idx;

	CopyBlock(arr + firstBegin, arr + secondLast + 1, buffArr + firstBegin);

	arr1Idx = firstBegin;
	arr2Idx = firstLast + 1;

	/*
		Loop Invariant
	*/
	/*
		Initialization
		buffArr[firstBegin]~buffArr[firstLast], buffArr[firstLast+1]~buffArr[secondLast] 두 범위 내의 숫자들은 이미 정렬되어 있다.
		따라서 앞의 범위를 arr1, 뒤의 범위를 arr2라고 정의한다면,
		arr1[firstBegin]의 값은 arr1의 값들 중 최소값이고,
		arr2[firstLast+1]의 값은 arr2의 값들 중 최소값이다.
		따라서 현 시점에서 arr1Idx는 arr1의 최소값을 가르키고, arr2Idx는 arr2의 최소값을 가르킨다.
		따라서 현 단계에서 loop invariant는 TRUE이다.
	*/
	for (idx = firstBegin; idx <= secondLast; idx++)
	{
		/*
			Maintenance
			arr1[arr1Idx] <= arr2[arr2Idx] 라고 가정한다.
			arr1[arr1Idx]는 아직 arr으로 복사되지 않은 가장 작은 원소이다.
			또한 이 전에 복사된 원소들은 모두 arr1[arr1Idx]보다 작거나 같다.
			따라서 arr1[arr1Idx]가 복사되면 arr의 개수가 한 개 늘어나도 정렬 상태를 유지한다.

			또한 arr1[arr1Idx]를 복사한 뒤 arr1Idx의 값을 1 증가시킨다.
			따라서 arr1[arr1Idx-1]보다 크거나 같은 새로운 arr1[arr1Idx]를 가르키게 되고, 다시 Maintenence의 첫 단계로 돌아가 값을 비교할 수 있다.
			또한 arr1[arr1Idx-1]가 arr1에 복사되었으므로 arr1[arr1Idx]의 값은 다시 arr1의 원소 중 가장 작은 값이 되어 초기 조건을 만족한다.

			반대의 경우도 마찬가지이다.
		*/
		if (arr1Idx > firstLast)
			arr[idx] = buffArr[arr2Idx++];
 		else if (arr2Idx > secondLast)
			arr[idx] = buffArr[arr1Idx++];
		else if (buffArr[arr1Idx] < buffArr[arr2Idx])
			arr[idx] = buffArr[arr1Idx++];
		else arr[idx] = buffArr[arr2Idx++];
	}
	/*
		Termination
		idx > secondLast의 시점일 때 종료
		idx - -1 == secondLast 이므로 buffArr의 모든 원소에 접근해서 arr으로 복사를 완료했음을 알 수 있다
		종료 시점에서 arr의 상태:
			원소 개수 : secondLast - firstBegin + 1
			원소 구성 : arr1과 arr2의 원소 중 작은 원소 (secondLast - firstBegin +1)개
			arr1과 arr2에 남아있는(복사되지 않은) 원소: 0개
			정렬상태 유지
	*/
}

void MergeSort(int *arr, int *buffArr, int begin, int last)
{
	int firstLast = 0;
	if (begin < last)
	{
		firstLast = (begin + last) / 2;
		MergeSort(arr, buffArr, begin, firstLast);
		MergeSort(arr, buffArr, firstLast + 1, last);
		Merge(arr, buffArr, begin, firstLast, last);
	}
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
	int arr1Buff[1] = {};
	std::cout << "정렬 전 : ";
	printArr(arr1, 0);
	MergeSort(arr1, arr1Buff, 0, 0);
	std::cout << "정렬 후 : ";
	printArr(arr1, 0);
	std::cout << "결과 : " << isSorted(arr1, 0) << std::endl;

	/*개수가 1개인 상황 테스트*/
	int arr2[1] = { 4 };
	int arr2Buff[1] = { 0 };
	std::cout << "정렬 전 : ";
	printArr(arr2, 1);
	MergeSort(arr2, arr2Buff, 0, 0);
	std::cout << "정렬 후 : ";
	printArr(arr2, 1);
	std::cout << "결과 : " << isSorted(arr2, 1) << std::endl;

	/*개수가 2개인 상황 + 감소순 테스트*/
	int arr3[2] = { 4, 0 };
	int arr3Buff[2] = { 0 };
	std::cout << "정렬 전 : ";
	printArr(arr3, 2);
	MergeSort(arr3, arr3Buff, 0, 1);
	std::cout << "정렬 후 : ";
	printArr(arr3, 2);
	std::cout << "결과 : " << isSorted(arr3, 2) << std::endl;

	/*개수가 20개인 상황 + 랜덤 + 동일한 숫자 테스트*/
	int arr4[20] = { 4, 4, 4, 4, 4, 3, 3, 5, 7, 9, 1, 3, 6, 0, 6, 3, 2, 6, 8, 3 };
	int arr4Buff[20] = {0};
	std::cout << "정렬 전 : ";
	printArr(arr4, 20);
	MergeSort(arr4, arr4Buff, 0, 19);
	std::cout << "정렬 후 : ";
	printArr(arr4, 20);
	std::cout << "결과 : " << isSorted(arr4, 20) << std::endl;

	getchar();
}