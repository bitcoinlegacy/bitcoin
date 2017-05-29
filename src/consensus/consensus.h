// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <stdint.h>

/** BIP102 block size increase height */
static const unsigned int BIP102_FORK_MIN_HEIGHT = 485218;

// TODO
// static const unsigned int BIP102_FORK_BUFFER = (90 * 144); // approx 3 mos.

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
static const unsigned int MAX_BLOCK_SERIALIZED_SIZE = 4000000;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
static const unsigned int MAX_BLOCK_WEIGHT = 4000000;
/** The maximum allowed size for a block excluding witness data, in bytes (network rule) */
static const unsigned int MAX_LEGACY_BLOCK_SIZE = (1 * 1000 * 1000);
inline unsigned int MaxBlockBaseSize(int nHeight, bool fSegWitActive)
{
    static const unsigned int newSize = (2 * 1000 * 1000);

    if (nHeight < (int)BIP102_FORK_MIN_HEIGHT)
        return MAX_LEGACY_BLOCK_SIZE;

    if (!fSegWitActive)
        return MAX_LEGACY_BLOCK_SIZE;

    // TODO: BIP102_FORK_BUFFER

    return newSize;
}

inline unsigned int MaxBlockBaseSize()
{
    return MaxBlockBaseSize(99999999, true);
}


/** The maximum allowed number of signature check operations in a block (network rule) */
static const int64_t MAX_LEGACY_SIGOPS_COST = 80000;
inline int64_t MaxBlockSigOpsCost(int nHeight, bool fSegWitActive)
{
    return ((MaxBlockBaseSize(nHeight, fSegWitActive) / 50) * 4);
}

inline int64_t MaxBlockSigOpsCost()
{
    return MaxBlockSigOpsCost(99999999, true);
}

/** The maximum allowed number of transactions per block */
static const unsigned int MAX_BLOCK_VTX_SIZE = 1000000;

/** The maximum allowed size for a transaction, excluding witness data, in bytes */
static const unsigned int MAX_TX_BASE_SIZE = 1000000;

/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 100;

/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
