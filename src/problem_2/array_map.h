#pragma once

#include <vector>
#include "entry.h"
#include "map.h"
#include <iostream>
#include "../problem_3/list/array_list.h"

template<class KeyType, class ValueType>
class ArrayMap : public Map<KeyType, ValueType> {
private:
    static const int DEFAULT_CAPACITY = 10;
    Entry<KeyType, ValueType> **entries;
    int capacity;
    int count;

    void delete_entry(Entry<KeyType, ValueType> *node) {
        if (node == nullptr) {
            return;
        }
        delete_entry(node->next);
        delete node;
    }

    int hashFunc(KeyType key) const {
        return (int) key % capacity;
    }

public:

    ArrayMap() : ArrayMap(DEFAULT_CAPACITY) {}

    ArrayMap(int capacity) : capacity(capacity), count(0) {
        // () at the end initialize all values to nullptr
        entries = new Entry<KeyType, ValueType> *[capacity]();
    }


    ArrayMap(const std::vector<std::pair<KeyType, ValueType>> &map_data) : ArrayMap(map_data.size()) {
        for (auto &pair: map_data) {
            put(pair.first, pair.second);
        }
    }

    ArrayMap(const ArrayMap &other_map) : ArrayMap(other_map.capacity) {
        for (int i = 0; i < capacity; i++) {
            Entry<KeyType, ValueType> *ptr = other_map.entries[i];
            while (ptr != nullptr) {
                put(ptr->key, ptr->value);
                ptr = ptr->next;
            }
        }
    }

    ~ArrayMap() {
        for (int i = 0; i < capacity; i++) {
            if (entries[i] == nullptr) {
                continue;
            }
            delete_entry(entries[i]);
        }
        delete[]entries;
    }

    int size() override {
        return count;
    }

    bool is_empty() override {
        return count == 0;
    }

    void put(KeyType const &key, ValueType const &value) override {

        int hashed_key = hashFunc(key);

        if(entries[hashed_key] == nullptr) { //first check if there are no node in the list
            entries[hashed_key] = new Entry(key, value);
        }

        else{ //if not the nodes are searched through
            Entry<KeyType, ValueType> *ptr = entries[hashed_key];
            //search stops either at the end of the list or when a duplicate key is found
            while(ptr->next != nullptr && ptr->key != key){
                ptr = ptr->next;
            }
            //if a dublicate is found, the new value is set and the function returns
            if (ptr->key == key) {
                ptr->value = value;
                return;
            }
            ptr->next = new Entry(key, value);
        }
        //count is only incremented at the end so duplicate values don't affect the count
        count++;
    }

    bool get(KeyType const &key, ValueType &value) const override {
        int hashed_key = hashFunc(key);
        Entry<KeyType, ValueType> *ptr = entries[hashed_key];
        while (ptr != nullptr) {
            if (ptr->key == key) {
                value = ptr->value;
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            if (entries[i] == nullptr) {
                printf("[%d] = null\n", i);
                continue;
            }
            Entry<KeyType, ValueType> *ptr = entries[i];
            printf("[%d] = {", i);
            while (ptr != nullptr) {
                printf("(%d, %f)", ptr->key, ptr->value);
                ptr = ptr->next;
            }
            printf("}\n");
        }
    }

    bool remove(KeyType const &key) override {
        //entering the correct entry list
        int hashed_key = hashFunc(key);
        Entry<KeyType, ValueType> *ptr = entries[hashed_key];

        //immediately sent false if the list is empty
        if(ptr == nullptr){
            return false;
        }
        //if the item that needs to be removed is the first item of the list
        if(ptr->key == key){
            count--;
            entries[hashed_key] = ptr->next;
            delete ptr;
            return true;
        }
        //checks the rest of the list
        while (ptr->next != nullptr) {
            if (ptr->next->key == key) {
                delete ptr->next;
                ptr->next = ptr->next->next;
                count--;
                return true;
            }
            ptr = ptr->next;
        }
        //returns false if nothing is found
        return false;
    }

    bool operator==(const ArrayMap &other_map) const {
        if (count != other_map.count) {
            return false;
        }

        for (int i = 0; i < other_map.capacity; i++) {
            Entry<KeyType, ValueType> *other_ptr = other_map.entries[i];
            while (other_ptr != nullptr) {
                ValueType val;
                if (!get(other_ptr->key, val) || val != other_ptr->value) {
                    return false;
                }
                other_ptr = other_ptr->next;
            }
        }
        return true;
    }

    bool operator!=(const ArrayMap &other_map) const {
        return !(other_map == *this);
    }

    void key_set(List<KeyType> &keys) {
        for (int i = 0; i < capacity; i++) {
            if (entries[i] == nullptr) {
                continue;
            }
            Entry<KeyType, ValueType> *ptr = entries[i];
            while (ptr != nullptr) {
                keys.push_back(ptr->key);
                ptr = ptr->next;
            }
        }
    }
};