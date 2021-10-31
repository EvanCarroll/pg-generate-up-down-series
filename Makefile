EXTENSION = generate_up_down_series
MODULE_big = generate_up_down_series
DATA = generate_up_down_series--0.0.1.sql
OBJS = generate_up_down_series.o 
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
PG_CFLAGS += $(PERMIT_DECLARATION_AFTER_STATEMENT)
include $(PGXS)
