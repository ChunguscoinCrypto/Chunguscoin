// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "console.h"
#include "blockchain.h"
#include "node.h"
#include "exec.h"
#include <string>

void node(std::string command, std::string opts)
{
    // print("./komodo-cli " + get_params() + opts + command);
    if(command == "start")
        node_start(opts);
    else if(command == "stop")
        node_stop(opts);
}

void node_start(std::string opts)
{
    print("Command to run:");
    print("./komodod " + get_params() + opts);
    exec_chungd(get_params() + opts);
    return;
}

void node_stop(std::string opts)
{
    print("Command to run:");
    print("./komodod-cli " + get_name() + opts + "stop");
    exec_chungcli(get_name() + opts + "stop ");
    return;
}
