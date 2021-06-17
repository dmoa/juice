#pragma once

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

inline u64 hash_string(string str) {
    u64 hash = FNV_OFFSET;
    for (u16 i = 0; i < str.len; i++) {
        hash ^= (u64) str.str[i];
        hash *= FNV_PRIME;
    }
    return hash;
}

// For we know, we assume all hashtables use strings as keys because we don't have any hashtables which don't use strings as keys.
// When that changes, we'll change this code.

// How many items are we going to store at a time?
// Basically, we aren't going to reallocate memory everytime we add an item,
// only every HT_MALLOC_INTERVAL times.
#define HT_MALLOC_INTERVAL 8

template <typename T>
struct Entry {
    T entry;
    string key;
    bool initialised = false;
};

struct ht {
    u8 num_entries = 0;
    Entry* entries;

    Add(string str, T value) {

        if (num_entries % HT_MALLOC_INTERVAL == 0) {
            entries = realloc(entries, sizeof(Entry) * (num_entries + HT_MALLOC_INTERVAL) );
        }

        index = hash_string(str) % 8;
        real_index = index;
        for (int i = 0; i < num-entries; i++) {

        }
        entries[index]
        num_entries++;
    }
};