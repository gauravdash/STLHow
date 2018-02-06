// part of the <utility>
// pair utility class

namespace STLHow
{

template <typename F, typename S>
class pair
{
    public :

		// the internal data is freely accessible
		F first;
		S second;

		// default constructor, calls default constructor of the members
		pair() : first( F() ), second( S() )
		{ }

		// constructor for values of the same types
		//pair(const F &f, const S &s) : first( f ), second( s )
		//{ }

		// constructor for values of different types
		// TODO: can this constructor substitute the one for the same types?
		template <typename U, typename V>
		pair(const U &u, const V &v) : first( u ), second( v )
		{ }
};

template <typename F, typename S>
bool operator==(const pair<F, S> &lhs, const pair<F, S> &rhs)
{
	return (lhs.fist == rhs.first) && (lhs.second == rhs.second);
}

template <typename F, typename S>
pair<F, S> make_pair(const F &f, const S &s)
{
	return pair<F, S>(f, s);
}

} // end namespace STLHow