// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "console.h"
#include "blockchain.h"
#include <string>

void rpc(std::string command, std::string opts)
{
    // print("./komodo-cli " + get_params() + opts + command);

    print("Command to run:");
    print("./komodo-cli " + opts + command);

    return;
}
