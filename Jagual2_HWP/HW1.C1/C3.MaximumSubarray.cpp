#include <iostream>
#include <limits>

typedef struct MaxSubArr
{
	int low;
	int high;
	int sum;
} MAXSUBARRAY;

MAXSUBARRAY FindMaxCrossingSubarray(int* arr, int high, int mid, int low)
{
	int leftSum = std::numeric_limits<int>::min();
	int maxLeft;
	int sum = 0;

	for (int leftIdx = mid; leftIdx >= low; leftIdx--)
	{
		sum += arr[leftIdx];
		if (sum > leftSum)
		{
			leftSum = sum;
			maxLeft = leftIdx;
		}
	}

	int rightSum = std::numeric_limits<int>::min();
	int maxRight;
	sum = 0;
	for (int rightIdx = mid + 1; rightIdx <= high; rightIdx++)
	{
		sum += arr[rightIdx];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxRight = rightIdx;
		}
	}
	MAXSUBARRAY tmp = {maxLeft, maxRight, leftSum + rightSum};
	return tmp;
}

MAXSUBARRAY FindMaximumSubarray(int* arr, int high, int low)
{
	int mid;
	if (high == low)
	{
		MAXSUBARRAY tmp = { low, high, arr[high] };
		return tmp;
	}
	else
	{
		mid = (high + low) / 2;
	}
	MAXSUBARRAY leftMax = FindMaximumSubarray(arr, mid, low);
	MAXSUBARRAY rightMax = FindMaximumSubarray(arr, high, mid+1);
	MAXSUBARRAY crossMax = FindMaxCrossingSubarray(arr, high, mid, low);
	
	if (leftMax.sum >= rightMax.sum && leftMax.sum >= crossMax.sum)
	{
		return leftMax;
	}
	else if (rightMax.sum >= leftMax.sum && rightMax.sum >= crossMax.sum)
	{
		return rightMax;
	}
	else
	{
		return crossMax;
	}
}

MAXSUBARRAY FindMaximumSubArrayNSquare(int* arr, int high)
{
	int maxSum = std::numeric_limits<int>::min();
	int maxLeft = 0;
	int maxRight = 0;
	
	for (int i = 0; i <= high; i++)
	{
		int sum = 0;
		for (int j = i; j <= high; j++)
		{
			sum += arr[j];
			if (sum > maxSum)
			{
				maxLeft = i;
				maxRight = j;
				maxSum = sum;
			}
		}
	}
	MAXSUBARRAY tmp = {maxLeft, maxRight, maxSum};
	return tmp;
}

void PrintMaxSubArray(int* arr, MAXSUBARRAY maxArr)
{
	std::cout << "Max Array : ";
	for (int i = maxArr.low; i <= maxArr.high; i++)
	{
		std::cout << arr[i];
		if (i != maxArr.high)
			std::cout << ", ";
	}
	std::cout << std::endl;
	std::cout << "Max Sum : " << maxArr.sum << std::endl;
}

int main()
{
	/*테스트 1 원소개수 0개*/
	int arr1[1] = { };
	int high1 = 0;
	int low1 = 0;
	std::cout << "테스트 1" << std::endl;
	PrintMaxSubArray(arr1, FindMaximumSubarray(arr1, high1, low1));
	PrintMaxSubArray(arr1, FindMaximumSubArrayNSquare(arr1, high1));

	/*테스트 2 원소개수 1개*/
	int arr2[1] = { -3 };
	int high2 = 0;
	int low2 = 0;
	std::cout << "테스트 2" << std::endl;
	PrintMaxSubArray(arr2, FindMaximumSubarray(arr2, high2, low2));
	PrintMaxSubArray(arr2, FindMaximumSubArrayNSquare(arr2, high2));

	/*테스트 3 원소개수 2개*/
	int arr3[2] = { 13, -3 };
	int high3 = 1;
	int low3 = 0;
	std::cout << "테스트 3" << std::endl;
	PrintMaxSubArray(arr3, FindMaximumSubarray(arr3, high3, low3));
	PrintMaxSubArray(arr3, FindMaximumSubArrayNSquare(arr3, high3));

	/*테스트 4 원소개수 4개*/
	int arr4[4] = { 13, -3, -25, 20 };
	int high4 = 3;
	int low4 = 0;
	std::cout << "테스트 4" << std::endl;
	PrintMaxSubArray(arr4, FindMaximumSubarray(arr4, high4, low4));
	PrintMaxSubArray(arr4, FindMaximumSubArrayNSquare(arr4, high4));

	/*테스트 5 원소개수 20개*/
	int arr5[20] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7, 1, -3, 4, -9};
	int high5 = 19;
	int low5 = 0;
	std::cout << "테스트 5" << std::endl;
	PrintMaxSubArray(arr5, FindMaximumSubarray(arr5, high5, low5));
	PrintMaxSubArray(arr5, FindMaximumSubArrayNSquare(arr5, high5));

	getchar();
}