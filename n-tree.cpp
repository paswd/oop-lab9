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
/*template <class T> std::shared_ptr<T> NTree<T>::Pop(std::shared_ptr<T> ptr) {
	std::shared_ptr<NTreeNode<T>> ths = this->Root;
	std::shared_ptr<NTreeNode<T>> prev = NULL;
	bool found = false;
	found_pos = 0;
	std::shared_ptr<NTreeNode<T>> found_ptr = NULL;
	while (ths != NULL) {
		for (size_t i = 0; i < ths->ClustersCnt; i++) {
			if (ths->Clusters[i] == ptr) {
				found = true;
				found_pos = i;
				found_ptr = ths;
				break;
			}
		}
		if (found) {
			break;
		}
		prev = ths;
		ths = ths->Child;
	}
	if (!found) {
		return NULL;
	}
	while (ths != NULL) {
		size_t i = 0;
		if (ths == found_ptr) {
			i = found_pos;
		}
		for(; i < ths->ClustersCnt; i++) {
			if (i == 0) {
				if (ths->Parent != NULL) {
					size_t tmp_pos = ths->Parent->ClustersCnt;
					ths->Parent->Clusters[tmp_pos - 1] = ths->Clusters[i];
				}
			} else {
				ths->Clusters[i - 1] = ths->Clusters[i];
			}
		}
		prev = ths;
		ths = ths->Child;
	}
	ths = prev;
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
	return ptr;
}*/
template <class T> bool NTree<T>::IsEmpty(void) {
	return this->Root == NULL;
}

/*template <class T> std::ostream& operator<<(std::ostream& os, const NTree<T>& ntree) {
	std::shared_ptr<NTreeNode<T>> item = ntree.Root;
	while (item != NULL) {
		for (size_t i = 0; i < item->ClustersCnt; i++) {
			os << item->Clusters[i] << endl;
		}
	}
	return os;
}*/

template class NTree<std::function<void(void)>>;
//template std::ostream& operator<<(std::ostream& os, const NTree<std::function<void(void)>> &ntree);