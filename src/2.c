Datum generate_up_down_series_2(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(generate_up_down_series_2);

typedef struct
{
	size_t		current;
	uint32    m;
	uint32		n2;
	Datum     data[FLEXIBLE_ARRAY_MEMBER];
} fctx_2;

Datum
generate_up_down_series_2(PG_FUNCTION_ARGS)
{
	if (SRF_IS_FIRSTCALL())
	{
		int32 n = PG_GETARG_INT32(0);
		int32 m = PG_GETARG_INT32(1);

		FuncCallContext *funcctx = SRF_FIRSTCALL_INIT();
		MemoryContext oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

		fctx_2 *fctx = (fctx_2 *) palloc(
			sizeof(fctx_2)
			+ ( 2 * n * sizeof(Datum))
		);
		
		for ( size_t idx = 0; idx < n; idx++ ) {
			// Set the up-sequence
			fctx->data[idx] = Int32GetDatum(idx + 1);
			// Set the down-sequence
			fctx->data[n + idx] = Int32GetDatum(n - idx);
		}

		fctx->current = 0;
		fctx->m       = m;
		fctx->n2      = n*2 - 1;

		funcctx->user_fctx = fctx;
		MemoryContextSwitchTo(oldcontext);
	}

	FuncCallContext *funcctx = SRF_PERCALL_SETUP();

	fctx_2 *fctx = funcctx->user_fctx;

	if ( fctx->current <= fctx->n2 ) {
		Datum result = fctx->data[fctx->current];
		if (
			(fctx->current)++ == (fctx->n2)
			&& --(fctx->m) > 0
		) { fctx->current = 0; }
		
		SRF_RETURN_NEXT(funcctx, result);
	}
	
	SRF_RETURN_DONE(funcctx);
}

