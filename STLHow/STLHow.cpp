// Copyright (c) 2014 Gaurav Dasharathe

// STLHow.cpp : Defines the entry point for the console application.
//

#include "vector.h"
#include "map.h"
#include "tree_internal.h"
#include "list.h"

#include <iostream>
#include <string>

using namespace STLHow;

void testVector()
{
	vector<int> v;
	for(int i=0; i<10; i++)
		v.push_back(i);

	for(int i=0; i<10; i++)
		std::cout << v[i] << std::endl;

	vector<int>::reverse_iterator iter;
	for(iter=v.rbegin(); iter!=v.rend(); iter++)
		std::cout << *iter << std::endl;
}

void testAlgorithm()
{
	std::cout << "min(3, 4) : " << min(3, 4) << std::endl; 
	std::cout << "max(3, 4) : " << max(3, 4) << std::endl;
}


void testMapTreeInternal()
{
	std::cout << "testMapTreeInternal begin" << std::endl;

	key_comp_pair<int, int> kcp1(3, 2);
	key_comp_pair<int, int> kcp2(4, 1);

	std::cout << "kcp1(3, 2) < kcp2(4, 1) : "
		      <<  (kcp1 < kcp2) << std::endl;

	Tree<int> tree(false);

	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	tree.insert(33);
	tree.insert(53);
	tree.insert(62);
	tree.insert(98);
	tree.insert(16);
	tree.insert(72);


	//Node<int> *i = tree.find(6);
	//std::cout << tree.inorderNext(i)->data << std::endl;

	tree.remove(62);


	tree.printPreOrder();
	tree.printDot();

	//map<int, int> m;
	//for(int i=0; i<109; i++)
	//    m[i] = i;

	////m.print();

	//for(int i=0; i<109; i++)
	//	std::cout << i << ":" << m[i] << std::endl;


	std::cout << "testMapTreeInternal end" << std::endl;
}

void testList()
{
	list<int> lst;
	
	lst.push_back(5);
	lst.push_back(6);
	lst.push_back(7);
	lst.push_back(8);
	lst.push_front(4);
	lst.push_front(3);
	lst.push_front(2);
	lst.push_front(1);
	
	std::cout << lst;

	std::cout << "front : " << lst.front() << std::endl;
	std::cout << "back : " << lst.back() << std::endl;

	std::cout << "pop_back" << std::endl;
	lst.pop_back();
	std::cout << lst;

	std::cout << "pop_front" << std::endl;
	lst.pop_front();
	std::cout << lst;

	//list<int>::iterator iter = lst.begin();

	std::cout << "iterator" << std::endl;
	for(list<int>::iterator i=lst.begin(); i!=lst.end(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "reverse_iterator" << std::endl;
	for(list<int>::reverse_iterator i=lst.rbegin(); i!=lst.rend(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::cout << "STLHow" << std::endl;

	//testMapTreeInternal();

	//testAlgorithm();

	//testVector();

	testList();

	int dummy;
	std::cin >> dummy;

	return 0;
}




