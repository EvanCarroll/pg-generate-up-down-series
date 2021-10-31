//--- REIMPORT
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
//--

Datum generate_up_down_series_3(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(generate_up_down_series_3);

Datum
generate_up_down_series_3(PG_FUNCTION_ARGS)
{
  
	ReturnSetInfo   *rsinfo        = (ReturnSetInfo *) fcinfo->resultinfo;
	rsinfo->returnMode = SFRM_Materialize;

	MemoryContext   per_query_ctx  = rsinfo->econtext->ecxt_per_query_memory;
	MemoryContext   oldcontext     = MemoryContextSwitchTo(per_query_ctx);

	Tuplestorestate *tupstore      = tuplestore_begin_heap(false, false, work_mem);
	rsinfo->setResult = tupstore;

	TupleDesc       tupdesc        = rsinfo->expectedDesc;

	int32 n = PG_GETARG_INT32(0);
	int32 m = PG_GETARG_INT32(1);
	
	Datum values[1] = {};
	bool nulls[sizeof(values)] = {0};

	while ( m-- ) {
		unsigned int idx = 0;
		while ( idx < n ) {
			values[0] = Int32GetDatum(++idx);
			tuplestore_putvalues(tupstore, tupdesc, values, nulls);
		}
		while ( idx > 0 ) {
			values[0] = Int32GetDatum(idx--);
			tuplestore_putvalues(tupstore, tupdesc, values, nulls);
		}
	}

	tuplestore_donestoring(tupstore);
	MemoryContextSwitchTo(oldcontext);

	PG_RETURN_NULL();
}
