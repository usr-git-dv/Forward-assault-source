#include "memory.hpp"

namespace memory {
    static uintptr_t b_cache;
    static const char* cache_lib;
    
    bool lib_loaded (const char* lib_name)
    {
        FILE* maps_file = fopen("/proc/self/maps", "r");
        if (!maps_file)
        {
            return false;
        }
        
        char line[256];
        bool found = false;
        
        while (fgets(line, sizeof(line), maps_file))
        {
            if (strstr(line, lib_name))
            {
                found = true;
                break;
            }
        }
        fclose (maps_file);
        return found;
    }
    
    uintptr_t get_lib_base (const char* lib_name)
    {
        if (cache_lib && strcmp(cache_lib, lib_name) == 0)
        {
            return b_cache;
        }
        
        FILE* maps_file = fopen("proc/self/maps", "r-xp");
        if (!maps_file)
        {
            return 0;
        }
        
        char line[256];
        uintptr_t addr;
        
        while (fgets(line, sizeof(line), maps_file))
        {
            if (strstr(line, lib_name) && strstr(line, "r-xp"))
            {
                addr = strtoul(line, nullptr, 16);
                break;
            }
        }
        
        fclose (maps_file);
        
        if (addr != 0)
        {
            b_cache = addr;
            cache_lib = lib_name;
        }
        return addr;
    }
    
    uintptr_t get_address (const char* lib_name, uintptr_t offset)
    {
        uintptr_t base = get_lib_base(lib_name);
        if (base == 0)
        {
            return 0;
        }
        return base + offset;
    }
};
