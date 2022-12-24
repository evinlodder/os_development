#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <dominos/hash.h>
#include <dominos/pair.h>
#include <initializer_list>

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

    /*template <typename... rest>
    constexpr map(std::initializer_list<value_type, rest...>& l) {
        for(size_t i{}; i < l.size(); ++i) {
            this[i] = l[i];
        }
    }*/
    map() = default;

    //capacity
    size_t size() {
        size_t count{};
        for(size_t i{}; i < Size; ++i) {
            if(values[i] != nullptr) {
                ++count;
            }
        }
        return count;
    }

    bool empty() {
        return size() == 0;
    }
    size_t max_size() {
        return Size;
    }
    //

    //modifiers
    void clear() {
        for(size_t i{}; i < Size; ++i) {
            delete values[i];
            values[i] = nullptr;
        }
    }
    bool insert(const value_type& val) {
        try {
            *this[val.first] = val.second;
            return true;
        }
        catch(const char* code) {
            //dont need to fw code
            return false;
        }
    }
    size_t erase(const Key& key) {
        const auto idx = hasher{}(key) % Size;
        if(values[idx] == nullptr) {
            return 0;
        }
        const auto current = *values[idx];
        const auto last = *values[idx];
        while(current.value.first != key) {
            last = current;
            current = current->next;
            if(current == nullptr) {
                return 0;
            }
        }
        delete last->next;
        last->next = nullptr;
    }
    //

    //lookup
    Value& operator[](const Key& key) {
        //hash to get index
        const auto idx = hasher{}(key) % Size;
        //check if index hasn't been used yet
        if(values[idx] == nullptr) {
            //initialize index to default and return it
            values[idx] = new value_node{value_type{key, Value{}}};
            return values[idx]->val.second;
        }
        auto current = values[idx];
        auto last = values[idx];
        //iterate through linked list until correct node found
        while(current->val.first != key) {
            last = current;
            current = current->next;
            //if no correct node found, initialize it and return it
            if(current == nullptr) {
                current = last;
                current->next = new value_node{value_type{key, Value{}}};
                return current->next->val.second;
            }
        }
        //if the correct node is found, return its second val
        return current->val.second;
    }

    Value& at(const Key& key) {
        const auto idx = hasher{}(key) % Size;
        if(values[idx] == nullptr) {
            throw "Error: no value at key";
        }
        auto current = *values[idx];
        while(current.value.first != key) {
            current = current->next;
            if(current == nullptr) {
                throw "Error: no value at key";
            }
        }
        return current.val.second;
    }

    size_t count(const Key& key) {
        const auto idx = hasher{}(key) % Size;
        auto current = *values[idx];
        while(current.value.first != key) {
            current = current->next;
            if(current == nullptr) {
                return 0;
            }
        }
        return 1;
    }
    bool contains(const Key& key) {
        const auto idx = hasher{}(key) % Size;
        auto current = *values[idx];
        while(current.value.first != key) {
            current = current->next;
            if(current == nullptr) {
                return false;
            }
        }
        return true;
    }
    //


private:
    struct value_node {
        value_type val;
        value_node* next;
        value_node() : val(value_type{}), next(nullptr) {}
        value_node(const value_type& v) : val(v), next(nullptr) {}
    };
    value_node* values[Size]{};
};


}


#endif //MAP_H
