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

#ifndef H_CHUNGUSCOINEVENTS_H
#define H_CHUNGUSCOINEVENTS_H
#include "komodo_defs.h"

struct chunguscoin_event *chunguscoin_eventadd(struct chunguscoin_state *sp,int32_t height,char *symbol,uint8_t type,uint8_t *data,uint16_t datalen)
{
    struct chunguscoin_event *ep=0; uint16_t len = (uint16_t)(sizeof(*ep) + datalen);
    if ( sp != 0 && ASSETCHAINS_SYMBOL[0] != 0 )
    {
        portable_mutex_lock(&chunguscoin_mutex);
        ep = (struct chunguscoin_event *)calloc(1,len);
        ep->len = len;
        ep->height = height;
        ep->type = type;
        strcpy(ep->symbol,symbol);
        if ( datalen != 0 )
            memcpy(ep->space,data,datalen);
        sp->Chunguscoin_events = (struct chunguscoin_event **)realloc(sp->Chunguscoin_events,(1 + sp->Chunguscoin_numevents) * sizeof(*sp->Chunguscoin_events));
        sp->Chunguscoin_events[sp->Chunguscoin_numevents++] = ep;
        portable_mutex_unlock(&chunguscoin_mutex);
    }
    return(ep);
}

void chunguscoin_eventadd_notarized(struct chunguscoin_state *sp,char *symbol,int32_t height,char *dest,uint256 notarized_hash,uint256 notarized_desttxid,int32_t notarizedheight,uint256 MoM,int32_t MoMdepth)
{
    static uint32_t counter; int32_t verified=0; char *coin; struct chunguscoin_event_notarized N;
    coin = (ASSETCHAINS_SYMBOL[0] == 0) ? (char *)"KMD" : ASSETCHAINS_SYMBOL;
    if ( IS_CHUNGUSCOIN_NOTARY != 0 && (verified= chunguscoin_verifynotarization(symbol,dest,height,notarizedheight,notarized_hash,notarized_desttxid)) < 0 )
    {
        if ( counter++ < 100 )
            LogPrintf("[%s] error validating notarization ht.%d notarized_height.%d, if on a pruned %s node this can be ignored\n",ASSETCHAINS_SYMBOL,height,notarizedheight,dest);
    }
    else if ( strcmp(symbol,coin) == 0 )
    {
        if ( 0 && IS_CHUNGUSCOIN_NOTARY != 0 && verified != 0 )
            LogPrintf("validated [%s] ht.%d notarized %d\n",coin,height,notarizedheight);
        memset(&N,0,sizeof(N));
        N.blockhash = notarized_hash;
        N.desttxid = notarized_desttxid;
        N.notarizedheight = notarizedheight;
        N.MoM = MoM;
        N.MoMdepth = MoMdepth;
        strncpy(N.dest,dest,sizeof(N.dest)-1);
        chunguscoin_eventadd(sp,height,symbol,CHUNGUSCOIN_EVENT_NOTARIZED,(uint8_t *)&N,sizeof(N));
        if ( sp != 0 )
            chunguscoin_notarized_update(sp,height,notarizedheight,notarized_hash,notarized_desttxid,MoM,MoMdepth);
    }
}

void chunguscoin_eventadd_pubkeys(struct chunguscoin_state *sp,char *symbol,int32_t height,uint8_t num,uint8_t pubkeys[64][33])
{
    struct chunguscoin_event_pubkeys P;
    //printf("eventadd pubkeys ht.%d\n",height);
    memset(&P,0,sizeof(P));
    P.num = num;
    memcpy(P.pubkeys,pubkeys,33 * num);
    chunguscoin_eventadd(sp,height,symbol,CHUNGUSCOIN_EVENT_RATIFY,(uint8_t *)&P,(int32_t)(sizeof(P.num) + 33 * num));
    if ( sp != 0 )
        chunguscoin_notarysinit(height,pubkeys,num);
}

void chunguscoin_eventadd_pricefeed(struct chunguscoin_state *sp,char *symbol,int32_t height,uint32_t *prices,uint8_t num)
{
    struct chunguscoin_event_pricefeed F;
    if ( num == sizeof(F.prices)/sizeof(*F.prices) )
    {
        memset(&F,0,sizeof(F));
        F.num = num;
        memcpy(F.prices,prices,sizeof(*F.prices) * num);
        chunguscoin_eventadd(sp,height,symbol,CHUNGUSCOIN_EVENT_PRICEFEED,(uint8_t *)&F,(int32_t)(sizeof(F.num) + sizeof(*F.prices) * num));
        if ( sp != 0 )
            chunguscoin_pvals(height,prices,num);
    } //else LogPrintf("skip pricefeed[%d]\n",num);
}

void chunguscoin_eventadd_opreturn(struct chunguscoin_state *sp,char *symbol,int32_t height,uint256 txid,uint64_t value,uint16_t vout,uint8_t *buf,uint16_t opretlen)
{
    struct chunguscoin_event_opreturn O; uint8_t *opret;
    if ( ASSETCHAINS_SYMBOL[0] != 0 )
    {
        opret = (uint8_t *)calloc(1,sizeof(O) + opretlen + 16);
        O.txid = txid;
        O.value = value;
        O.vout = vout;
        memcpy(opret,&O,sizeof(O));
        memcpy(&opret[sizeof(O)],buf,opretlen);
        O.oplen = (int32_t)(opretlen + sizeof(O));
        chunguscoin_eventadd(sp,height,symbol,CHUNGUSCOIN_EVENT_OPRETURN,opret,O.oplen);
        free(opret);
        if ( sp != 0 )
            chunguscoin_opreturn(height,value,buf,opretlen,txid,vout,symbol);
    }
}

void chunguscoin_event_undo(struct chunguscoin_state *sp,struct chunguscoin_event *ep)
{
    switch ( ep->type )
    {
        case CHUNGUSCOIN_EVENT_RATIFY: LogPrintf("rewind of ratify, needs to be coded.%d\n",ep->height); break;
        case CHUNGUSCOIN_EVENT_NOTARIZED: break;
        case CHUNGUSCOIN_EVENT_KMDHEIGHT:
            if ( ep->height <= sp->SAVEDHEIGHT )
                sp->SAVEDHEIGHT = ep->height;
            break;
        case CHUNGUSCOIN_EVENT_PRICEFEED:
            // backtrack prices;
            break;
        case CHUNGUSCOIN_EVENT_OPRETURN:
            // backtrack opreturns
            break;
    }
}

void chunguscoin_event_rewind(struct chunguscoin_state *sp,char *symbol,int32_t height)
{
    struct chunguscoin_event *ep;
    if ( sp != 0 )
    {
        if ( ASSETCHAINS_SYMBOL[0] == 0 && height <= CHUNGUSCOIN_LASTMINED && prevCHUNGUSCOIN_LASTMINED != 0 )
        {
            LogPrintf("undo CHUNGUSCOIN_LASTMINED %d <- %d\n",CHUNGUSCOIN_LASTMINED,prevCHUNGUSCOIN_LASTMINED);
            CHUNGUSCOIN_LASTMINED = prevCHUNGUSCOIN_LASTMINED;
            prevCHUNGUSCOIN_LASTMINED = 0;
        }
        while ( sp->Chunguscoin_events != 0 && sp->Chunguscoin_numevents > 0 )
        {
            if ( (ep= sp->Chunguscoin_events[sp->Chunguscoin_numevents-1]) != 0 )
            {
                if ( ep->height < height )
                    break;
                //printf("[%s] undo %s event.%c ht.%d for rewind.%d\n",ASSETCHAINS_SYMBOL,symbol,ep->type,ep->height,height);
                chunguscoin_event_undo(sp,ep);
                sp->Chunguscoin_numevents--;
            }
        }
    }
}

void chunguscoin_setkmdheight(struct chunguscoin_state *sp,int32_t kmdheight,uint32_t timestamp)
{
    if ( sp != 0 )
    {
        if ( kmdheight > sp->SAVEDHEIGHT )
        {
            sp->SAVEDHEIGHT = kmdheight;
            sp->SAVEDTIMESTAMP = timestamp;
        }
        if ( kmdheight > sp->CURRENT_HEIGHT )
            sp->CURRENT_HEIGHT = kmdheight;
    }
}

void chunguscoin_eventadd_kmdheight(struct chunguscoin_state *sp,char *symbol,int32_t height,int32_t kmdheight,uint32_t timestamp)
{
    uint32_t buf[2];
    if ( kmdheight > 0 )
    {
        buf[0] = (uint32_t)kmdheight;
        buf[1] = timestamp;
        chunguscoin_eventadd(sp,height,symbol,CHUNGUSCOIN_EVENT_KMDHEIGHT,(uint8_t *)buf,sizeof(buf));
        if ( sp != 0 )
            chunguscoin_setkmdheight(sp,kmdheight,timestamp);
    }
    else
    {
        //LogPrintf("REWIND kmdheight.%d\n",kmdheight);
        kmdheight = -kmdheight;
        chunguscoin_eventadd(sp,height,symbol,CHUNGUSCOIN_EVENT_REWIND,(uint8_t *)&height,sizeof(height));
        if ( sp != 0 )
            chunguscoin_event_rewind(sp,symbol,height);
    }
}


/*void chunguscoin_eventadd_deposit(int32_t actionflag,char *symbol,int32_t height,uint64_t chunguscoinshis,char *fiat,uint64_t fiatoshis,uint8_t rmd160[20],bits256 kmdtxid,uint16_t kmdvout,uint64_t price)
 {
 uint8_t opret[512]; uint16_t opretlen;
 chunguscoin_eventadd_opreturn(symbol,height,CHUNGUSCOIN_OPRETURN_DEPOSIT,kmdtxid,chunguscoinshis,kmdvout,opret,opretlen);
 }
 
 void chunguscoin_eventadd_issued(int32_t actionflag,char *symbol,int32_t height,int32_t fiatheight,bits256 fiattxid,uint16_t fiatvout,bits256 kmdtxid,uint16_t kmdvout,uint64_t fiatoshis)
 {
 uint8_t opret[512]; uint16_t opretlen;
 chunguscoin_eventadd_opreturn(symbol,height,CHUNGUSCOIN_OPRETURN_ISSUED,fiattxid,fiatoshis,fiatvout,opret,opretlen);
 }
 
 void chunguscoin_eventadd_withdraw(int32_t actionflag,char *symbol,int32_t height,uint64_t chunguscoinshis,char *fiat,uint64_t fiatoshis,uint8_t rmd160[20],bits256 fiattxid,int32_t fiatvout,uint64_t price)
 {
 uint8_t opret[512]; uint16_t opretlen;
 chunguscoin_eventadd_opreturn(symbol,height,CHUNGUSCOIN_OPRETURN_WITHDRAW,fiattxid,fiatoshis,fiatvout,opret,opretlen);
 }
 
 void chunguscoin_eventadd_redeemed(int32_t actionflag,char *symbol,int32_t height,bits256 kmdtxid,uint16_t kmdvout,int32_t fiatheight,bits256 fiattxid,uint16_t fiatvout,uint64_t chunguscoinshis)
 {
 uint8_t opret[512]; uint16_t opretlen;
 chunguscoin_eventadd_opreturn(symbol,height,CHUNGUSCOIN_OPRETURN_REDEEMED,kmdtxid,chunguscoinshis,kmdvout,opret,opretlen);
 }*/

// process events
//

#endif
