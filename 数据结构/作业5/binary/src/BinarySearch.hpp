#ifndef _BINARY_SEARCH_HPP_
#define _BINARY_SEARCH_HPP_

#include <functional>

namespace My {

    template <typename Val, class RandomAccessIter>
    RandomAccessIter lower_bound(RandomAccessIter first, RandomAccessIter last, Val key) {
        return lower_bound(first, last, ::std::less<Val>());
    }

    template <typename Val, class RandomAccessIter, typename Cmp>
    RandomAccessIter lower_bound(RandomAccessIter first, RandomAccessIter last, Val key, Cmp cmp) {
        while (first < last) {
            RandomAccessIter mid = first + (last - first) / 2;
            if (cmp(*mid, key))
                first = mid + 1;
            else
                last = mid;
        }
        return first; // return end;
    }

    template <typename Val, class RandomAccessIter>
    RandomAccessIter upper_bound(RandomAccessIter first, RandomAccessIter last, Val key) {
        return upper_bound(first, last, ::std::less<Val>());
    }

    template <typename Val, class RandomAccessIter, typename Cmp>
    RandomAccessIter upper_bound(RandomAccessIter first, RandomAccessIter last, Val key, Cmp cmp) {
        while (first < last) {
            RandomAccessIter mid = first + (last - first) / 2;
            if (cmp(key, *mid))
                last = mid;
            else
                first = mid + 1;
        }
        return first; // return end;
    }

    template <typename Val, class RandomAccessIter, typename Cmp>
    ::std::pair<RandomAccessIter, RandomAccessIter> equal_range(RandomAccessIter first, RandomAccessIter last, Val key, Cmp cmp = ::std::less<Val>()) {
        return ::std::make_pair(lower_bound(first, last, key, cmp), upper_bound(first, last, key, cmp));
    }

    template <typename Val, class RandomAccessIter>
    ::std::pair<RandomAccessIter, RandomAccessIter> equal_range(RandomAccessIter first, RandomAccessIter last, Val key) {
        return ::std::make_pair(lower_bound(first, last, key), upper_bound(first, last, key));
    }
    
    template <typename Val, class RandomAccessIter, typename Cmp>
    RandomAccessIter lower_bound_rec(RandomAccessIter first, RandomAccessIter last, Val key, Cmp cmp = ::std::less<Val>()) {
        if (first == last)
            return first; // return last;
        
        RandomAccessIter mid = first + (last - first) / 2;
        if (cmp(*mid, key))
            return lower_bound_rec(mid + 1, last, key, cmp);
        else
            return lower_bound_rec(first, mid, key, cmp);
    }

    template <typename Val, class RandomAccessIter, typename Cmp>
    RandomAccessIter upper_bound_rec(RandomAccessIter first, RandomAccessIter last, Val key, Cmp cmp = ::std::less<Val>()) {
        if (first == last)
            return first; // return last;
        
        RandomAccessIter mid = first + (last - first) / 2;
        if (cmp(key, *mid))
            return upper_bound_rec(first, mid, key, cmp);
        else
            return upper_bound_rec(mid + 1, last, key, cmp);
    }

} // namespace My

#endif // _BINARY_SEARCH_HPP_