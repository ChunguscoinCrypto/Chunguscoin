// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "console.h"
#include "blockchain.h"
#include <string>

void rpc(std::string command, std::string opts)
{
    print("==========================================");
    print("RPC Command -> " + command);
    print("==========================================");
    print("RPC args -> " + opts);
    print("==========================================");

    print("==============| CHUNG ARGS |==============");
    print(get_params());
    print("==========================================");
    print("=============| FULL COMMAND |=============");
    print("./komodo-cli " + get_params() + opts + command);
    print("==========================================");

    return;
}