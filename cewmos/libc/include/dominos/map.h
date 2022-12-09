#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <cstddef>
#include <dominos/hash>
#include <dominos/pair>

namespace dominos {


//my current map implementation will have a templated size, and the underlying container will be a simple array (with no MMU I can't do vectors) with "nodes" that will be as such:
//
//  value (of type Value),
//  node* next,
//  key (of type Key)
//
//  the reasoning behind the key is so that if you have hash overlap,
//  when reading you will know which value to select.
template <typename Key, typename Value, typename Hash = dominos::hash<Key>, size_t Size = 255>
class map {
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = dominos::pair<Key, Value>;
    using size_type = size_t;
    using hasher = Hash;

    using reference = value_type&;
    using const_reference = const value_type&;

    //implement iterators when you get home with book

    //

    //capacity
    bool empty();
    size_t size();
    size_t max_size();
    //

    //modifiers
    void clear();
    bool insert(const value_type& val);
    size_t erase(const Key& key);


    Value& operator[](const Key& key);
private:
    struct value_node {
        value_type val;
        value_node* next;
    }
    value_node values[Size]{};
};


}


#endif //MAP_H
