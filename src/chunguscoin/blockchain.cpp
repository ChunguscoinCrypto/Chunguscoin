// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/* Blockchain params */

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "blockchain.h"
#include "util.h"

/* Define params */
std::string ac_name = "CHUNG";
std::vector<std::string> ac_nodes = {"172.106.70.133", "73.137.75.128"};
int ac_blocktime = 60; // 60 sec = 1 min
long ac_init_supply = 90000000000;
// TODO - long Blockchain::supply_cap;

/* Return params as string */
std::string get_params()
{
    std::string params;

    std::ostringstream ss;
    ss << std_format("-ac_name=%s -ac_supply=%ld ", ac_name.c_str(), ac_init_supply);
    params += ss.str();

    for(uint i; i < ac_nodes.size(); ++i)
        params += "-addnode=" + ac_nodes[i] + " ";

    return params;
}
