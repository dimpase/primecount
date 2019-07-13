///
/// @file   factor_table.cpp
/// @brief  FactorTable is a compressed lookup table of mu
///         (moebius) and lpf (least prime factor).
///
/// Copyright (C) 2019 Kim Walisch, <kim.walisch@gmail.com>
///
/// This file is distributed under the BSD License. See the COPYING
/// file in the top level directory.
///

#include <FactorTable.hpp>
#include <generate.hpp>

#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>

using namespace std;
using namespace primecount;

void check(bool OK)
{
  cout << "   " << (OK ? "OK" : "ERROR") << "\n";
  if (!OK)
    exit(1);
}

int main()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dist(500000, 1000000);

  auto max = dist(gen);
  auto threads = max % 4;
  auto lpf = generate_lpf(max);
  auto mu = generate_moebius(max);

  FactorTable<uint16_t> factorTable(max, threads);
  int64_t uint16_max = numeric_limits<uint16_t>::max();
  int64_t limit = factorTable.get_first_coprime();
  vector<int> small_primes = { 2, 3, 5, 7, 11, 13, 17, 19 };

  for (int n = 1; n <= max; n++)
  {
    int64_t i = factorTable.get_index(n);
    bool is_prime = (lpf[n] == n);

    // Check if n is coprime to the primes < limit
    for (int p : small_primes)
    {
      if (p >= limit)
        break;
      if (n % p == 0)
        goto not_coprime;
    }

    cout << "mu(" << n << ") = " << factorTable.mu(i);
    check(mu[n] == factorTable.mu(i));

    cout << "lpf(" << n << ") = " << lpf[n];

    // mu_lpf(n) is a combination of the mu(n) (Möbius function)
    // and lpf(n) (least prime factor) functions.
    // mu_lpf(n) returns (with n = get_number(index)):
    //
    // 1) INT_MAX - 1  if n = 1
    // 2) INT_MAX      if n is a prime
    // 3) 0            if moebius(n) = 0
    // 4) lpf - 1      if moebius(n) = 1
    // 5) lpf          if moebius(n) = -1

    if (n == 1)
      check(factorTable.mu_lpf(i) == uint16_max - 1);
    else if (is_prime)
      check(factorTable.mu_lpf(i) == uint16_max);
    else if (mu[n] == 0)
      check(factorTable.mu_lpf(i) == 0);
    else
      check(lpf[n] == factorTable.mu_lpf(i) + (factorTable.mu(i) == 1));

    not_coprime:;
  }

  cout << endl;
  cout << "All tests passed successfully!" << endl;

  return 0;
}
