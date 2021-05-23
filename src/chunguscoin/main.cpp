// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// C Libraries:
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "test.h"
#include "console.h"
#include "rpc.h"
#include "node.h"

// Namespaces:
using namespace std;

int main(int argc, char **argv) {

  if (argc <= 1) {
    print("Running wallet...");
    print("Running test command ->");
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

      string opt;
      for (auto const &s : opts) {
        opt += s + " ";
      }

      // Call RPC function
      rpc(command, opt);


      return 0;

    } else

    /* Node command */
    if (arg == "node") {
      print("node");

      vector<string> opts;
      vector<string> actions;

      for (int i = 2; i < argc; ++i) {
        string action = string(argv[i]);

        if (action[0] == "-"[0])
          opts.push_back(action);
        else if (action == "start" || action == "stop")
          actions.push_back(action);
        else
          errorout("Arg " + action + " is not a vaild option.");
      }

      string command;
      for (auto const &s : actions) {
        command += s;
      }

      string opt;
      for (auto const &s : opts) {
        opt += s + " ";
      }

      // Call RPC function
      node(command, opt);

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
