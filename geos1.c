/* geos1.c */

#include <stdio.h>  /* for printf */
#include <stdarg.h> /* for va_list */

/* Only the CAPI header is required */
#include <geos_c.h>

static void
geos_msg_handler(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf (fmt, ap);
    va_end(ap);
}

int main()
{
    /* Send notice and error messages to the terminal */
    GEOSContextHandle_t ctx = GEOS_init_r ();
    GEOSContext_setNoticeHandler_r(ctx, geos_msg_handler);
    GEOSContext_setErrorHandler_r(ctx, geos_msg_handler);

    /* Read WKT into geometry object */
    GEOSWKTReader* reader = GEOSWKTReader_create_r(ctx);
    GEOSGeometry* geom_a = GEOSWKTReader_read_r(ctx, reader, "POLYGON ((0 0, 1 0, 1 1, 0.5 0.5, 0 1, 0 0))");

    GEOSGeometry* geom_b =  GEOSConstrainedDelaunayTriangulation_r(ctx, geom_a);

    /* Convert result to WKT */
    GEOSWKTWriter* writer = GEOSWKTWriter_create_r(ctx);
    char* wkt = GEOSWKTWriter_write_r(ctx, writer, geom_b);
    printf("Geometry: %s\n", wkt);

    /* Clean up allocated objects */
    GEOSWKTReader_destroy_r(ctx, reader);
    GEOSWKTWriter_destroy_r(ctx, writer);
    GEOSGeom_destroy_r(ctx, geom_a);
    GEOSGeom_destroy_r(ctx, geom_b);

    GEOSFree_r(ctx, wkt);

    /* Clean up the global context */
    GEOS_finish_r(ctx);
    return 0;
}
