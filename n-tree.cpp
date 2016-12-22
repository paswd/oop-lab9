#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "n-tree.h"

#define NTREE_CONST 5

using namespace std;


template <class T> NTreeNode<T>::NTreeNode(void) {
	this->ClustersCnt = 0;
}
template <class T> NTreeNode<T>::~NTreeNode(void) {
	
}


//=================================================

template <class T> NTree<T>::NTree(void) {
	this->Root = NULL;
	this->NConst = NTREE_CONST;
	//this->ClusterSize = cluster_size;
}

template <class T> NTree<T>::~NTree(void) {
	
}

template <class T> void NTree<T>::Push(std::shared_ptr<T> element) {
	if (this->Root == NULL) {
		std::shared_ptr<NTreeNode<T>> tmp(new NTreeNode<T>);
		this->Root = tmp;
		this->Root->Child = NULL;
		this->Root->Parent = NULL;
		this->Root->Level = 0;
		this->Root->Clusters.resize(1);
	}
	std::shared_ptr<NTreeNode<T>> ths = this->Root;
	while (ths->Child != NULL) {
		ths = ths->Child;
	}
	if (ths->ClustersCnt >= ths->Clusters.size()) {
		std::shared_ptr<NTreeNode<T>> tmp(new NTreeNode<T>);
		tmp->Child = NULL;
		tmp->Parent = ths;
		tmp->Level = ths->Level + 1;
		tmp->Clusters.resize(ths->Clusters.size() * this->NConst);
		ths->Child = tmp;
		ths = tmp;
	}
	ths->ClustersCnt++;
	ths->Clusters[ths->ClustersCnt - 1] = element;
}
template <class T> std::shared_ptr<T> NTree<T>::Pop(void) {
	std::shared_ptr<NTreeNode<T>> ths = this->Root;
	while (ths->Child != NULL) {
		ths = ths->Child;
	}
	std::shared_ptr<T> res = ths->Clusters[ths->ClustersCnt - 1];
	ths->ClustersCnt--;
	if (ths->ClustersCnt <= 0) {
		ths = ths->Parent;
		if (ths != NULL) {
			ths->Child = NULL;
		} else {
			this->Root = NULL;
		}
	}
	return res;
}
template <class T> bool NTree<T>::IsEmpty(void) {
	return this->Root == NULL;
}

template class NTree<std::function<void(void)>>;