#include "GeneralLists.h"

GeneralList::Node* GeneralList::CreatList(const char*& str)
{
	assert(*str);
	++str;
	Node* head = new Node(HEAD);
	Node* cur = head;
	while(*str)
	{
		if(*str == '(')
		{
			Node* sub = new Node(SUB);
			cur->_next = sub;
			sub->_sub = CreatList(str);
			cur = sub;
		}
		else if(IsValue(*str))
		{
			Node* value = new Node(VALUE, *str);
			++str;
			cur->_next = value;
			cur = value;
		}
		else if(*str == ')')
		{
			++str;
			return head;
		}
		else
		{
			++str;
		}
	}
	return head;
}

bool GeneralList::IsValue(char value)
{
	if((value>='a'&&value<='z')
		||(value>='A'&&value<='Z')
		||(value>='0'&&value<='9'))
		return true;
	else
		return false;
}	

void GeneralList::Print(GeneralListNode* head)
{
	Node* cur = head;
	while (cur)
	{
		if (cur->_type == HEAD)
		{
			cout << "(";
		}
		else if (cur->_type == SUB)
		{
			Print(cur->_sub);
			if(cur->_next != NULL)
			{
				cout << ",";
			}
		}
		else
		{
			cout << cur->_value;
			if (cur->_next)
			{
				cout << ",";
			}
		}
		cur = cur->_next;
	}
	cout << ")";
}

GeneralList::Node* GeneralList::Copy(GeneralList::Node* head)
{
	Node* newHead = NULL;
	Node* newCur = NULL;
	Node* cur = head;
	while (cur)
	{
		if (cur->_type == HEAD)
		{
			newCur = new Node(HEAD);
			newHead = newCur;
			cur = cur->_next;
		}
		else if (cur->_type == SUB)
		{
			Node* node = new Node(SUB);
			newCur->_next = node;
			newCur = newCur->_next;

			node->_sub = Copy(cur->_sub);
			cur = cur->_next;
		}
		else //VALUE
		{
			Node* node = new Node(VALUE, cur->_value);
			newCur->_next = node;
			newCur = newCur->_next;

			cur = cur->_next;
		}
	}
	return newHead;
}

void GeneralList::Release(Node* head)
{
	if (head != NULL)
	{
		Node* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD || cur->_type == VALUE)
			{
				Node* del = cur;
				cur = cur->_next;
				delete del;
				del = NULL;
			}
			else // SUB
			{
				Release(cur->_sub);
				Node* del = cur;
				cur = cur->_next;
				delete del;
				del = NULL;
			}
		}
	}
	head = NULL;
}

size_t GeneralList::Count(Node* head)
{
	size_t count = 0;
	Node* cur = head;
	while (cur)
	{
		if (cur->_type == VALUE)
		{
			++count;
		}
		else if (cur->_type == SUB)
		{
			count += Count(cur->_sub);
		}
		cur = cur->_next;
	}
	return count;
}

size_t GeneralList::Dep(Node* node)
{
	size_t dep = 1;
	Node* cur = node;
	while (cur)
	{
		size_t nd = 1;
		if (cur->_type == SUB)
		{
			nd += Dep(cur->_sub);
		}

		if (nd > dep)
		{
			dep = nd;
		}
		cur = cur->_next;
	}
	return dep;
}
