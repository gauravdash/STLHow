// Copyright (c) 2014 Gaurav Dasharathe
// codefreakr.com

// part of <map>
// implementation of map

#ifndef _MAP_H
#define _MAP_H

#include "tree_internal.h"
#include "key_comp_pair.h"

namespace STLHow
{
	template <typename K, typename V>
	class map
	{
	    public:

			// the key of any element is unmodifyable
			typedef key_comp_pair<const K, V> pair_type;

			map() : tree(false /*allowDuplicate*/) { }

			V &operator[](const K &k)
			{
				// map inserts a default constructed value
				// if one is not found to already exist
				// here you see, it is this
				V dummy = V();
				pair_type in(k, dummy);
				pair_type &out = tree.insert(in);
				return out.second;
			}

			void print()
			{
				tree.printPreOrder();
			}
					

			class iterator
			{
			    public:
					iterator(pair_type *p)
						: pos(p) { }

					iterator() 
						: pos(0) { }

					V &operator*()
					{ return *pos; }

					V *operator->()
					{ return pos; }

					iterator operator++(int)
					{ pos--; return *this; }

					iterator operator--(int)
					{ pos++; return *this; }

					bool operator!=(const iterator &rhs)
					{ return this->pos != rhs.pos; }
					
			    private:
					
					pair_type *pos;
			};
			
	    private:
						
			Tree<pair_type> tree;
	};

} // namespace STLHow

#endif