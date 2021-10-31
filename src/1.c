Datum generate_up_down_series_1(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(generate_up_down_series_1);

typedef struct
{
	uint32		current;
	uint32    n;
	uint32		n2m;
} generate_series_fctx_1;

Datum
generate_up_down_series_1(PG_FUNCTION_ARGS)
{
	FuncCallContext *funcctx;
	generate_series_fctx_1 *fctx;
	uint32		result;
	MemoryContext oldcontext;

	/* stuff done only on the first call of the function */
	if (SRF_IS_FIRSTCALL())
	{
		int32 n = PG_GETARG_INT32(0);
		int32 m = PG_GETARG_INT32(1);

		/* create a function context for cross-call persistence */
		funcctx = SRF_FIRSTCALL_INIT();

		/*
		 * switch to memory context appropriate for multiple function calls
		 */
		oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

		/* allocate memory for user context */
		fctx = (generate_series_fctx_1 *) palloc(sizeof(generate_series_fctx_1));

		/*
		 * Use fctx to keep state from call to call. Seed current with the
		 * original n value
		 */
		fctx->current = 0;
		fctx->n = n;
		fctx->n2m = n*2*m - 1;

		funcctx->user_fctx = fctx;
		MemoryContextSwitchTo(oldcontext);
	}

	funcctx = SRF_PERCALL_SETUP();

	fctx = funcctx->user_fctx;

	if (
		fctx->current <= fctx->n2m
	)
	{
		uint32 n = fctx->n;
		uint32 e = fctx->current;
		uint32 n2 = e % (n*2);
		result = n2 < n ? n2 + 1 : n*2 - n2;
		
		(fctx->current)++;
		
		SRF_RETURN_NEXT(funcctx, Int32GetDatum(result));
	}
	else {
		/* do when there is no more left */
		SRF_RETURN_DONE(funcctx);
	}
}

