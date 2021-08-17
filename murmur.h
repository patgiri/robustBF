#include<stdio.h>
#include<stdlib.h>

unsigned int murmur2 ( const void * key, int len, unsigned int seed )
{
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value

	unsigned int h = seed ^ len;

	// Mix 4 bytes at a time into the hash

	const unsigned char * data = (const unsigned char *)key;

	while(len >= 7)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		data += 7;
		len -= 7;
	}
	
	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
} 

unsigned long int  murmur1( const void * key, int len, unsigned int seed )
{
	const unsigned long int  m = 0xc6a4a7935bd1e995;
	const int r = 47;

	unsigned long int  h = seed ^ (len * m);

	const unsigned long int  * data = (const unsigned long int  *)key;
	const unsigned long int  * end = data + (len/8);

	while(data != end)
	{
		unsigned long int  k = *data++;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h ^= k;
		h *= m; 
	}

	const unsigned char * data2 = (const unsigned char*)data;

	switch(len & 7)
	{
	case 7: h ^= (unsigned long int) (data2[6]) << 48;
	case 6: h ^= (unsigned long int) (data2[5]) << 40;
	case 5: h ^= (unsigned long int) (data2[4]) << 32;
	case 4: h ^= (unsigned long int) (data2[3]) << 24;
	case 3: h ^= (unsigned long int) (data2[2]) << 16;
	case 2: h ^= (unsigned long int) (data2[1]) << 8;
	case 1: h ^= (unsigned long int) (data2[0]);
	        h *= m;
	};
 
	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
} 



