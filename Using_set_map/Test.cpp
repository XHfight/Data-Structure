#include <iostream>
#include <set>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

namespace Test_set
{
	void TestInsert()
	{
		set<int> s1;
		set<int>::iterator setIt;
		pair<set<int>::iterator, bool> ret;
		//����1:ֱ�Ӳ���key
		s1.insert(1);
		s1.insert(10);
		s1.insert(5);
		s1.insert(7);
		ret = s1.insert(10);  //�Ѿ����ڣ�����ʧ��

		//�����:���õ���������
		if (ret.second == false)
			setIt = ret.first;
		s1.insert(setIt, 6);

		//������:����һ������������
		list<int> l1;
		l1.push_back(34);
		l1.push_back(33);
		l1.push_back(32);
		l1.push_back(31);
		list<int>::iterator listIt = l1.begin();
		s1.insert(listIt, l1.end()); //��list�ĵ������������

		//�������
		setIt = s1.begin();
		while (setIt != s1.end())
		{
			cout << *setIt << " ";
			++setIt;
		}
	}
	void TestErase()
	{
		set<int> s1;
		set<int>::iterator setIt;
		for (int i = 10; i > 0; --i)
			s1.insert(i);
		//ɾ��һ:���õ�����ɾ��(�޷���ֵ)
		setIt = s1.begin();//setItָ��1
		s1.erase(setIt);

		//ɾ����:����keyֵɾ����ɾ���ɹ�����1��ʧ�ܷ���0��
		size_t ret1 = s1.erase(10);
		size_t ret3 = s1.erase(5);
		size_t ret2 = s1.erase(20);
		cout << "ɾ��������ֵ:";
		cout << ret1 << " " << ret2 << " " << ret3 << endl;

		//ɾ������ɾ��һ�ε���������
		setIt = s1.find(50);
		setIt = s1.find(7);
		s1.erase(setIt, s1.end());

		//����
		cout << "����set:";
		setIt = s1.begin();
		while (setIt != s1.end())
		{
			cout << *setIt << " ";
			++setIt;
		}
	}
	void TestFind()
	{
		set<int> s1;
		set<int>::iterator setIt;
		for (int i = 10; i > 0; --i)
			s1.insert(i);

		setIt = s1.find(8); //����
		cout << *setIt << endl;
		setIt = s1.find(20); //������
		cout << (setIt == s1.end()) << endl; //��ӡ1��˵������ֵΪend()
	}
}

namespace Test_map
{
	void PrintMap(map<string, int>& m)
	{
		map<string, int>::iterator it = m.begin();
		while (it != m.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
	}

	void TestInsert()
	{
		map<string, int> wordCount;
		//ʾ�����뷽ʽ֮һ������pairԪ�أ�������set����
		wordCount.insert(pair<string, int>("hello", 1));
		wordCount.insert(pair<string, int>("world", 3));
		wordCount.insert(pair<string, int>("aaa", 7));
		wordCount.insert(pair<string, int>("bbb", 1));
		PrintMap(wordCount); //����map�ĺ���
	}

	//ͳ�Ƴ��ִ�������ǰK��ˮ��
	void TopK(vector<string>& fruits)
	{
		//ͳ��ˮ�����ֵĴ���
		map<string, int> fruitCount;
		size_t size = fruits.size();
		for (size_t i = 0; i < size; ++i)
		{
			fruitCount[fruits[i]]++;
		}

		//����
		vector<map<string, int>::iterator> v; //�����ݱ����ڿ���������ʵ������
		map<string, int>::iterator it = fruitCount.begin();
		while (it != fruitCount.end())
		{
			v.push_back(it);
			++it;
		}

		struct CMP
		{
			bool operator()(const map<string, int>::iterator l,
							const map<string, int>::iterator r) const
			{
				return (l->second > r->second);
			}
		};
		sort(v.begin(), v.end(), CMP());
		
		//���������
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i]->first << "-" << v[i]->second << endl;
		}
		
	}

	void TestFruitCount()
	{
		vector<string> fruits;
		fruits.push_back("ƻ��");
		fruits.push_back("��");
		fruits.push_back("ƻ��");
		fruits.push_back("�㽶");
		fruits.push_back("����");
		fruits.push_back("ƻ��");
		fruits.push_back("ƻ��");
		fruits.push_back("��");
		fruits.push_back("����");
		fruits.push_back("����");
		fruits.push_back("⨺���");
		fruits.push_back("����");
		fruits.push_back("⨺���");
		fruits.push_back("⨺���");
		fruits.push_back("����");
		fruits.push_back("�㽶");
		fruits.push_back("����");
		fruits.push_back("�㽶");

		TopK(fruits);
	}

}
int main()
{
	//Test_set::TestInsert();
	//Test_set::TestErase();
	//Test_set::TestFind();
	//Test_map::TestInsert();
	Test_map::TestFruitCount();
	system("pause");
	return 0;
}


