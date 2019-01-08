#include "odictionary.h"
#include <stdlib.h>

ODICTIONARY odictionary_create(uint8_t max_entries)
{
  ODICTIONARY d;
  d.records =
      (ODICTIONARY_ENTRY *)malloc(sizeof(ODICTIONARY_ENTRY) * max_entries);
  d.max_entries = max_entries;
  d.num_entries = 0;

  for (uint8_t i = 0; i < max_entries; i++)
  {
    d.records[i].is_used = false;
  }

  return d;
}

ODICTIONARY odictionary_free(ODICTIONARY *d)
{
  if (d->records != NULL)
  {
    free(d->records);

    d->records = NULL;
    d->num_entries = 0;
    d->max_entries = 0;
  }
}

ODICTIONARY_ENTRY *odictionary_lookup(ODICTIONARY *d, ODICTIONARY_VALUE key)
{
  uint8_t entries_used = 0;
  for (uint8_t i = 0; (i < d->max_entries) || (entries_used < d->num_entries);
       i++)
  {
    ODICTIONARY_ENTRY *e = &d->records[i];
    if (e->is_used)
    {
      entries_used++;
    }

    if (e->key.uint_val == key.uint_val && e->is_used)
    {
      return e;
    }
  }

  return NULL;
}

bool odictionary_set(ODICTIONARY *d, ODICTIONARY_VALUE key,
                     ODICTIONARY_VALUE value)
{
  if (d->num_entries >= d->max_entries)
  {
    return false;
  }

  ODICTIONARY_ENTRY *entry_for_key = odictionary_lookup(d, key);

  if (entry_for_key != NULL)
  {
    entry_for_key->value = value;

    return true;
  }

  for (uint8_t i = 0; i < d->max_entries; i++)
  {
    ODICTIONARY_ENTRY *e = &d->records[i];

    if (!e->is_used)
    {
      e->key = key;
      e->value = value;
      e->is_used = true;
      d->num_entries++;

      return true;
    }
  }

  return false;
}

void odictionary_unset(ODICTIONARY *d, ODICTIONARY_VALUE key)
{
  ODICTIONARY_ENTRY *e = odictionary_lookup(d, key);

  if (e != NULL)
  {
    e->is_used = false;
    d->num_entries--;
  }
}

uint8_t odictionary_size(ODICTIONARY *d) { return d->num_entries; }
