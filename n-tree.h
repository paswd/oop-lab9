#ifndef NTREE_H
#define NTREE_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <memory>

template <class T> class NTreeNode {
public:
	std::vector <std::shared_ptr<T>> Clusters; //Элементы на одной высоте дерева
	std::shared_ptr<NTreeNode<T>> Parent; //Ссылка на родителя
	std::shared_ptr<NTreeNode<T>> Child; //Ссылка на потомка
	size_t Level; //Текущая высота
	size_t ClustersCnt;

	NTreeNode(void);
	~NTreeNode(void);
};

template <class T> class NTree {
public:
	std::shared_ptr<NTreeNode<T>> Root; //Корень дерева
	size_t NConst; //Максимальное число потомков у одного листа

	//Methods
	NTree(void); //Конструктор
	~NTree(void); //Деструктор

	void Push(std::shared_ptr<T> element);
	std::shared_ptr<T> Pop(void);
	//std::shared_ptr<T> Pop(std::shared_ptr<T> ptr);

	bool IsEmpty(void);

	//template <class A> friend std::ostream& operator<<(std::ostream& os,const NTree<A>& ntree);
};

#endif /* FIGURE_H */
