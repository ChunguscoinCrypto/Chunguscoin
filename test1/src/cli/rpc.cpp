// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "console.h"
#include "blockchain.h"
#include "rpc.h"
#include "exec.h"
#include <string>

void rpc(std::string command, std::string opts)
{
    // print("./chunguscoin-cli " + get_params() + opts + command);

    print("Command to run:");
    print("./chunguscoin-cli " + get_name() + opts + command);
    exec_chungcli(opts + get_name() + command);

    return;
}
