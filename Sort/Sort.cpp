#include <iostream>
#include <cassert>
using namespace std;

void PrintArr(int* arr, size_t size)
{
	for(size_t i = 0; i < size; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//��������
void InsertSort(int* arr, size_t size)
{
	assert(arr);
	for(size_t j = 1; j < size; ++j)//Ҫ�������ݵ�λ��
	{
		int insert = arr[j]; //Ҫ���������
		int i = j-1;
		for( ; i >= 0 ;--i) //���˲���
		{
			if(arr[i] > insert)
				arr[i+1] = arr[i];
			else
				break;
		}
		arr[i+1] = insert;
	}
}

void TestInsertSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	InsertSort(arr, sizeof(arr)/sizeof(arr[0]));
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

//ϣ������
void ShellSort(int* arr, size_t size)
{
	assert(arr);
	int gap = size;
	while(gap != 1)
	{
		gap = gap/3 + 1;
		for(size_t j = gap; j < size; ++j)
		{
			int insert = arr[j];
			int i = j-gap;
			for( ; i>=0; i-=gap)
			{
				if(arr[i] > insert)
					arr[i+gap] = arr[i];
				else
					break;
			}
			arr[i+gap] = insert;
		}
	}
}
void TestShellSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	ShellSort(arr, sizeof(arr)/sizeof(arr[0]));
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

void SelectSort(int* arr, size_t size)
{
	assert(arr);
	int left = 0;
	int right = size-1;
	while(left < right)
	{
		size_t max = left; //��¼���ֵ���±�
		size_t min = left;
		for(int i = left; i <= right; ++i)
		{
			if(arr[i] > arr[max])
				max = i;
			if(arr[i] < arr[min])
				min = i;
		}
		swap(arr[left], arr[min]);
		//ע�⣺��ֹ����Ľ���ʹmaxֵ����ȷ��
		//��max��ֵΪ��ʱ����������maxֵ�ı䣬����Ҫ������
		if(left == max) 
			max = min;
		swap(arr[right], arr[max]);
		left++;
		right--;
	}
}
void TestSelectSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	SelectSort(arr, sizeof(arr)/sizeof(arr[0]));
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

void AdjustDown(int* arr, size_t size, size_t parent)
{
	size_t child = parent*2+1;
	while(child < size)
	{
		if(child+1<size && arr[child+1] > arr[child])
			++child;
		if(arr[parent] < arr[child])
			swap(arr[parent], arr[child]);
		else
			break;
		parent = child;
		child = parent*2+1;
	}
}

//������
void HeapSort(int* arr, size_t size)
{
	assert(arr);
	//����
	int parent = (size-1-1)/2;
	while(parent >= 0)
	{
		AdjustDown(arr, size, parent);
		parent--;
	}
	//����
	int index = size-1;//��¼������λ��
	while(index>0)
	{
		swap(arr[0], arr[index]);
		AdjustDown(arr, index, 0);
		--index;
	}
}

void TestHeapSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	HeapSort(arr, sizeof(arr)/sizeof(arr[0]));
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

void BubbleSort(int* arr, size_t size)
{
	assert(arr);
	for(size_t i = 0; i<size-1; ++i)
	{
		for(size_t j = 1; j < size-i; ++j)
		{
			if(arr[j-1] > arr[j])
			{
				swap(arr[j-1],arr[j]);
			}
		}
	}
}
void TestBubbleSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	BubbleSort(arr, sizeof(arr)/sizeof(arr[0]));
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

//��������
//�Ż�һ������ȡ�з�
size_t GetMid(int* arr, size_t left, size_t right)
{
	size_t mid = left+((right-left)>>2);
	if(arr[left] < arr[mid])
	{
		if(arr[mid] < arr[right])
			return mid;
		else if(arr[left] < arr[right])
			return right;
		else
			return left;
	}
	else  //left��
	{
		if(arr[left] < arr[right])
			return left;
		else if(arr[right] < arr[mid])
			return mid;
		else
			return right;
	}
}
//��1������ָ��
size_t PartSort1(int* arr, size_t left, size_t right)
{
	size_t key = right;
	size_t mid = GetMid(arr, left, right);
	if(key != mid)
		swap(arr[key], arr[right]);
	while(left < right)
	{
		//left�Ҵ�
		while(left < right && arr[left] <= arr[key])
			++left;
		while(left < right && arr[right] >= arr[key])
			--right;
		swap(arr[left], arr[right]);
	}
	if(right != key)
		swap(arr[left], arr[key]);
	return left;
}

//��2���ڿӷ�
size_t PartSort2(int* arr, size_t left, size_t right)
{
	int key = arr[right];
	while(left < right)
	{
		while(left < right && arr[left] <= key)
			++left;
		arr[right] = arr[left];

		while(left < right && arr[right] >= key)
			--right;
		arr[left] = arr[right];
	}
	//right == left
	arr[right] = key;
	return right;
}

//��3��ǰ��ָ�뷨
size_t PartSort3(int* arr, int left, int right)
{
	int cur = left-1;
	int prev = left-1;
	int key = right;
	while(cur < right)
	{
		while(cur < right && arr[++cur] >= arr[key]);//cur��С
		++prev;
		swap(arr[prev], arr[cur]);
	}
	return prev;
}

void QuickSort(int* arr, size_t left, size_t right)
{
	assert(arr);
	if(right-left > 0)
	{
		int div = PartSort3(arr, left, right);
		//[left, div-1] [div+1, right]
		if(div != left) //ע�⣺��divΪ�߽�ʱ���߽��һ�߲���Ҫ��������
			QuickSort(arr, left, div-1);
		if(div != right)
			QuickSort(arr, div+1, right);
	}
}

void TestQuickSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	QuickSort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

//�鲢����

//[left, right]
void MSort(int* arr,int* tmp, int left, int right)
{
	if(right - left > 0)
	{
		int mid = left+(right-left)/2;
		MSort(arr, tmp, left, mid);
		MSort(arr, tmp, mid+1, right);
		
		//�ϲ�
		int begin1 = left, end1 = mid;
		int begin2 = mid+1, end2 = right;
		int i = left;
		while(begin1<=end1 && begin2<= end2)
		{
			if(arr[begin1] < arr[begin2])
			{
				tmp[i++] = arr[begin1];
				++begin1;
			}
			else
			{
				tmp[i++] = arr[begin2];
				++begin2;
			}
		}
		while(begin1 <= end1)
		{
			tmp[i++] = arr[begin1];
			++begin1;
		}
		while(begin2 <= end2)
		{
			tmp[i++] = arr[begin2];
			++begin2;
		}
		for(int j = left; j <= right; ++j)
		{
			arr[j] = tmp[j];
		}
	}

}
void MergeSort(int* arr, size_t size)
{
	assert(arr);
	int* tmp = new int[size];
	MSort(arr, tmp, 0, size-1);
	delete[] tmp;
}

void TestMergeSort()
{
	int arr[] = {3, 5, 7, 2, 4, 9, 1, 0, 8, 6};
	MergeSort(arr,sizeof(arr)/sizeof(arr[0]));
	PrintArr(arr,sizeof(arr)/sizeof(arr[0]));
}

int main()
{
	TestInsertSort();
	TestShellSort();
	TestSelectSort();
	TestBubbleSort();
	TestHeapSort();
	TestQuickSort();
	TestMergeSort();
	return 0;
}