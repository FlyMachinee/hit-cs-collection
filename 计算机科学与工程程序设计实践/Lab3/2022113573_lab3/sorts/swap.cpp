#ifndef SWAP_CPP_INCLUDED
#define SWAP_CPP_INCLUDED

template <typename T> void my_swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

#endif
