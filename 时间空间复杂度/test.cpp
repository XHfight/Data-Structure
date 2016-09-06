#include <iostream>
#include <cassert>
using namespace std;

//���ֲ��ң��ݹ飩
//ʱ�临�Ӷ�:O(log2(N))   �ռ临�Ӷȣ�O(1)
int BinarySearch(int *_arr, int search, int left, int right)
{
	assert(left >= 0);
	int mid = (right - left) / 2 + left;
	if (left <= right)
	{
		if (_arr[mid] == search)
		{
			return mid;
		}
		else if (_arr[mid] > search)
		{
			BinarySearch(_arr, search, left, mid - 1);
		}
		else
		{
			BinarySearch(_arr, search, mid + 1, right);
		}
	}
	else
	{
		return -1;
	}
}

//�����������ǵݹ飩
//ʱ�临�Ӷȣ�O(n)   �ռ临�Ӷȣ�O(1)
unsigned long long Fib(long long n)
{
	unsigned long long ret = 0;
	unsigned long long fir = 0, sec = 1;
	assert(n >= 0);
	if (n == 0 || n == 1)
	{
		return n;
	}
	for (long long i = 2; i <= n; ++i)
	{
		ret = fir + sec;
		fir = sec;
		sec = ret;
	}
	return ret;
}


int main()
{
	//cout << Fib(3) << endl;
	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << BinarySearch(arr, 10, 0, 9) << endl;
	cout << BinarySearch(arr, 3, 0, 9) << endl;

	system("pause");
	return 0;
}