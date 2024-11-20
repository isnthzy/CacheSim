#include "include/cache_mem.h"

void Cache::init_cache(){
  bank_size = 1<<cache_params.index;
  line_word_size = cache_params.lineWidth/32;
  cache_mem.way = new cache_bank_t[cache_params.way];
  for(int i = 0; i < cache_params.way; i++){
    cache_mem.way[i].bank = new meta_data_t[bank_size];
    for(int j = 0; j < bank_size; j++){
      cache_mem.way[i].bank[j].valid = false;
      cache_mem.way[i].bank[j].tag   = 0;
      cache_mem.way[i].bank[j].data_word = new line_word_t[line_word_size]; 
    }
  }
}

void Cache::exit_cache(){
  for(int i = 0; i < cache_params.way; i++){
    for(int j = 0; j < bank_size; j++){
      delete [] cache_mem.way[i].bank[j].data_word;
    }
    delete [] cache_mem.way[i].bank;
  }
  delete [] cache_mem.way;
}

void Cache::run_sim(uint64_t n){
  
}

