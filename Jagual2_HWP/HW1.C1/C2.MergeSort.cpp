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
		buffArr[firstBegin]~buffArr[firstLast], buffArr[firstLast+1]~buffArr[secondLast] �� ���� ���� ���ڵ��� �̹� ���ĵǾ� �ִ�.
		���� ���� ������ arr1, ���� ������ arr2��� �����Ѵٸ�,
		arr1[firstBegin]�� ���� arr1�� ���� �� �ּҰ��̰�,
		arr2[firstLast+1]�� ���� arr2�� ���� �� �ּҰ��̴�.
		���� �� �������� arr1Idx�� arr1�� �ּҰ��� ����Ű��, arr2Idx�� arr2�� �ּҰ��� ����Ų��.
		���� �� �ܰ迡�� loop invariant�� TRUE�̴�.
	*/
	for (idx = firstBegin; idx <= secondLast; idx++)
	{
		/*
			Maintenance
			arr1[arr1Idx] <= arr2[arr2Idx] ��� �����Ѵ�.
			arr1[arr1Idx]�� ���� arr���� ������� ���� ���� ���� �����̴�.
			���� �� ���� ����� ���ҵ��� ��� arr1[arr1Idx]���� �۰ų� ����.
			���� arr1[arr1Idx]�� ����Ǹ� arr�� ������ �� �� �þ�� ���� ���¸� �����Ѵ�.

			���� arr1[arr1Idx]�� ������ �� arr1Idx�� ���� 1 ������Ų��.
			���� arr1[arr1Idx-1]���� ũ�ų� ���� ���ο� arr1[arr1Idx]�� ����Ű�� �ǰ�, �ٽ� Maintenence�� ù �ܰ�� ���ư� ���� ���� �� �ִ�.
			���� arr1[arr1Idx-1]�� arr1�� ����Ǿ����Ƿ� arr1[arr1Idx]�� ���� �ٽ� arr1�� ���� �� ���� ���� ���� �Ǿ� �ʱ� ������ �����Ѵ�.

			�ݴ��� ��쵵 ���������̴�.
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
		idx > secondLast�� ������ �� ����
		idx - -1 == secondLast �̹Ƿ� buffArr�� ��� ���ҿ� �����ؼ� arr���� ���縦 �Ϸ������� �� �� �ִ�
		���� �������� arr�� ����:
			���� ���� : secondLast - firstBegin + 1
			���� ���� : arr1�� arr2�� ���� �� ���� ���� (secondLast - firstBegin +1)��
			arr1�� arr2�� �����ִ�(������� ����) ����: 0��
			���Ļ��� ����
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
	/*������ 0���� ��Ȳ �׽�Ʈ*/
	int arr1[1] = {};
	int arr1Buff[1] = {};
	std::cout << "���� �� : ";
	printArr(arr1, 0);
	MergeSort(arr1, arr1Buff, 0, 0);
	std::cout << "���� �� : ";
	printArr(arr1, 0);
	std::cout << "��� : " << isSorted(arr1, 0) << std::endl;

	/*������ 1���� ��Ȳ �׽�Ʈ*/
	int arr2[1] = { 4 };
	int arr2Buff[1] = { 0 };
	std::cout << "���� �� : ";
	printArr(arr2, 1);
	MergeSort(arr2, arr2Buff, 0, 0);
	std::cout << "���� �� : ";
	printArr(arr2, 1);
	std::cout << "��� : " << isSorted(arr2, 1) << std::endl;

	/*������ 2���� ��Ȳ + ���Ҽ� �׽�Ʈ*/
	int arr3[2] = { 4, 0 };
	int arr3Buff[2] = { 0 };
	std::cout << "���� �� : ";
	printArr(arr3, 2);
	MergeSort(arr3, arr3Buff, 0, 1);
	std::cout << "���� �� : ";
	printArr(arr3, 2);
	std::cout << "��� : " << isSorted(arr3, 2) << std::endl;

	/*������ 20���� ��Ȳ + ���� + ������ ���� �׽�Ʈ*/
	int arr4[20] = { 4, 4, 4, 4, 4, 3, 3, 5, 7, 9, 1, 3, 6, 0, 6, 3, 2, 6, 8, 3 };
	int arr4Buff[20] = {0};
	std::cout << "���� �� : ";
	printArr(arr4, 20);
	MergeSort(arr4, arr4Buff, 0, 19);
	std::cout << "���� �� : ";
	printArr(arr4, 20);
	std::cout << "��� : " << isSorted(arr4, 20) << std::endl;

	getchar();
}