#include "String.h"

String::String() noexcept
{
    for (size_t i{}; i < m_stack_size; ++i) {
        m_string.m_on_stack[i] = '\0';
    }
    m_in_stack = true;
}

String::String(size_t init_size, char ch)
{
    heap_or_stack(init_size,ch);
}

String::String(const char *str)
{
    size_t length{};
    for (size_t i{}; *(str + i) != '\0'; ++i) {
        ++length;
    }
    if (length > m_stack_size) {
        char* new_str = new char[length];
        for (size_t i{}; i < length + 1; ++i) {
            if (i == length) {
                new_str[i] = '\0';
                break;
            }
            new_str[i] = str[i];
        }
        m_string.m_on_heap.m_ptr = new_str;
        m_string.m_on_heap.m_size = length;
        m_in_heap = true;
    }
    else {
        for (size_t i{}; i < length + 1; ++i) {
            if (i == length) {
                m_string.m_on_stack[i] = '\0';
                break;
            }
            m_string.m_on_stack[i] = str[i];
        }  
        m_in_stack = true;
    }
    
}

String::String(const String &other)
    : m_in_heap {other.m_in_heap}
    , m_in_stack {other.m_in_stack}
    , m_string {other.m_string}
{
}

String::String(String &&other)
    : m_in_heap {other.m_in_heap}
    , m_in_stack {other.m_in_stack}
    , m_string {other.m_string}
{
}

String::String(std::initializer_list<char> init_list)
{
    size_t init_size = init_list.size();
    if (init_size > m_stack_size) {
        char* new_str = new char[init_size];
        for (size_t i{}; i < init_size + 1; ++i) {
            if (i == init_size) {
                new_str[i] = '\0';
                break;
            }
            new_str[i] = *(init_list.begin() + i);
        }
        m_string.m_on_heap.m_ptr = new_str;
        m_string.m_on_heap.m_size = init_size;
        m_in_heap = true;
    }
    else {
        for (size_t i{}; i < init_size + 1; ++i) {
            if (i == init_size) {
                m_string.m_on_stack[i] = '\0';
                break;
            }
        m_string.m_on_stack[i] = *(init_list.begin() + i);
        }
        m_in_stack = true;
    }
}

void String::store_in_heap(size_t init_size, char ch)
{
    char* new_str = new char[init_size];
    for (size_t i{}; i < init_size + 1; ++i) { 
        if (i == init_size) {
            new_str[i] = '\0';
            break;
        }
        new_str[i] = ch;
    }
    m_string.m_on_heap.m_ptr = new_str;
    m_string.m_on_heap.m_size = init_size;
    m_in_heap = true;
}

void String::store_in_stack(size_t init_size, char ch)
{
    for (size_t i{}; i < init_size + 1; ++i) {
        if (i == init_size) {
            m_string.m_on_stack[i] = '\0';
            break;
        }
        m_string.m_on_stack[i] = ch;
    }
    m_in_stack = true;
}

void String::heap_or_stack(size_t init_size, char ch)
{
    if (init_size > m_stack_size) {
        store_in_heap(init_size,ch);
    }
    else {
        store_in_stack(init_size,ch);
    }
}

String::~String()
{
    if (m_in_heap) {
        delete[] m_string.m_on_heap.m_ptr;
    }
}

String& String::operator=(const String& other) {
    if (this == &other) {
        return *this; 
    }

    if (other.m_in_heap) {
        size_t length = other.m_string.m_on_heap.m_size;
        char* new_str = new char[length];
        for (size_t i = 0; i < length; ++i) {
            new_str[i] = other.m_string.m_on_heap.m_ptr[i];
        }
        m_string.m_on_heap.m_ptr = new_str;
        m_string.m_on_heap.m_size = length;
        m_in_heap = true;
    } else {
        for (size_t i = 0; i < other.m_stack_size; ++i) {
            m_string.m_on_stack[i] = other.m_string.m_on_stack[i];
        }
        m_in_stack = true;
    }

    return *this;
}

const char String::operator[](size_t index)
{
    if (index >= size()) {
        throw std::out_of_range("Index out of range");
    }

    if (size() > m_stack_size) {
        return m_string.m_on_heap.m_ptr[index];
    }
    else {
        return m_string.m_on_stack[index];
    }
}

size_t String::size()
{
    size_t length{};
    if (m_in_heap) {
        return m_string.m_on_heap.m_size;
    }
    else {
        for (size_t i{}; *(m_string.m_on_stack + i) != '\0'; ++i) {
            ++length;
        }
        return length;
    }
}

bool String::empty()
{
    if (size() == 0) {
        return true;
    }
    return false;
}

size_t String::capacity()
{
    return SIZE_MAX;
}

void String::clear()
{
    if (m_in_heap) {
        for (size_t i{}; i < size(); ++i) {
            m_string.m_on_heap.m_ptr[i] = '\0';
        }
    }
    else {
        for (size_t i{}; i < size(); ++i) {
            m_string.m_on_stack[i] = '\0';
        }
    }
}

void String::push_back(const char ch)
{
    size_t str_size = size();
    if (str_size + 1 < m_stack_size) {
        m_string.m_on_stack[str_size] = ch;
    }
    else {
        char* new_str = new char[str_size + 1];
        for (size_t i{}; i < str_size + 2; ++i) { 
            if (i == str_size + 1) {
                new_str[i] = '\0';
                break;
            }
            else if (i == str_size) {
                new_str[i] = ch;
            }
            else {
                new_str[i] = m_string.m_on_stack[i];
            }
        }
        m_string.m_on_heap.m_ptr = new_str;
        m_string.m_on_heap.m_size = str_size + 1;
        m_in_heap = true;
        m_in_stack = false;
    }
}

void String::pop_back()
{
    size_t str_size = size();
    if ((str_size - 1) < m_stack_size && m_in_heap) {
        m_in_heap = false;
        m_in_stack = true;
        for (size_t i{}; i < str_size; ++i) {
            m_string.m_on_stack[i] = m_string.m_on_heap.m_ptr[i];
        }
    }
    else if ((str_size - 1) < m_stack_size && !m_in_heap) {
        m_string.m_on_stack[str_size] = '\0';
    }
    else {
        --m_string.m_on_heap.m_size;
    }
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    if (str.m_in_stack) {
        os << str.m_string.m_on_stack;
    } else if (str.m_in_heap) {
        os << str.m_string.m_on_heap.m_ptr;
    }
    return os;
}