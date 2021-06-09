// Copyright (c) 2021 Shafil Alam
// Copyright (c) 2021 Chunguscoin Devs
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/* This is a example header file  */

#include <stdio.h>
#include <string>

#include "test.h"
#include "console.h"

void testFunc() {
  printf("Welcome to Chunguscoin wrapper by Shafil Alam!\n");

  std::string chung;
  chung = "Chunguscoin Smart Chain";
  print("Thank you " + chung);

  return;
}
