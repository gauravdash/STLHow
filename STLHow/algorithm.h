// Copyright (c) 2014 Gaurav Dasharathe

// part of <algorithm>

#ifndef _ALGORITHM_H
#define _ALGORITHM_H

namespace STLHow
{
	// return max of the two, if both are equal return left
	template <typename T>
	const T &max(const T &l, const T &r)
	{
		return (l < r) ? r : l;
	}

	// return min of the two, if both are equal return left
	template <typename T>
	const T &min(const T &l, const T &r )
	{
        return !(r < l) ? l : r;
    }

} // namespace STLHow

#endif