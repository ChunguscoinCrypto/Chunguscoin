// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>

void print(std::string str)
{
   std::cout << str << std::endl;
}

void error(std::string str)
{
   std::cout << str << std::endl;
}

void errorout(std::string str)
{
   std::cout << str << std::endl;
   std::exit(0);
}
