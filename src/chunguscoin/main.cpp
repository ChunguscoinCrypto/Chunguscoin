// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// C Libraries:
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "console.h"
#include "test.h"

// Namespaces:
using namespace std;

int main(int argc, char **argv) {

  if (argc <= 1) {
    print("Running wallet...");
    testFunc();
    return 0;
  }

  for (int i = 1; i < argc; ++i) {
    string arg = string(argv[i]);

    /* RPC Command */
    if (arg == "rpc") {
      print("rpc");

      vector<string> opts;
      vector<string> actions;

      for (int i = 2; i < argc; ++i) {
        string action = string(argv[i]);

        if (action[0] == "-"[0])
          opts.push_back(action);
        else if (action != "")
          actions.push_back(action);
      }

      string command;
      for (auto const &s : actions) {
        command += s + " ";
      }

      // Call RPC function
      // rpc(command, opts)

      print("Command + args: " + command);

      for (uint i = 0; i < opts.size(); ++i)
        print("RPC Options: " + opts[i]);

      return 0;

    } else

    /* Node command */
    if (arg == "node") {
      print("node");

      return 0;

    } else

    /* Help command */
    if (arg == "help") {
      print("help");
      testFunc();

      return 0;

    } else

    /* Command not found */
    {
      print("The arg " + arg + " is not a vaild command.");
      return 0;
    }
  }

  // Return OK.
  return 0;
}