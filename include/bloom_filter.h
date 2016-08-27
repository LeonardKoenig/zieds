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

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define BLOOM_INIT(bf)                                         \
	bf = malloc(sizeof(struct bloom_filter));              \
	bf->nelems = 100;                                      \
	bf->mbits = 1600;                                      \
	bf->nhashes = 11;                                      \
	bf->buf = calloc(bf->nelems, sizeof(uint16_t));

#define BLOOM_INIT_NELEMS(bf, nelems)                          \
	bf = malloc(sizeof(struct bloom_filter));              \
	bf->nelems = nelems;                                   \
	bf->mbits = bf->nelems * (sizeof(uint16_t) << 3);      \
	bf->nhashes = (bf->mbits / bf->nelems) * log(2);       \
	bf->buf = calloc(bf->nelems, sizeof(uint16_t));

#define BLOOM_FREE(bf)                                         \
	free(bf->buf);                                         \
	free(bf);

struct bloom_filter {
        uint8_t nhashes; /* optimal number of hashes unless explicit (m / n * ln(2)) */
        uint16_t *buf; /* bits per element */
        uint32_t nelems; /* number of elements */
        uint32_t mbits; /* number of bits (16 * nelems) */
};

void bloom_insert_bytes(struct bloom_filter *bf, const char *data, size_t len);
void bloom_insert_int(struct bloom_filter *bf, const int32_t data);
void bloom_insert_string(struct bloom_filter *bf, const char *data);
bool bloom_query_int(struct bloom_filter *bf, const int32_t data);
bool bloom_query_string(struct bloom_filter *bf, const char *data);

#endif
