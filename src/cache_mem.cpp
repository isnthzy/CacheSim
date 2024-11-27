#include "include/cache_mem.h"
#include "include/common.h"
#include "include/util.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

void Cache::init_cache(){
  bank_size = 1<<cache_params.index;
  line_word_size = cache_params.lineWidth/32;
  cache_mem.way = new cache_bank_t[cache_params.way];
  for(int i = 0; i < cache_params.way; i++){
    cache_mem.way[i].bank = new meta_data_t[bank_size];
    for(int j = 0; j < bank_size; j++){
      cache_mem.way[i].bank[j].valid = false;
      cache_mem.way[i].bank[j].tag   = 0;
    }
  }
}

void Cache::exit_cache(){
  if(cache_mem.way != NULL){
    for(int i = 0; i < cache_params.way; i++){
      delete [] cache_mem.way[i].bank;
    }
    delete [] cache_mem.way;
  }
}

void Cache::access(addr_t addr){
  bool access_miss = false;
  uint32_t bank_idx = (addr >> cache_params.offset) % (1 << cache_params.index);
  uint32_t tag = addr >> (cache_params.index + cache_params.offset);
  for(int i = 0; i < cache_params.way; i++){
    if(cache_mem.way[i].bank[bank_idx].valid 
    && cache_mem.way[i].bank[bank_idx].tag == tag){
      //NOTE:hit
      hit_count++;
      return; //命中后直接返回，防止命中多个way
    }else{
      //NOTE:miss
      access_miss = true;
    }
  }

  if(access_miss){ //NOTE:miss分开处理是因为替换的way不确定
    int way_idx = rand() % cache_params.way;
    cache_mem.way[way_idx].bank[bank_idx].valid = true;
    cache_mem.way[way_idx].bank[bank_idx].tag = tag;
  }
  return;
}

void Cache::run_sim(uint64_t n){
  addr_t addr;
  addr_t pc;
  for(uint64_t i = 0; i < n; i++){
    if(fscanf(mtrace_fp,"pc:%x addr:%x %*s:%*x,len:%*d", &pc, &addr)==EOF){
      printf_green("sim end");
      fclose(mtrace_fp);
      break;
    }
    mem_count++;
    access(addr);
  }  
  return;
}

void Cache::display(){
  printf("cache pamrams:\n");
  printf("tag:%d index:%d \
way:%d linewidth:%d\n",cache_params.tag, cache_params.index
                      ,cache_params.way, cache_params.lineWidth);
  printf("hit count:%ld mem count:%ld\n",hit_count, mem_count);
  printf("hit rate:%.3f\n",(double)hit_count / mem_count);
}