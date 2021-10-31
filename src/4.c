//--- REIMPORT
#include <math.h>
#include <unistd.h>
//--

Datum generate_up_down_series_4(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(generate_up_down_series_4);

typedef struct
{
	size_t		current;
	uint32    m;
	uint32		n2;
	Datum     data[FLEXIBLE_ARRAY_MEMBER];
} fctx_4;

Datum
generate_up_down_series_4(PG_FUNCTION_ARGS)
{
  
	if (SRF_IS_FIRSTCALL()) {
		int32 n = PG_GETARG_INT32(0);
		int32 m = PG_GETARG_INT32(1);
		int32 n2 = n*2-1;
	
		ReturnSetInfo *rsinfo = (ReturnSetInfo *) fcinfo->resultinfo;
		
		if ( rsinfo->allowedModes & SFRM_Materialize_Preferred ) {
			rsinfo->returnMode = SFRM_Materialize;

			MemoryContext   per_query_ctx  = rsinfo->econtext->ecxt_per_query_memory;
			MemoryContext   oldcontext     = MemoryContextSwitchTo(per_query_ctx);

			Tuplestorestate *tupstore      = tuplestore_begin_heap(false, false, work_mem);
			rsinfo->setResult              = tupstore;

			TupleDesc       tupdesc        = rsinfo->expectedDesc;

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

		else {
			FuncCallContext *funcctx = SRF_FIRSTCALL_INIT();
			MemoryContext oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
		
			fctx_4 *fctx = (fctx_4 *) palloc(
				sizeof(fctx_4)
				+ ( 2 * n * sizeof(Datum))
			);
		
			for ( size_t idx = 0; idx < n; idx++ ) {
				// Set the up-sequence
				fctx->data[idx] = Int32GetDatum(idx + 1);
				// Set the down-sequence
				fctx->data[n + idx] = Int32GetDatum(n - idx);
			}

			fctx->current = 0;
			fctx->m  = m;
			fctx->n2 = n2;

			funcctx->user_fctx = fctx;
			MemoryContextSwitchTo(oldcontext);
		}

	}
	
	FuncCallContext *funcctx = SRF_PERCALL_SETUP();
	fctx_4 *fctx = funcctx->user_fctx;

	if ( fctx->current <= fctx->n2 ) {
		Datum result = fctx->data[fctx->current];
		if (
			(fctx->current)++ == (fctx->n2)
			&& --(fctx->m) > 0
		) { fctx->current = 0; }
		
		SRF_RETURN_NEXT(funcctx, result);
	}
	else {
		SRF_RETURN_DONE(funcctx);
	}

	PG_RETURN_NULL();
}
