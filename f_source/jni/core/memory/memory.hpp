#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace memory {
    bool lib_loaded (const char* lib_name);
    uintptr_t get_lib_base (const char* lib_name);
    uintptr_t get_address (const char* lib_name, uintptr_t offset);   
};
