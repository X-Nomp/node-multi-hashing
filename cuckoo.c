// Cuckoo Cycle, a memory-hard proof-of-work
// Copyright (c) 2013-2016 John Tromp

#include "cuckoo.h"
#include <inttypes.h> // for SCNx64 macro
#include <stdio.h>    // printf/scanf
#include <stdlib.h>   // exit
#include <unistd.h>   // getopt
#include <assert.h>   // d'uh

// arbitrary length of header hashed into siphash key
#define HEADERLEN 80

void cuckoo_hash(const char* input, const char *nonces, uint32_t len, char* output){
    char headernonce[HEADERLEN];
    siphash_keys keys;
    memcpy(headernonce, input, 56);
    memset(headernonce+56, 0, sizeof(headernonce)-56);
    setheader(headernonce, sizeof(headernonce), &keys);
    int pow_rc = verify(&nonces, &keys);
    if ( pow_rc == POW_OK ){
        blake2b((void *)output, 32, (const void *)nonces, len, 0, 0);
    }
    else{
        memset(output, 0, 32);
    }
}

