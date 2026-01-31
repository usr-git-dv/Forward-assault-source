#include "searcher.hpp"

bool find_players (void* player)
{
    return std::find (Players.begin(), Players.end(), player) != Players.end();
}

bool find_grenades (void* grenade)
{
    return std::find (Grenades.begin(), Grenades.end(), grenade) != Grenades.end();
}