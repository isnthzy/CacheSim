#ifndef __CACHE_MEM_H__
#define __CACHE_MEM_H__
#include <cstdint>
#include <cstdio>
#include "common.h"
#include "util.h"

enum trace_type{
  TYPE_ITRACE, TYPE_MTRACE
};

typedef struct MetaData{
  uint32_t      tag;
  bool          valid;
  uint32_t      other; //保留用于cache替换等操作
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
  int offset;
  int lineWidth;
}cache_parameters_t;

class Cache{
private:
  cache_way_t cache_mem;
  cache_parameters_t cache_params = { .way = 2 , .tag = 26 ,\
    .index = 4 , .offset = 2, .lineWidth = 128 \
  }; 
  int bank_size;
  int line_word_size;
  trace_type trace_type = TYPE_ITRACE; //NOTE:0代表 itrace , 1 代表 mtrace
  FILE *trace_fp;
  uint64_t hit_count; //命中的次数
  uint64_t mem_count; //访存的次数
  void access(addr_t addr);
  bool scan_traces();
public:
  void init_cache();
  void exit_cache();
  void run_sim(uint64_t n);
  void display();

  void set_cache_params(cache_parameters_t params){
    cache_params = params;
    cache_params.offset = ADDR_WIDTH - cache_params.index - cache_params.tag;
    cache_params.lineWidth = (1 << (cache_params.offset - 2)) * 32;
  }
  void set_trace_fp(char *trace_file){
    trace_fp = fopen(trace_file,"r");
    if(trace_fp == NULL) panic("trace_file is NULL");
    printf("The file is %s\n", trace_file);
  }
  void set_trace_type(enum trace_type type){
    trace_type = type;
  }
};

extern Cache *global_cache;
#endif /* __CACHE_MEM_H__ */