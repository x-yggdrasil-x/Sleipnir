// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/transaction.h"
#include "main.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main_tests)

CAmount nMoneySupplyPoWEnd = 250000000 * COIN; // pre-mine 250,000,000 M ODIN

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    CAmount nSum = 0;
    for (int nHeight = 0; nHeight < 1; nHeight += 1) {
        /* premine in block 1 (166,667 ODIN) */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 166667 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 1; nHeight < 1501; nHeight += 1) {
        /* PoW premine (249,833,333 ODIN) */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 249833333 * COIN);
        nSum += nSubsidy;
    }

    BOOST_CHECK(nSum > 0 && nSum <= nMoneySupplyPoWEnd);

    // TODO: Adjust with PoS blocks
    for (int nHeight = 201; nHeight < 775601; nHeight += 1) {
        /* PoS Phase One */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 7 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 775601; nHeight < 1044000; nHeight += 1) {
        /* PoS Phase Two */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 4.5 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 1044000; nHeight < 1562398; nHeight += 1) {
        /* PoS Phase Two */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 3.6 * COIN);
        nSum += nSubsidy;
    }
}

BOOST_AUTO_TEST_SUITE_END()
