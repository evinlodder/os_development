#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <cstddef>
#include <dominos/hash>

namespace dominos {


//my current map implementation will have a templated size, and the underlying container will be a simple array (with no MMU I can't do vectors) with "nodes" that will be as such:
//
//  value (of type Value),
//  node* next,
//  key (of type Key)
//
//  the reasoning behind the key is so that if you have hash overlap,
//  when reading you will know which value to select.
template <typename Key, typename Value, typename Hash = dominos::hash<Key>, size_t size = 255>
class map {
public:
    using key_type = Key;
    using mapped_type = Value;
    //using value_type = std::pair<Key, Value>
    using size_type = size_t;
    using hasher = Hash;

    using reference = 

    Value& operator[](const Key& key);

};


}


#endif //MAP_H
