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

//�鲢����

int main()
{
	TestInsertSort();
	TestShellSort();
	TestSelectSort();
	TestBubbleSort();
	TestHeapSort();
	return 0;
}