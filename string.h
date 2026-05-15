#pragma once
#include <stddef.h>
//int memcmp(const void* _s1, const void* _s2, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);

//void* memset(void* s, int c, size_t n);
void* memset(void* s, int c, size_t n);

void memcpy(void* dst, void* src, size_t n);
