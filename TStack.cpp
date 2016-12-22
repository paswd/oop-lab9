#include "TStack.h"
#include <exception>
#include <functional>

template <class T> TStack<T>::TStack() : head(NULL) {
}

template <class T> std::shared_ptr<T> TStack<T>::operator[](size_t i) {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
	if (i > size() - 1) throw std::invalid_argument("index greater then stack size");
	size_t j = 0;
	for (std::shared_ptr<T> a : * this) {
		if (j == i) {
			return a;
		}
		j++;
	}
	return std::shared_ptr<T>(NULL);
}

template <class T> std::ostream& operator<<(std::ostream& os, const TStack<T>& stack) {
	std::shared_ptr<TStackItem<T>> item = stack.head;

	while(item != NULL) {
		os << *item;
		item = item->GetNext();
	}

	return os;
}
template <class T> void TStack<T>::push(T *item) {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
	std::shared_ptr<TStackItem <T>> other(new TStackItem<T>(item, &stack_mutex));
	other->SetNext(head);
	head = other;
}
template <class T> void TStack<T>::push(std::shared_ptr<T> item) {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
	std::shared_ptr<TStackItem < T >> other(new TStackItem<T>(item,&stack_mutex));
	other->SetNext(head);
	head = other;
}
template <class T> bool TStack<T>::empty() {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
	return head == NULL;
}
template <class T> size_t TStack<T>::size() {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
 	int result = 0;
 	for (auto i : * this) {
 		result++;
 	}
 	return result;
}
template <class T> std::shared_ptr<T> TStack<T>::pop() {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
	std::shared_ptr<T> result;
	if (head != NULL) {
		result = head->GetItem();
		head = head->GetNext();
	}
	return result;
}
template <class T> std::shared_ptr<T> TStack<T>::pop_last() {
	std::lock_guard<std::recursive_mutex> lock(stack_mutex);
	std::shared_ptr<T> result;
	if (head != NULL) {
		std::shared_ptr<TStackItem < T>> element = head;
		std::shared_ptr<TStackItem < T>> prev = NULL;
		while (element->GetNext() != NULL) {
			prev = element;
			element = element->GetNext();
		}
		if (prev != NULL) {
			prev->SetNext(NULL);
			result = element->GetItem();
		} else {
			result = element->GetItem();
			head = NULL;
		}
	}
	return result;
}

template <class T> TIterator<TStackItem<T>,T> TStack<T>::begin() const
{
	return TIterator<TStackItem<T>,T>(head);
}
template <class T> TIterator<TStackItem<T>,T> TStack<T>::end() const
{
	return TIterator<TStackItem<T>,T>(NULL);
}

template <class T> TStack<T>::~TStack() {

}


template class TStack<Figure>;
//template class TStack<std::function<void(void)>>;
template std::ostream& operator<<(std::ostream& os, const TStack<Figure> &stack);
