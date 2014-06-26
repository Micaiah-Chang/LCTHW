#include <lcthw/hashmap_algos.h>
#include <lcthw/bstrlib.h>

// settings taken from
// http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
const uint32_t FNV_PRIME = 16777619;
const uint32_t FNV_OFFSET_BASIS = 2166136261;
const uint32_t MURMUR_SEED = 0;

uint32_t Hashmap_bad_hash(void *data)
{
	 bstring s = (bstring)data;
	 uint32_t hash = 6136264; // random number I typed
	 int i = 0;

	 for (i = 0; i < blength(s); i++) {
		  hash ^= bchare(s, i, 0);
		  hash *= 9;
	 }

	 return hash;
	 
}


uint32_t Hashmap_fnv1a_hash(void *data)
{
	 bstring s = (bstring)data;
	 uint32_t hash = FNV_OFFSET_BASIS;
	 int i = 0;

	 for(i = 0; i < blength(s); i++) {
		  hash ^= bchare(s, i, 0);
		  hash *= FNV_PRIME;
	 }

	 return hash;
}
	 
const int MOD_ADLER = 65521;

uint32_t Hashmap_adler32_hash(void *data)
{
	 bstring s = (bstring)data;
	 uint32_t a = 1, b=0;
	 int i = 0;

	 for (i = 0; i < blength(s); i++) {
		  a = (a + bchare (s, i, 0)) % MOD_ADLER;
		  b = (b + a) % MOD_ADLER;
	 }

	 return (b << 16) | a;
}

uint32_t Hashmap_djb_hash(void *data)
{
	 bstring s = (bstring)data;
	 uint32_t hash = 5381;
	 int i = 0;

	 for (i = 0; i < blength(s); i++) {
		  hash = ((hash << 5) + hash) + bchare(s,i, 0); /* hash * 33 + c */
	 }

	 return hash;
}

uint32_t Hashmap_jenkins_hash(void *a)
{
	 size_t len = blength((bstring)a);
	 char *key = bdata((bstring)a);
	 uint32_t hash = 0;
	 uint32_t i = 0;

	 for(hash = i = 0; i < len; ++i) {
		  hash += key[i];
		  hash += (hash << 10);
		  hash ^= (hash >> 6);
	 }


	 hash += (hash << 3);
	 hash ^= (hash >> 11);
	 hash += (hash << 15);

	 return hash;
}



uint32_t Hashmap_murmur_hash(void *data)
{
	 char *key = bdata((bstring)data);
	 size_t len = blength((bstring)data);

	 int i = 0;

	 uint32_t c1 = 0xcc9e2d51;
	 uint32_t c2 = 0x1b873593;
	 uint32_t r1 = 15;
	 uint32_t r2 = 13;

	 uint32_t hash = MURMUR_SEED; 

	 uint32_t *blocks = (uint32_t *)key;
	 int blocklen = len /4;
	 uint32_t k = 0;
	 for(i = 0; i < blocklen; i++) {
		  k = blocks[i];
		  k *= c1;
		  k = (k << r1) | (k >> (32 - r1));
		  k *= c2;

		  hash ^= k;
		  hash = (hash << r2) | (hash >> (32-r2));
			   
	 }

	 const uint8_t *tail = (const uint8_t *)(key + blocklen * 4);
	 uint32_t k1 = 0;

	 switch (len & 3) {
	 case 3:
		  k1 ^= tail[2] << 16;
	 case 2:
		  k1 ^= tail[1] << 8;
	 case 1:
		  k1 ^= tail[0];

		  k1 *= c1;
		  k1 = (k1 << r1) | (k1 >> (32 - r1));
		  k1 *= c2;
		  hash ^= k1;
	 }

	 hash ^= len;
	 hash ^= (hash >> 16);
	 hash *= 0x85ebca6b;
	 hash ^= (hash >> 13);
	 hash *= 0xc2b2ae35;
	 hash ^= (hash >> 16);

	 return hash;
}

uint32_t Hashmap_hsieh_hash(void *data)
{
	 char *key = bdata((bstring)data);
	 size_t len = blength((bstring)data);
	 
	 uint32_t hash = len, tmp;
	 int rem;

	 if(len <= 0 || key == NULL) return 0;

	 rem = len & 3;

	 for(len >>= 2; len > 0; len--) {
		  hash += get16bits(key);
		  tmp = (get16bits(key+2) << 11) ^ hash;
		  hash = (hash << 16) ^ tmp;
		  key += 2*sizeof(uint16_t);
		  hash += hash >> 11;
	 }

	 switch (rem) {
	 case 3:
		  hash += get16bits(key);
		  hash ^= hash << 16;
		  hash ^= ((signed char)key[sizeof(uint16_t)]) << 18;
		  hash += hash >> 11;
		  break;
	 case 2:
		  hash += get16bits(key);
		  hash ^= hash << 11;
		  hash += hash >> 17;
	 case 1:
		  hash += (signed char)*key;
		  hash ^= hash << 10;
		  hash += hash >>1;
	 }

	 hash ^= hash << 3;
	 hash += hash >> 5;
	 hash ^= hash << 4;
	 hash += hash >> 17;
	 hash ^= hash << 25;
	 hash += hash >> 6;

	 return hash;
}
