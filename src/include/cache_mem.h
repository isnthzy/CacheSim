#ifndef __CACHE_MEM_H__
#define __CACHE_MEM_H__
#include <cstdint>

typedef struct CacheBankLine{
  uint8_t bit[4];
}line_word_t;

typedef struct MetaData{
  uint32_t      tag;
  bool          valid;
  line_word_t  *data_word;
}meta_data_t;

typedef struct CacheBank{
  meta_data_t *bank;
}cache_bank_t;

typedef struct CacheWay{
  cache_bank_t *way;
}cache_way_t;

typedef struct CacheParameters{
  int way;
  int tag;
  int index;
  int lineWidth;
}cache_parameters_t;

class Cache{
private:
  cache_way_t cache_mem;
  cache_parameters_t cache_params; //FIXME: 为param设置初始值
  int bank_size;
  int line_word_size;
public:
  void init_cache();
  void exit_cache();
  void run_sim(uint64_t n);
  void set_cache_params(cache_parameters_t params);
};

extern Cache *global_cache;
#endif /* __CACHE_MEM_H__ */