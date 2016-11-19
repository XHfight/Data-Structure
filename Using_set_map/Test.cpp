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
		//插入1:直接插入key
		s1.insert(1);
		s1.insert(10);
		s1.insert(5);
		s1.insert(7);
		ret = s1.insert(10);  //已经存在，插入失败

		//插入二:利用迭代器插入
		if (ret.second == false)
			setIt = ret.first;
		s1.insert(setIt, 6);

		//插入三:插入一个迭代器区间
		list<int> l1;
		l1.push_back(34);
		l1.push_back(33);
		l1.push_back(32);
		l1.push_back(31);
		list<int>::iterator listIt = l1.begin();
		s1.insert(listIt, l1.end()); //将list的迭代器区间插入

		//正向遍历
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
		//删除一:利用迭代器删除(无返回值)
		setIt = s1.begin();//setIt指向1
		s1.erase(setIt);

		//删除二:根据key值删除（删除成功返回1，失败返回0）
		size_t ret1 = s1.erase(10);
		size_t ret3 = s1.erase(5);
		size_t ret2 = s1.erase(20);
		cout << "删除二返回值:";
		cout << ret1 << " " << ret2 << " " << ret3 << endl;

		//删除三：删除一段迭代器区间
		setIt = s1.find(50);
		setIt = s1.find(7);
		s1.erase(setIt, s1.end());

		//遍历
		cout << "遍历set:";
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

		setIt = s1.find(8); //存在
		cout << *setIt << endl;
		setIt = s1.find(20); //不存在
		cout << (setIt == s1.end()) << endl; //打印1，说明返回值为end()
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
		//示例插入方式之一，插入pair元素，其余与set类似
		wordCount.insert(pair<string, int>("hello", 1));
		wordCount.insert(pair<string, int>("world", 3));
		wordCount.insert(pair<string, int>("aaa", 7));
		wordCount.insert(pair<string, int>("bbb", 1));
		PrintMap(wordCount); //遍历map的函数
	}

	//统计出现次数最多的前K种水果
	void TopK(vector<string>& fruits)
	{
		//统计水果出现的次数
		map<string, int> fruitCount;
		size_t size = fruits.size();
		for (size_t i = 0; i < size; ++i)
		{
			fruitCount[fruits[i]]++;
		}

		//排序
		vector<map<string, int>::iterator> v; //将数据保存在可以随机访问的容器里。
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
		
		//输出排序结果
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i]->first << "-" << v[i]->second << endl;
		}
		
	}

	void TestFruitCount()
	{
		vector<string> fruits;
		fruits.push_back("苹果");
		fruits.push_back("梨");
		fruits.push_back("苹果");
		fruits.push_back("香蕉");
		fruits.push_back("葡萄");
		fruits.push_back("苹果");
		fruits.push_back("苹果");
		fruits.push_back("梨");
		fruits.push_back("葡萄");
		fruits.push_back("西瓜");
		fruits.push_back("猕猴桃");
		fruits.push_back("葡萄");
		fruits.push_back("猕猴桃");
		fruits.push_back("猕猴桃");
		fruits.push_back("柠檬");
		fruits.push_back("香蕉");
		fruits.push_back("柚子");
		fruits.push_back("香蕉");

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


