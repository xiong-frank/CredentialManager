﻿#pragma once

#include <cstdint>

namespace xf::encrypt
{

	inline void _swap(unsigned char& a, unsigned char& b)
	{
		if (a != b)
			a ^= b ^= a ^= b;
	}

	void memory_xor(unsigned char* out, const unsigned char* in, unsigned int n);
	void memory_copy(unsigned char* out, const unsigned char* in, unsigned int n);
	
	void mix_sbox(unsigned char* sbox, unsigned int len, const void* key, unsigned int n);

	template<unsigned int len>
	void mix_sbox(unsigned char(&sbox)[len], const void* key, unsigned int n)
	{
		mix_sbox(sbox, len, key, n);
	}

}