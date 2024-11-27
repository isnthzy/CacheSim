CACHE_TAG   = 26
CACHE_INDEX = 4
CACHE_WAY   = 2 
CACHE_LINE  = 128


ARGS = --way=$(CACHE_WAY) --index=$(CACHE_INDEX) \
			 --tag=$(CACHE_TAG) --line=$(CACHE_LINE)