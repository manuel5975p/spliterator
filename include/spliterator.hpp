#ifndef SPLITERATOR_HPP
#define SPLITERATOR_HPP
#include <iterator>
#include <iostream>
#include <list>
template<typename _iterator>
struct spliterator{
    using iterator_category = std::bidirectional_iterator_tag;
    using iterator = _iterator;
    spliterator(iterator begin, iterator end, typename std::iterator_traits<iterator>::value_type sc){
        range.first = begin;
        limit_begin = begin;
        limit_end = end;
        if(*begin != sc && begin < limit_end)
            while(begin < limit_end && *(++begin) != sc);
        range.second = begin;
        splitval = sc;
    }
    void rev_advance(){
        if(range.first == limit_begin)return;
        iterator newbeg = range.first;
        while(*(--newbeg) != splitval && newbeg > limit_begin);
        range.second = range.first - 1;
        range.first = newbeg;
    }
    void advance(){
        if(range.second == limit_end){
            range.first = range.second;
            return;
        }
        iterator newend = range.second + 1;
        while((*(newend) != splitval) && newend < limit_end){
            newend++;
        }
        range.first = range.second + 1;
        range.second = newend;
    }
    spliterator operator--(int){
        spliterator copy = *this;
        rev_advance();
        return copy;
    }
    spliterator& operator--(){
        rev_advance();
        return *this;
    }
    spliterator operator++(int){
        spliterator copy = *this;
        advance();
        return copy;
    }
    spliterator& operator++(){
        advance();
        return *this;
    }
    bool operator==(const spliterator<iterator>& o)const{
        return range.first == o.range.first && o.range.second == range.second;
    }
    bool operator!=(const spliterator<iterator>& o)const{
        return (range.first != o.range.first) || (o.range.second != range.second);
    }
    const std::pair<iterator, iterator>* operator->()const{
        return &range;
    }
    std::pair<iterator, iterator> operator*()const{
        return range;
    }
    private:
    iterator limit_begin;
    iterator limit_end;
    std::pair<iterator, iterator> range;
    typename std::iterator_traits<iterator>::value_type splitval;
};
template<typename _iterator>
struct split_range{
    using iterator = _iterator;
    split_range(iterator begin, iterator end, typename std::iterator_traits<iterator>::value_type sc){
        limit_begin = begin;
        limit_end = end;
        splitval = sc;
    }
    spliterator<iterator> begin()const{
        return spliterator<iterator>(limit_begin, limit_end, splitval);
    }
    spliterator<iterator> end()const{
        return spliterator<iterator>(limit_end, limit_end, splitval);
    }
    private:
    iterator limit_begin;
    iterator limit_end;
    typename std::iterator_traits<iterator>::value_type splitval;
};
#endif