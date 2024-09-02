/*
 *  Copyright 2016 Henry Lee
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "hash.h"
#include "tables.h"

static short binaries_by_id[52] = {
	0x1,	0x1,	0x1,	0x1,
	0x2,	0x2,	0x2,	0x2,
	0x4,	0x4,	0x4,	0x4,
	0x8,	0x8,	0x8,	0x8,
	0x10,	0x10,	0x10,	0x10,
	0x20,	0x20,	0x20,	0x20,
	0x40,	0x40,	0x40,	0x40,
	0x80,	0x80,	0x80,	0x80,
	0x100,	0x100,	0x100,	0x100,
	0x200,	0x200,	0x200,	0x200,
	0x400,	0x400,	0x400,	0x400,
	0x800,	0x800,	0x800,	0x800,
	0x1000,	0x1000,	0x1000,	0x1000,
};

static short suitbit_by_id[52] = {
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
	0x1,	0x8,	0x40,	0x200,
};

/*
 * Card id, ranged from 0 to 51.
 * The two least significant bits represent the suit, ranged from 0-3.
 * The rest of it represent the rank, ranged from 0-12.
 * 13 * 4 gives 52 ids.
 */
int evaluate_6cards(int a, int b, int c, int d, int e, int f)
{
	int i;
	int suit_hash = 0;
	int suit_binary[4] = {0};
	unsigned char quinary[13] = {0};
	int hash;

	suit_hash += suitbit_by_id[a];
	quinary[(a >> 2)]++;
	suit_hash += suitbit_by_id[b];
	quinary[(b >> 2)]++;
	suit_hash += suitbit_by_id[c];
	quinary[(c >> 2)]++;
	suit_hash += suitbit_by_id[d];
	quinary[(d >> 2)]++;
	suit_hash += suitbit_by_id[e];
	quinary[(e >> 2)]++;
	suit_hash += suitbit_by_id[f];
	quinary[(f >> 2)]++;

	if (suits[suit_hash])
	{
		suit_binary[a & 0x3] |= binaries_by_id[a];
		suit_binary[b & 0x3] |= binaries_by_id[b];
		suit_binary[c & 0x3] |= binaries_by_id[c];
		suit_binary[d & 0x3] |= binaries_by_id[d];
		suit_binary[e & 0x3] |= binaries_by_id[e];
		suit_binary[f & 0x3] |= binaries_by_id[f];

		return flush[suit_binary[suits[suit_hash]-1]];
	}

	hash = hash_quinary(quinary, 13, 6);

	return noflush6[hash];
}

