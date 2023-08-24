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

void String::store_in_heap(char *str)
{
    const size_t buf_size = 256;
    m_string.m_on_heap.m_ptr = new char[buf_size];
    int length{};
    for (size_t i{}; *(str + i) != '\0'; ++i) {
        ++length;
        m_string.m_on_heap.m_ptr[i] = str[i];
    }
    m_string.m_on_heap.m_ptr[length] = '\0';
    m_string.m_on_heap.m_size = length;
    m_in_heap = true;
    m_in_stack = false;
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

void String::store_in_stack(char *str)
{
    for (size_t i{}; *(str + i) != '\0'; ++i) {
        m_string.m_on_stack[i] = str[i];
    }
    m_in_stack = true;
    m_in_heap = false;
}

void String::heap_or_stack(size_t init_size, char ch)
{
    (init_size > m_stack_size ? store_in_heap(init_size,ch) : store_in_stack(init_size,ch));
}

String::~String()
{
    // if (m_in_heap) {
    //     delete[] m_string.m_on_heap.m_ptr;
    // }
}

String& String::operator=(const String& other) {
    if (this == &other) {
        return *this; 
    }

    if (other.m_in_heap) {
        size_t length = other.m_string.m_on_heap.m_size;
        char* new_str = new char[length];
        for (size_t i{}; i < length; ++i) {
            new_str[i] = other.m_string.m_on_heap.m_ptr[i];
        }
        m_string.m_on_heap.m_ptr = new_str;
        m_string.m_on_heap.m_size = length;
        m_in_heap = true;
    } else {
        for (size_t i{}; i < other.m_stack_size; ++i) {
            m_string.m_on_stack[i] = other.m_string.m_on_stack[i];
        }
        m_in_stack = true;
    }
    return *this;
}

String String::operator+=(const String &rhs)
{
    size_t lh_size = size();
    size_t rh_size = rhs.size();
    if (m_in_heap) {
        if (rhs.m_in_heap) {
            for (size_t i{lh_size}, j{}; i < (lh_size + rh_size) && j < rh_size; ++i, ++j) {
                m_string.m_on_heap.m_ptr[i] = rhs.m_string.m_on_heap.m_ptr[j];
            }
        }
        else {
            for (size_t i{lh_size}, j{}; i < (lh_size + rh_size) && j < rh_size; ++i, ++j) {
                m_string.m_on_heap.m_ptr[i] = rhs.m_string.m_on_stack[j];
            }
        }
        m_string.m_on_heap.m_size = lh_size + rh_size;
        m_string.m_on_heap.m_ptr[lh_size + rh_size] = '\0';
    }
    else {
        if (lh_size + rh_size > m_stack_size) {
            char* new_str = new char[lh_size + rh_size];
            for (size_t i{}; i < lh_size; ++i) {
                new_str[i] = m_string.m_on_stack[i];
            }
            if (rhs.m_in_heap) {
                for (size_t i{lh_size}, j{}; i < (lh_size + rh_size) && j < rh_size; ++i, ++j) {
                    new_str[i] = rhs.m_string.m_on_heap.m_ptr[j];
                }
            }
            else {
                for (size_t i{lh_size}, j{}; i < (lh_size + rh_size) && j < rh_size; ++i, ++j) {
                    new_str[i] = rhs.m_string.m_on_stack[j];
                }
            }
            m_string.m_on_heap.m_ptr = new_str;
            m_string.m_on_heap.m_size = lh_size + rh_size;
            m_string.m_on_heap.m_ptr[lh_size + rh_size] = '\0';
            m_in_heap = true;
            m_in_stack = false;
        }
        else {
            for (size_t i{lh_size}, j{}; i < (lh_size + rh_size) && j < rh_size; ++i, ++j) {
                    m_string.m_on_stack[i] = rhs.m_string.m_on_stack[j];
            }
        }
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

size_t String::size() const
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

bool String::empty() const
{
    return (size() == 0 ? true : false);
}

size_t String::capacity() const
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
    if (m_in_heap) {
        m_string.m_on_heap.m_ptr[str_size] = ch;
        m_string.m_on_heap.m_ptr[str_size + 1] = '\0';
        m_string.m_on_heap.m_size = str_size + 1;
    }
    if ((str_size + 1) == m_stack_size) {
        char* new_str = new char[str_size + 1];
        for (size_t i{}; i < str_size + 1; ++i) {
            if (i == str_size) {
                new_str[i] = ch;
                break;
            }
            new_str[i] = m_string.m_on_stack[i];
        }
        m_string.m_on_heap.m_ptr = new_str;
        m_string.m_on_heap.m_size = str_size + 1;
        m_string.m_on_heap.m_ptr[str_size + 1] = '\0';
        m_in_heap = true;
        m_in_stack = false;
    } 
    else {
        m_string.m_on_stack[str_size] = ch;
    }
}

void String::pop_back()
{
    size_t str_size = size();
    if ((str_size - 1) < m_stack_size && m_in_heap) {
        m_in_heap = false;
        m_in_stack = true;
        char* m_ptr_cpy = m_string.m_on_heap.m_ptr;
        for (size_t i{}; i < str_size; ++i) {
            if (i == (str_size - 1)) {
                m_string.m_on_stack[i] = '\0';
                break;
            }
            m_string.m_on_stack[i] = m_ptr_cpy[i];
        }
    }
    else if ((str_size - 1) < m_stack_size && !m_in_heap) {
        m_string.m_on_stack[str_size - 1] = '\0';
    }
    else {
        char* m_ptr_cpy = m_string.m_on_heap.m_ptr;
        for (size_t i{}; i < str_size; ++i) {
            if (i == (str_size - 1)) {
                m_ptr_cpy[i] = '\0';
                break;
            }
            m_ptr_cpy[i] = m_string.m_on_heap.m_ptr[i];
        }
        m_string.m_on_heap.m_ptr = m_ptr_cpy;
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

std::istream &operator>>(std::istream &in, String &str)
{
    const size_t buf_size = 256;
    char buf[buf_size];
    in >> buf;

    if (std::strlen(buf) < str.m_stack_size) {
        str.store_in_stack(buf);
    }
    else {
        str.store_in_heap(buf);
    }
    return in;    
}