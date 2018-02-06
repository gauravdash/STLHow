// Copyright (c) 2014 Gaurav Dasharathe

// A pair which has its comparion and equality operators
// based on the 'first' ie. key
// used as an internal structure for map
// STL standard does not require this, it is an internal data structure

#ifndef _KEY_COMP_PAIR_H
#define _KEY_COMP_PAIR_H

#include "utility.h"

namespace STLHow
{
	template <typename K, typename V>
	struct key_comp_pair : public pair<K, V>
	{
		key_comp_pair(const K &k, const V &v)
			: pair(k, v)
		{ }

		bool operator<(const key_comp_pair<K, V> &rhs) const
		{ return this->first < rhs.first; } 

		bool operator>(const key_comp_pair<K, V> &rhs) const
		{ return this->first > rhs.first; }

		bool operator>=(const key_comp_pair<K, V> &rhs) const
		{ return this->first >= rhs.first; }

		bool operator==(const key_comp_pair<K, V> &rhs) const
		{ return this->first == rhs.first; } 
	};

	template <typename K, typename V>
	std::ostream &operator<<(std::ostream &os, const key_comp_pair<K, V> &p)
	{
		os << p.first <<":" << p.second;
		return os;
	}
	
} // namespace STLHow

#endif