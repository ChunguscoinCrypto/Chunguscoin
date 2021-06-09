// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "node.h"
#include "rpc.h"
#include "console.h"

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r");
    
    if (!pipe) print("Fatal error: popen() failed!");
    
    while (!feof(pipe))
    {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }
    
    auto rc = pclose(pipe);
    
    if (rc != EXIT_SUCCESS)
        print("Command returned error!");
    
    return result;
}

void exec_chungd(std::string opts)
{
    print("Running chunguscoind -> " + opts);
}

void exec_chungcli(std::string opts)
{
    print("Running chunguscoind-cli -> " + opts);
    print("Running exec()...");
    print(exec("neofetch"));
}
