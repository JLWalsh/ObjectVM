#ifndef ODICTIONARY_H
#define ODICTIONARY_H

#include "otypes.h"
#include <stdbool.h>
#include <stdint.h>

typedef union ODICTIONARY_VALUE_T {
  OVM_UINT uint_val;
  void *ptr_val;
} ODICTIONARY_VALUE;

typedef struct ODICTIONARY_ENTRY_T
{
  ODICTIONARY_VALUE key;
  ODICTIONARY_VALUE value;
  bool is_used;
} ODICTIONARY_ENTRY;

typedef struct ODICTIONARY_T
{
  ODICTIONARY_ENTRY *records;
  uint8_t num_entries;
  uint8_t max_entries;
} ODICTIONARY;

ODICTIONARY odictionary_create(uint8_t max_entries);

ODICTIONARY odictionary_free(ODICTIONARY *d);

ODICTIONARY_ENTRY *odictionary_lookup(ODICTIONARY *d, ODICTIONARY_VALUE key);

bool odictionary_set(ODICTIONARY *d, ODICTIONARY_VALUE key,
                     ODICTIONARY_VALUE value);

void odictionary_unset(ODICTIONARY *d, ODICTIONARY_VALUE key);

uint8_t odictionary_size(ODICTIONARY *d);

#endif /* ODICTIONARY_H */
