/******************************************************************************
 * Copyright © 2014-2019 The SuperNET Developers.                             *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * SuperNET software, including this file may be copied, modified, propagated *
 * or distributed except according to the terms contained in the LICENSE file *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#include "komodo_defs.h"

#include "uthash.h"
#include "utlist.h"

/*#ifdef _WIN32
#define PACKED
#else
#define PACKED __attribute__((packed))
#endif*/

#ifndef CHUNGUSCOIN_STRUCTS_H
#define CHUNGUSCOIN_STRUCTS_H

#define GENESIS_NBITS 0x1f00ffff
#define CHUNGUSCOIN_MINRATIFY ((height < 90000) ? 7 : 11)
#define CHUNGUSCOIN_NOTARIES_HARDCODED 180000 // DONT CHANGE
#define CHUNGUSCOIN_MAXBLOCKS 250000 // DONT CHANGE

#define CHUNGUSCOIN_EVENT_RATIFY 'P'
#define CHUNGUSCOIN_EVENT_NOTARIZED 'N'
#define CHUNGUSCOIN_EVENT_KMDHEIGHT 'K'
#define CHUNGUSCOIN_EVENT_REWIND 'B'
#define CHUNGUSCOIN_EVENT_PRICEFEED 'V'
#define CHUNGUSCOIN_EVENT_OPRETURN 'R'
#define CHUNGUSCOIN_OPRETURN_DEPOSIT 'D'
#define CHUNGUSCOIN_OPRETURN_ISSUED 'I' // assetchain
#define CHUNGUSCOIN_OPRETURN_WITHDRAW 'W' // assetchain
#define CHUNGUSCOIN_OPRETURN_REDEEMED 'X'

#define CHUNGUSCOIN_KVPROTECTED 1
#define CHUNGUSCOIN_KVBINARY 2
#define CHUNGUSCOIN_KVDURATION 1440
#define CHUNGUSCOIN_ASSETCHAIN_MAXLEN 65

#ifndef _BITS256
#define _BITS256
    union _bits256 { uint8_t bytes[32]; uint16_t ushorts[16]; uint32_t uints[8]; uint64_t ulongs[4]; uint64_t txid; };
    typedef union _bits256 bits256;
#endif    

union _bits320 { uint8_t bytes[40]; uint16_t ushorts[20]; uint32_t uints[10]; uint64_t ulongs[5]; uint64_t txid; };
typedef union _bits320 bits320;

struct chunguscoin_kv { UT_hash_handle hh; bits256 pubkey; uint8_t *key,*value; int32_t height; uint32_t flags; uint16_t keylen,valuesize; };

struct chunguscoin_event_notarized { uint256 blockhash,desttxid,MoM; int32_t notarizedheight,MoMdepth; char dest[16]; };
struct chunguscoin_event_pubkeys { uint8_t num; uint8_t pubkeys[64][33]; };
struct chunguscoin_event_opreturn { uint256 txid; uint64_t value; uint16_t vout,oplen; uint8_t opret[]; };
struct chunguscoin_event_pricefeed { uint8_t num; uint32_t prices[35]; };

struct chunguscoin_event
{
    struct chunguscoin_event *related;
    uint16_t len;
    int32_t height;
    uint8_t type,reorged;
    char symbol[CHUNGUSCOIN_ASSETCHAIN_MAXLEN];
    uint8_t space[];
};

struct pax_transaction
{
    UT_hash_handle hh;
    uint256 txid;
    uint64_t chunguscoinshis,fiatoshis,validated;
    int32_t marked,height,otherheight,approved,didstats,ready;
    uint16_t vout;
    char symbol[CHUNGUSCOIN_ASSETCHAIN_MAXLEN],source[CHUNGUSCOIN_ASSETCHAIN_MAXLEN],coinaddr[64]; uint8_t rmd160[20],type,buf[35];
};

struct knotary_entry { UT_hash_handle hh; uint8_t pubkey[33],notaryid; };
struct knotaries_entry { int32_t height,numnotaries; struct knotary_entry *Notaries; };
struct notarized_checkpoint
{
    uint256 notarized_hash,notarized_desttxid,MoM,MoMoM;
    int32_t nHeight,notarized_height,MoMdepth,MoMoMdepth,MoMoMoffset,kmdstarti,kmdendi;
};

struct chunguscoin_ccdataMoM
{
    uint256 MoM;
    int32_t MoMdepth,notarized_height,height,txi;
};

struct chunguscoin_ccdata_entry { uint256 MoM; int32_t notarized_height,kmdheight,txi; char symbol[65]; };
struct chunguscoin_ccdatapair { int32_t notarized_height,MoMoMoffset; };

struct chunguscoin_ccdataMoMoM
{
    uint256 MoMoM;
    int32_t kmdstarti,kmdendi,MoMoMoffset,MoMoMdepth,numpairs,len;
    struct chunguscoin_ccdatapair *pairs;
};

struct chunguscoin_ccdata
{
    struct chunguscoin_ccdata *next,*prev;
    struct chunguscoin_ccdataMoM MoMdata;
    uint32_t CCid,len;
    char symbol[65];
};

struct chunguscoin_state
{
    uint256 NOTARIZED_HASH,NOTARIZED_DESTTXID,MoM;
    int32_t SAVEDHEIGHT,CURRENT_HEIGHT,NOTARIZED_HEIGHT,MoMdepth;
    uint32_t SAVEDTIMESTAMP;
    uint64_t deposited,issued,withdrawn,approved,redeemed,shorted;
    struct notarized_checkpoint *NPOINTS; int32_t NUM_NPOINTS,last_NPOINTSi;
    struct chunguscoin_event **Chunguscoin_events; int32_t Chunguscoin_numevents;
    uint32_t RTbufs[64][3]; uint64_t RTmask;
};

#endif /* CHUNGUSCOIN_STRUCTS_H */
