#pragma once

#include <dlfcn.h>

inline long mono_address = 0;

inline std::string utf16be_to_utf8(const std::u16string &s) 
{
    std::string r;

    r.reserve (s.size() * 3);

    for (size_t i = 0; i < s.size(); i++)
    {
        uint32_t c = s [i];

        if (c < 0x80)
        {
            r += char (c);
        } else if (c < 0x800) {
            r += { char(0xC0 | c >> 6), char(0x80 | (c & 0x3F))};
        } else if ((c &  0xFC00) == 0xD800) {
            uint32_t cp = ((c - 0xD800) << 10) + (s[++i] - 0xDC00) + 0x10000;

            r += {char(0xF0 | cp >> 18), char(0x80 | (cp >> 12) & 0x3F), char(0x80 | (cp >> 6) & 0x3F),
            char (0x80 | (cp & 0x3F))};
        } else {
            r += {char(0xE0 | c >> 12), char (0x80 | (c >> 6) & 0x3F), char(0x80 | (c & 0x3F))};
        }
    }

    return r;
}

struct MonoString {
    void* klass;   
    void* monitor;

    int length;

    char firstChar[1];

    const char* to_chars() 
    {       
        std::u16string ss((char16_t*) get_chars(), 0, get_length());  

        std::string str = utf16be_to_utf8(ss);  

        return str.c_str();   
    }

    char* get_chars() 
    {    
       return firstChar;    
    }  

     int get_length()
     {
        return length;
     }

    std::string get_string()
    {
        std::u16string str((char16_t*)firstChar, (char16_t*)firstChar + length);

        std::string res = utf16be_to_utf8(str);

        return res;
    }
    
    const char* get_cstring()
    {
        return get_string().c_str();
    }
};

inline MonoString* il2cpp_string_new (const char* str){
    static const auto _il2cpp_string_new = (MonoString*(*)(const char*)) dlsym(dlopen("libil2cpp.so", RTLD_LAZY), "il2cpp_string_new");

    return _il2cpp_string_new(str);
}

template<typename T>
struct monoArray {
    void *klass;
    void *monitor;
    void *bounds;

    int length;
    int capacity;

    T m_Items [0];

    int getCapacity() 
    {
        return capacity;
    }
    
    int getLength() 
    {
        return length;
    }

    T* getPointer() 
    {
        return m_Items;
    }
    
    template<typename V = T>
    std::vector<V> toCPPlist() 
    {
        std::vector<V> ret;

        for (int i = 0; i < capacity; i++)
        {
            ret.push_back (m_Items[i]);
        }

        return std::move (ret);
    }

    void copyFrom(std::vector<T> vec) 
    {
        copyFrom (vec.data(), vec.size());
    }
    
    void copyFrom (T *arr, int size)
    {
        if (size > capacity)
        {
            Resize (size);
        }

        memcpy (arr, m_Items, capacity * sizeof(T));
    }

    void copyTo(T *arr) 
    {
        memcpy (arr, m_Items, sizeof(T) * capacity);
    }
    
    T operator[] (int index) 
    {
        return m_Items[index];
    }

    void Resize(int newSize) 
    {
        if (newSize <= capacity) return;

        T* newArr = new T [newSize];

        memcpy (newArr, m_Items, capacity * sizeof(T));

        capacity = newSize;
    }
    
    monoArray<T>* MonoCreate(int size) 
    {
        monoArray<T>* monoArr = (monoArray<T> *)malloc(sizeof(monoArray) + sizeof(T) * size);

        monoArr->capacity = size;

        return monoArr;
    }

    template<typename t>
    static monoArray<t>* Create(int size) 
    {
        monoArray<t> *monoArr = (monoArray<t> *)malloc(sizeof(monoArray) + sizeof(t) * size);

        monoArr->capacity = size;
        
        return monoArr;
    }
    
    template<typename t>
    static monoArray<t>* Create(std::vector<t> vec) 
    {
        return Create<t> (vec.data(), vec.size());
    }
    
    template<typename t>
    static monoArray<t> *Create(T *arr, int size) 
    {
        monoArray<t> *monoArr = Create<t> (size);
        for (int i = 0; i < size; i++)
        {
            monoArr->m_Items[i] = arr[i];
        }

        return monoArr;
    }
};