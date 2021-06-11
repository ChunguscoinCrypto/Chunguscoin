// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <array>
#include <cstdio>
#include <vector>
#include <iostream>
#include "chungusparams.h"
#include "../util.h"

// Chunguscoin launch params
const char* params[] = 
{
    "chung-args",
    "-ac_name=CHUNG",
    "-ac_reward=5000000000",
    "-ac_halving=3000000",
    "-addnode=172.106.70.133:22001"
};

void SetChungusParams(int argc, char *argv[])
{
    argc--;
    argv++;

    unsigned long count = sizeof(params)/sizeof(params[0]);
    int total = count + argc;
    int index = 0;

    const char* args[total];

    for(int i = 0; i < count; ++i)
        args[index++] = params[i];

    for(int i = 0; i < argc; ++i)
        args[index++] = argv[i];

    ParseParameters(total, args);
}