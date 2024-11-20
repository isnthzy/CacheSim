#include <stdio.h>
#include <getopt.h>
#include "include/cache_mem.h"
Cache *global_cache;
/*NOTE:参数解析
way -> w //way数量
tag -> t //tag宽度
index -> i //宽度
lineWidth -> l //bank里每一行的宽度，bank_size用index计算出来
*/

//NOTE:想法，通过参数解析，初始化cache,malloc出响应大小的结构体
//NOTE:创建出一个lineWidth宽度，banksize类型的数组，然后通过index下标访问相应的lineWidth,同时也需要考虑way带来的影响


static int parse_args(int argc, char *argv[]) {
  cache_parameters_t cache_params;
  const struct option table[] = {
    {"way"      , required_argument, NULL, 'w'},
    {"tag"      , required_argument, NULL, 't'},
    {"index"    , required_argument, NULL, 'i'},
    {"line"     , required_argument, NULL, 'l'},
    {0          , 0                , NULL, 0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-w:t:i:l:", table, NULL)) != -1) {
    switch (o) {
      case 'w': sscanf(optarg, "%d", &cache_params.way);       break;
      case 't': sscanf(optarg, "%d", &cache_params.tag);       break;
      case 'i': sscanf(optarg, "%d", &cache_params.index);     break;
      case 'l': sscanf(optarg, "%d", &cache_params.lineWidth); break;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-w,--way=num            set way num\n");
        printf("\t-t,--tag=width          set tag width\n");
        printf("\t-i,--index=width        set index width\n");
        printf("\t-l,--line=width         set line width\n");
        printf("\n");
        // exit_sim();
    }
  }
  global_cache->set_cache_params(cache_params);
  return 0;
}


void init_sim(int argc, char* argv[]) {
  global_cache = new Cache;
  parse_args(argc,argv);
  global_cache->init_cache();
}

// void exit_sim(){

// }

int main(int argc, char* argv[]) {
  init_sim(argc,argv);

  global_cache->run_sim(-1);
  global_cache->exit_cache();
  delete global_cache;
}