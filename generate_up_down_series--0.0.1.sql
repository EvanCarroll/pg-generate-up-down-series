
CREATE FUNCTION generate_up_down_series_evan(n int4, m int4)
RETURNS TABLE(seq int4)
AS 'MODULE_PATHNAME', 'generate_up_down_series_4'
LANGUAGE C STRICT VOLATILE;

-- CREATE FUNCTION generate_up_down_series_1(n int4, m int4)
-- RETURNS TABLE(seq int4)
-- AS 'MODULE_PATHNAME', 'generate_up_down_series_1'
-- LANGUAGE C STRICT VOLATILE;
-- 
-- CREATE FUNCTION generate_up_down_series_2(n int4, m int4)
-- RETURNS TABLE(seq int4)
-- AS 'MODULE_PATHNAME', 'generate_up_down_series_2'
-- LANGUAGE C STRICT VOLATILE;
-- 
-- CREATE FUNCTION generate_up_down_series_3(n int4, m int4)
-- RETURNS TABLE(seq int4)
-- AS 'MODULE_PATHNAME', 'generate_up_down_series_3'
-- LANGUAGE C STRICT VOLATILE;

-- CREATE FUNCTION generate_up_down_series_4(n int4, m int4)
-- RETURNS TABLE(seq int4)
-- AS 'MODULE_PATHNAME', 'generate_up_down_series_4'
-- LANGUAGE C STRICT VOLATILE;
