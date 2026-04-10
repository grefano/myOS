#pragma once

//int memcmp(const void* _s1, const void* _s2, size_t n);
int memcmp(const void* s1, const void* s2, size_t n){
  unsigned char* _s1 = (unsigned char*) s1;
  unsigned char* _s2 = (unsigned char*) s2;
  for(size_t i = 0; i < n; i++){
    if (_s1[i] != _s2[i]){
      if (_s1[i] != _s2[i]) return _s1[i] - _s2[i];
    }
  }
  return 0;
} 

//void* memset(void* s, int c, size_t n);
void* memset(void* s, int c, size_t n){
  int* _s = (int*) s;
  for(size_t i = 0; i < n; i++){
    _s[n] = c;
  }
}
