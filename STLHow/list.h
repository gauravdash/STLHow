// Copyright (c) 2014 Gaurav Dasharathe

// part of <list>
// implementation of list

#ifndef _LIST_H_
#define _LIST_H_

#include <ostream>

namespace STLHow
{
	template <typename T>
	struct ListNode
	{
		ListNode(const T &e) : data(e),
			                   next(0), prev(0)
		{ }

		T data;
		ListNode<T> *next;
		ListNode<T> *prev;
	};

	template <typename T>
	class list
	{
	public:
		list() : head_(0), tail_(0),
			     size_(0)
		{ }

		T &front()
		{ return head_->data; }

		T &back()
		{ return tail_->data; }

		void push_back(const T &e);
		void push_front(const T&e);
		
		void pop_front();
		void pop_back();

		~list();

		int size() { return size_; }

		class iterator
		{
		public:
			iterator(ListNode<T> *p=0) : pos_(p) { }
			
			T &operator*()
			{ return pos_->data; }

			T *operator->()
			{ return &(pos_->data); }

			bool operator!=(const iterator &rhs)
			{ return this->pos_ != rhs.pos_; }

			iterator operator++(int)
			{ pos_ = pos_->next; return *this; }

			iterator operator--(int)
			{ pos_ = pos_->prev; return *this; }

		private:
			ListNode<T> *pos_;
		};

		iterator insert(const iterator &pos, const T &e);
		iterator erase(const iterator &pos);

		iterator begin()
		{ return iterator(head_); }

		iterator end()
		{ return iterator(0); }

		class reverse_iterator
		{
		public:
			reverse_iterator(ListNode<T> *p=0) : pos_(p) { }
			
			T &operator*()
			{ return pos_->data; }

			T *operator->()
			{ return &(pos_->data); }

			bool operator!=(const reverse_iterator &rhs)
			{ return this->pos_ != rhs.pos_; }

			reverse_iterator operator++(int)
			{ pos_ = pos_->prev; return *this; }

			reverse_iterator operator--(int)
			{ pos_ = pos_->next; return *this; }

		private:
			ListNode<T> *pos_;
		};

		reverse_iterator rbegin()
		{ return reverse_iterator(tail_); }

		reverse_iterator rend()
		{ return reverse_iterator(0); }

		friend std::ostream &operator<< <T>(std::ostream &os, const list<T> &lst);

	private:
		ListNode<T> *insertInternal(const T &e, ListNode<T> *pos);
		void removeInternal(ListNode<T> *pos);

		ListNode<T> *head_;
		ListNode<T> *tail_;

		int size_;
	};

	template <typename T>
	list<T>::~list()
	{
		ListNode<T> *current( head_ );

		while(current)
		{
			ListNode<T> *next( current->next );
			delete current;
			current = next;
		}
	}


	template <typename T>
	ListNode<T> *list<T>::insertInternal(const T &e, ListNode<T> *pos)
	{
		ListNode<T> *n = new ListNode<T>(e);

		size_++;
		// no operation below this should throw
		// as state of the list has changed and memory allocated

		n->next = pos;

		if(pos)
		{
			n->prev = pos->prev;
			pos->prev = n;
		}
		else
		{
			// pos is null that is at the very end of the list
			n->prev = tail_;
			tail_ = n;
		}

		if(n->prev)
		{
			n->prev->next = n;
		}
		else
		{
			// at the very begining of the list
			head_ = n;
		}

		return n;
	}

	template <typename T>
	void list<T>::removeInternal(ListNode<T> *pos)
	{
		if(pos)
		{
			if(pos->prev)
				pos->prev->next = pos->next;

			if(pos->next)
				pos->next->prev = pos->prev;

			if(pos == head_)
				head_ = pos->next;

			if(pos == tail_)
				tail_ = pos->prev;

			delete pos;

			size_--;
		}
	}

	template <typename T>
	void list<T>::push_back(const T &e)
	{
		// inserts before the position, 
        // 0 is the end() iterator
		// hence insert at the end
		insertInternal(e, 0);
	}

	template <typename T>
	void list<T>::push_front(const T &e)
	{
		// insert before the head
		insertInternal(e, head_);
	}

	template <typename T>
	void list<T>::pop_back()
	{
		removeInternal(tail_);
	}

	template <typename T>
	void list<T>::pop_front()
	{		
		removeInternal(head_);
	}

	template <typename T>
	typename list<T>::iterator list<T>::insert(const iterator &pos, const T&e)
	{
		// insert before pos and return iterator to the new element
		ListNode<T> *n = insertInternal(e, pos);
		return iterator(n);
	}

	template <typename T>
	typename list<T>::iterator list<T>::erase(const iterator &pos)
	{
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const list<T> &lst)
	{
		ListNode<T> *current( lst.head_ );

		os << "head -> ";

		while(current)
		{
			os << current->data << " ";
			current = current->next;
		}

		os << "<- tail" << std::endl;

		return os;
	}
}

#endif