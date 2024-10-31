#pragma once

#include "includes.h"

const size_t SIZE = 20;

struct Hinfo {
    string key;
    string value;
    Hinfo* next;

     // Конструктор для удобства создания узлов
      Hinfo(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

struct Hash_table { 
    Hinfo** table;
    int sizetable = 0;

    Hash_table();
    ~Hash_table();

    int hashFunction(const string& key);
    void insert(const string &key, const string value);
    bool get(const string& key, string& value);
    bool remove(const string& key);
};

#include "../src/hashtable.cpp"