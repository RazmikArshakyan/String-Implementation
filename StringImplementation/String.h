#ifndef STRING
#define STRING

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <exception>
#include <cstddef>

class String {
public: 
    String() noexcept;
    String(size_t init_size, char ch);
    String(const char* str);
    String(const String& other);
    String(String&& other);
    String(std::initializer_list<char> init_list);
    ~String();
    String& operator=(const String& other);
    const char operator[](size_t index);
    size_t size();
    bool empty();
    size_t capacity();
    void clear();
    void push_back(const char ch);
    void pop_back();
    friend std::ostream& operator<<(std::ostream& os, const String& str);
private:
    void store_in_heap(size_t init_size, char ch);
    void store_in_stack(size_t init_size, char ch);
    void heap_or_stack(size_t init_size, char ch);
    bool m_in_stack{};
    bool m_in_heap{};
    struct m_dyn_str {
        size_t m_size;
        char* m_ptr;
    };
    size_t m_stack_size = 16; 
    union {
        char m_on_stack[16];
        m_dyn_str m_on_heap;
    } m_string;
};

#include "String.cpp"
#endif