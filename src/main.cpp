#include <cstddef>
#include <cstdio>
#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include "include/cache_mem.h"
#include "include/util.h"

Cache *global_cache;
static cache_parameters_t cache_params = {
  .way = 0,
  .tag = 0,
  .index = 0,
};
static char *trace_file = NULL;
/*NOTE:参数解析
way -> w //way数量
tag -> t //tag宽度
index -> i //index宽度
lineWidth -> l //bank里每一行的宽度，bank_size用index计算出来
*/

//NOTE:想法，通过参数解析，初始化cache,malloc出响应大小的结构体

void init_trace(char *trace_file) {
  if(trace_file == NULL) panic("need trace_file to sim");
  if(strstr(trace_file, "itrace") != NULL) global_cache->set_trace_type(TYPE_ITRACE);
  else if(strstr(trace_file, "mtrace") != NULL) global_cache->set_trace_type(TYPE_MTRACE);
  global_cache->set_trace_fp(trace_file);
  return;
}

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"way"      , required_argument, NULL, 'w'},
    {"tag"      , required_argument, NULL, 't'},
    {"index"    , required_argument, NULL, 'i'},
    {"line"     , required_argument, NULL, 'l'},
    {"trace"    , required_argument, NULL, 'r'},
    {"help"     , no_argument      , NULL, 'h'},
    {0          , 0                , NULL, 0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-hw:t:i:l:r:", table, NULL)) != -1) {
    switch (o) {
      case 'w': sscanf(optarg, "%d", &cache_params.way);       break;
      case 't': sscanf(optarg, "%d", &cache_params.tag);       break;
      case 'i': sscanf(optarg, "%d", &cache_params.index);     break;
      case 'r': trace_file = optarg;                                    break;
      default:
        printf("Usage: %s [OPTION...] trace [args]\n\n", argv[0]);
        printf("\t-w,--way=num            set way num\n");
        printf("\t-t,--tag=width          set tag width\n");
        printf("\t-i,--index=width        set index width\n");
        printf("\t-l,--line=width         set line width\n");
        printf("\t-r,--trace=FILE         read {i,m}trace FILE to sim\n");
        printf("\n");
        exit(0);
    }
  }
  return 0;
}


void init_sim(int argc, char* argv[]) {
  global_cache = new Cache;
  parse_args(argc,argv);
  if(cache_params.way == 0   || cache_params.tag == 0 
  || cache_params.index == 0){
    printf_red("no cache params,use default params to init cache");
  }else{
    global_cache->set_cache_params(cache_params);
  }
  init_trace(trace_file);
  global_cache->init_cache();

  return;
}

void exit_sim(){
  if(global_cache != NULL){
    global_cache->exit_cache();
    delete global_cache;
  }
}

int main(int argc, char* argv[]) {
  init_sim(argc,argv);
  global_cache->run_sim(-1);
  global_cache->display();
  exit_sim();
}