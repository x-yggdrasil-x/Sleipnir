// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Phore developers
// Copyright (c) 2018 The ODIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions


/**
 * MAIN NET CHECKPOINTS
 * 
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (    0, uint256("37b3b9b0c61335f9cdb82fccfe70a8f123c3b812e2c658ef42f691a150074b9b"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1534859753, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3600        // * estimated number of transactions per day after checkpoint
};


/**
 * TEST NET CHECKPOINTS
 * 
 */
static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    ( 0, uint256("01519125dd84851de9437d61a24162610e8cba04d57f8a53765b7b0231e80866") );

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1535569392, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3600        // * estimated number of transactions per day after checkpoint
};


/**
 * REGRESSION TEST NET CHECKPOINTS
 * 
 */
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    ( 0, uint256("57953c6db14b32b8fd1579c8aee7c2b7b2efd7ac9b15bbdf32fc96586cd69b5d") );
    // (0, uint256("0x2b1a0f66712aad59ad283662d5b919415a25921ce89511d73019107e380485bf"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1535569429, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3600        // * estimated number of transactions per day after checkpoint
};


libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

libzerocoin::ZerocoinParams* CChainParams::OldZerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus;
    bnTrustedModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
    public:
    CMainParams()
    {
        networkID     = CBaseChainParams::MAIN;
        strNetworkID  = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x32;
        pchMessageStart[1] = 0x67;
        pchMessageStart[2] = 0x69;
        pchMessageStart[3] = 0x53;

        vAlertPubKey = ParseHex("048e8c3d748796606a5b22ddb5bc7daf1db2f2428529c7836d41a897c675e8e247dade5476751ef5984e7da30e6b927c13a7a61197281b2d16275d81f63982fd6c");

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        // Primary configurations
        nDefaultPort            = 34221;  // Main (mainnet) P2P Port
        nMaxReorganizationDepth = 100;
        nMinerThreads           = 0;
        nTargetTimespan         = 1 * 60; // Odin: 1 day
        nTargetSpacing          = 2 * 60; // Odin: 1 minute
        nMaturity               = 9;      // Transaction maturity
        nMasternodeCountDrift   = 20;
        nMaxMoneyOut            = 2000000000 * COIN;
        bnProofOfWorkLimit      = ~uint256(0) >> 1;
        nLastPOWBlock           = 7500;   // Last Proof-of-Work block
        nModifierUpdateBlock    = 999999999;

        // Zerocoin Configurations
        nZerocoinLastOldParams            = 99999999; // Updated to defer zerocoin v2 for further testing.
        nMaxZerocoinSpendsPerTransaction  = 7;        // Assume about 20kb each
        nMinZerocoinMintFee               = 1 * CENT; // high fee required for zerocoin mints
        nMintRequiredConfirmations        = 20;       // the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation             = 1;
        nDefaultSecurityLevel             = 100;      // full security level for accumulators
        nZerocoinHeaderVersion            = 4;        // Block headers must be this version once zerocoin is active
        nBudgetFeeConfirmations           = 6;        // Number of confirmations for the finalization fee
        nZerocoinStartHeight              = 501;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "https://youtu.be/bCodVbucTbo";

        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        // txNew.vout[0].SetEmpty();
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0402063889d534fb2b51e521c6f730586f86db8577cad991fb0f07c0c54cbc0cac32d8e42ca3cc6b98a76c2216e727ddb298b2489cf392dda006c551acf2f2e991") << OP_CHECKSIG;

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock   = 0;
        genesis.hashMerkleRoot  = genesis.BuildMerkleTree();
        genesis.nVersion        = 1;
        genesis.nTime           = 1534859753; // August 21, 2018 (date +%s)
        genesis.nBits           = 0x207fffff;
        genesis.nNonce          = 5;

        // printf("ODIN MainNet\n");

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x37b3b9b0c61335f9cdb82fccfe70a8f123c3b812e2c658ef42f691a150074b9b"));
        assert(genesis.hashMerkleRoot == uint256("0xc0d5bcb3e4042c4b3068dcde64cfe1559987bdb7ea18394d9ca20ae5cc213253"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // vSeeds.push_back(CDNSSeedData("0", "142.93.128.134"));  // MN 0X
        // vSeeds.push_back(CDNSSeedData("1", "178.128.229.107")); // MN 00
        // vSeeds.push_back(CDNSSeedData("2", "142.93.177.49"));   // MN 01
        // vSeeds.push_back(CDNSSeedData("3", "209.97.182.78"));   // MN 02

        // value prefixed to addresses that consist of public keys
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115);

        // affixed to addresses that are the hashes of scripts
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 57);

        // value prefix for the private half of the pair
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 138);

        /*
          four-byte prefixes for the so-called “stealth addresses” that got introduced in Bitcoin version 0.9, which allow fun things like addresses that can be used to generate new keys that can receive payments but not spend them. These two should have the same first byte but must differ in the other three bytes.
        */
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x27)(0x56)(0x18)(0x72).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x27)(0x25)(0x67)(0x46).convert_to_container<std::vector<unsigned char> >();

        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x6f)(0x64)(0x69)(0x6e).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "odin";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04472764f5675aa5ae3c8f0b2b5d54bbd6d91b020a8dbd688350ed8646bc82f211f626c9db8bbdc1e51660f1630ffccca9736217cc6daa660c0154e459353a2a29";
	      strObfuscationPoolDummyAddress = "oPjJyuGDrFfT3vmiv1SHzFf9bgFwheKxpx";
        //nStartMasternodePayments = genesis.nTime + 500; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784406918290641249515082189298559149176184502808489120072844992687392807287776735971418347270261896375014971824691165077613379859095700097330459748808428401797429100642458691817195118746121515172654632282216869987549182422433637259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133844143603833904414952634432190114657544454178424020924616515723350778707749817125772467962926386356373289912154831438167899885040445364023527381951378636564391212010397122822120720357";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        pchMessageStart[0] = 0x63;
        pchMessageStart[1] = 0x17;
        pchMessageStart[2] = 0x37;
        pchMessageStart[3] = 0x22;

        vAlertPubKey = ParseHex("0402063889d534fb2b51e521c6f730586f86db8577cad991fb0f07c0c54cbc0cac32d8e42ca3cc6b98a76c2216e727ddb298b2489cf392dda006c551acf2f2e991");

        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;

        // Primary configurations
        nDefaultPort            = 34223;      // Main (testnet) P2P Port
        nLastPOWBlock           = 5000;       // Last Proof-of-Work block
        nMaturity               = 15;         // Transaction maturity
        nMasternodeCountDrift   = 4;          // TODO
        nMaxMoneyOut            = 43199500 * COIN; // TODO
        nModifierUpdateBlock    = 51197;      // TODO
        nRequiredAccumulation   = 1;          // TODO
        nTargetTimespan         = 1 * 60;     // TODO
        nTargetSpacing          = 1 * 10;     // Blocktime aim, ODIN: 1 minute
        bnProofOfWorkLimit      = ~uint256(0) >> 1;

        // Zerocoin Configurations
        nBudgetFeeConfirmations = 3;          // Number of confirmations for the finalization fee
                                              // We have to make this very short here because we only 
                                              // have a 8 block finalization window on testnet
        nZerocoinLastOldParams  = 100000000;  // TODO - Updated to defer zerocoin v2 for further testing
        nZerocoinStartHeight    = 201576;     // When zODIN becomes available

        //! Test-net Genesis (nTime a bit in the future)
        genesis.nTime           = 1535569392; // August 29, 2018 (date +%s)
        genesis.nBits           = 0x207fffff;
        genesis.nNonce          = 0;
        genesis.nVersion        = 1;
        genesis.hashMerkleRoot  = genesis.BuildMerkleTree();

        // Set hash genesis block
        hashGenesisBlock = genesis.GetHash();

        // Ensure validity
        assert(hashGenesisBlock == uint256("0x01519125dd84851de9437d61a24162610e8cba04d57f8a53765b7b0231e80866"));
        assert(genesis.hashMerkleRoot == uint256("0xc0d5bcb3e4042c4b3068dcde64cfe1559987bdb7ea18394d9ca20ae5cc213253"));

        // Remove seeding nodes
        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet odin addresses start with 'x' or 'y'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139);

        // Testnet odin script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);

        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);

        // Testnet odin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();

        // Testnet odin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();

        // Testnet odin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "odt";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04659d53bd8f7ad9d34a17281febedac754e5a6eb136142d3a9c6c0ea21b6ed7498ceb3d872eed00ae755f7aeadaeb1d9ab5e1a8f1e7efcd0ddcb39d4623c12790";
        strObfuscationPoolDummyAddress = "PCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";
        //nStartMasternodePayments = 1505224800; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        pchMessageStart[0] = 0x23;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x98;
        pchMessageStart[3] = 0x83;

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        // Primary configurations
        nDefaultPort            = 34223;        // Main (regtest) P2P Port
        nLastPOWBlock           = 999999999;    // Last Proof-of-Work block
        nMaturity               = 0;            // Transaction maturity
        nMasternodeCountDrift   = 20;           // TODO
        nMaxMoneyOut            = 2000000000 * COIN; // TODO
        nMaxReorganizationDepth = 100;          // TODO
        nMinerThreads           = 1;            // TODO
        nModifierUpdateBlock    = 999999999;    // TODO
        nRequiredAccumulation   = 1;            // TODO
        nTargetTimespan         = 24 * 60 * 60; // TODO
        nTargetSpacing          = 1 * 60;       // Blocktime aim, ODIN: 1 minute
        bnProofOfWorkLimit      = ~uint256(0) >> 1;

        // Zerocoin Configurations
        nZerocoinLastOldParams  = 499;  // TODO - Updated to defer zerocoin v2 for further testing.
        nZerocoinStartHeight    = 100;  // When zODIN becomes available

        //! Regtest-net Genesis
        genesis.nTime           = 1535569429; // (August 29, 2018) date +%s
        genesis.nBits           = 0x207fffff;
        genesis.nNonce          = 0;
        genesis.hashMerkleRoot  = genesis.BuildMerkleTree();

        // Set hash genesis block
        hashGenesisBlock = genesis.GetHash();

        // Set hash genesis block
        hashGenesisBlock = genesis.GetHash();

         // Ensure validity
        assert(hashGenesisBlock == uint256("0x57953c6db14b32b8fd1579c8aee7c2b7b2efd7ac9b15bbdf32fc96586cd69b5d"));
        assert(genesis.hashMerkleRoot == uint256("0xc0d5bcb3e4042c4b3068dcde64cfe1559987bdb7ea18394d9ca20ae5cc213253"));

        // Remove seeding nodes
        vFixedSeeds.clear();
        vSeeds.clear();
      
        bech32_hrp = "odnt";

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        strSporkKey = "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 34224;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
