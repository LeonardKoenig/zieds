/*
*   Zieds - A C implementation of a bloom filter
*   Copyright (C) <2016>  Grif Hughes - ghughes@smu.edu
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include "bloom_filter.h"
#include "hashes.h"

#define SET_BIT(bf, k) (bf->buf[k >> 4] |= 1 << (k % 16))
#define TEST_BIT(bf, k) (bf->buf[k >> 4] & 1 << (k % 16))

#define H_a(pointer, bytes, out) (MurmurHash3_x86_32((void *)pointer, bytes, 0, out))
#define H_b(pointer, bytes) (FNV1A_Hash_WHIZ((void *)pointer, bytes))
#define G(in, scalar, pointer, bytes, size) (abs(in[0] + scalar * H_b(pointer, bytes)) % size)

void bloom_insert_int(struct bloom_filter *bf, const int32_t data)
{
        uint8_t i;
        uint32_t hash[4];

        H_a(&data, sizeof(data), hash);
        for(i = 0; i < bf->nhashes; ++i)
                SET_BIT(bf, G(hash, i, &data, sizeof(data), bf->mbits));
}

void bloom_insert_string(struct bloom_filter *bf, const char *data)
{
        uint8_t i;
        uint32_t hash[4];
        uint64_t len = strlen(data);

        H_a(data, len, hash);
        for(i = 0; i < bf->nhashes; ++i)
                SET_BIT(bf, G(hash, i, data, len, bf->mbits));
}

bool bloom_query_int(struct bloom_filter *bf, const int32_t data)
{
        uint8_t i;
        uint32_t hash[4];

        H_a(&data, sizeof(data), hash);
        for(i = 0; i < bf->nhashes; ++i)
                if(!TEST_BIT(bf, G(hash, i, &data, sizeof(data), bf->mbits)))
                        return false;
        return true;
}

bool bloom_query_string(struct bloom_filter *bf, const char *data)
{
        uint8_t i;
        uint32_t hash[4];
        uint64_t len = strlen(data);

        H_a(data, len, hash);
        for(i = 0; i < bf->nhashes; ++i)
                if(!TEST_BIT(bf, G(hash, i, data, len, bf->mbits)))
                        return false;
        return true;
}
