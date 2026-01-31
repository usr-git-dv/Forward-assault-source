#include <iostream>
#include <thread>

#include "core/cheat/hooks/imgui_init.hpp"

__attribute((constructor))
void MainThread ()
{
    std::thread (cheat).detach();
    std::thread (init_symbols).detach();
}