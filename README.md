Generate Up Down Series
====

**I AM THE GREAT EVAN "THE GREAT" CARROLL**

Note this module uses `SFRM_Materialize_Preferred`. It will outperform
`generate_series` when materialization is required.

Synopsis
----

**The script inside the repo [`install_and_test`](./install_and_test)
demonstrates the Setup and Benchmarking entirely**

This extension can be used with

```sql
SELECT *
FROM generate_up_down_series_evan(n,m);
```

Like this

```sql
SELECT generate_up_down_series_evan(3,2);
 generate_up_down_series
-------------------------
                       1
                       2
                       3
                       3
                       2
                       1
                       1
                       2
                       3
                       3
                       2
                       1
```


Setup
----

First you'll need to compile. Note on Debian you'll need
`postgresql-server-dev-all` and `build-essentials`. Then you can install it
with

```sh
$ make
$ sudo make install
```

Then to add or remove the extension, use

```sql
CREATE EXTENSION generate_up_down_series;
DROP EXTENSION generate_up_down_series;
```

Background
----

This question was inspired by [this post by joanolo on
DBA.StackExchange](https://dba.stackexchange.com/q/160354/2639). Four years
after asked, [user Vérace](https://dba.stackexchange.com/a/301680/2639) decided
to benchmark all of these solutions, including mine. Though mine was the most
[charming, elegant, and bueatiful solution (using only SQL) it was not the most
efficient.](https://dba.stackexchange.com/a/160355/2639)

This is an obscene amount of overengineering. Don't do this. However, it should
be maximally fast. This is a [port of Erwin's answer to
C.](https://dba.stackexchange.com/a/160361/2639) just to win. Becuase that's what I DO.

Salt
----

* You can't do this (easily) with SQL Server (as it's not open source). It's
	basically just the devil's stateful abacus.
* Oracle will add this feature for US 2 BILLION DOLLARS.
* Go open source, or go home.
* I am the realest DBA, ever.
* MySQL is not real database.

Links
----

* [Erwin's logic](https://dba.stackexchange.com/a/160361/2639)
* Lots of copy-pasta from the [`generate_series` code in PostgreSQL](https://github.com/postgres/postgres/blob/c30f54ad732ca5c8762bb68bbe0f51de9137dd72/src/backend/utils/adt/int8.c#L1426)
* [PostgreSQL has the best docs ever](https://www.postgresql.org/docs/current/xfunc-c.html)
