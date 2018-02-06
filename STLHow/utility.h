// Copyright (c) 2014 Gaurav Dasharathe

// part of <utility>

#ifndef _UTILITY_H
#define _UTILITY_H

namespace STLHow
{
	template <typename F, typename S>
	struct pair
	{
		F first;
		S second;

		// create from constituents
		pair(const F &f, const S &s) : first(f), second(s) { }

		// create from another pair of possibly different types
		template <typename U, typename V>
		pair(const pair<U, V> &p) : first(p.first), second(p.second) { }
	};


	// short-hand function, so that template parameters are implicitly derived
	template <typename F, typename S>
	pair<F, S> make_pair(const F &f, const S &s)
	{
		return pair<F, S>(f, s);
	}

} // namespace STLHow

#endif