#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>

#include "golibre.hxx"

extern "C" int lo_demo_1 ()
{
    GoLibreOffice *pOffice = lo_cpp_init_g( "/usr/local/lib/libreoffice/program" );
    if( !pOffice )
    {
        fprintf( stderr, "Failed to initialize shared library\n" );
        return -1;
    } else
        fprintf( stdout, "Shared library initialized\n");
 

    // This separate init is lame I think.
    if( !pOffice->initialize( "/usr/local/lib/libreoffice/program"   ) )
    {
        fprintf( stderr, "failed to initialize /usr/local/lib/libreoffice/program\n" );
        return -1;
    }

    fprintf( stderr, "start to load document '%s'\n", "/home/bringout/test.ods" );
    GoLODocument *pDocument = pOffice->documentLoad(  "/home/bringout/test.ods" );
    if( !pDocument )
    {
        char *pError = pOffice->getError();
        fprintf( stderr, "failed to load document '%s': '%s'\n",
                "/home/bringout/test.ods" , pError );
        free (pError);
        return -1;
    }

    const char *pFilter = NULL;
    pFilter = "pdf";
    fprintf( stderr, "save document as '%s' (%s)\n", "test.pdf", pFilter ? pFilter : "<null>" );
    if( !pDocument->saveAs( "test.pdf", pFilter ) )
    {
            char *pError = pOffice->getError();
            fprintf( stderr, "failed to save document '%s'\n", pError);
            free (pError);
     }
     else
     {
            fprintf( stderr, "Save pdf succeeded\n" );
     }
  
    fprintf( stderr, "all tests passed.\n" );

    delete pDocument;
    delete pOffice;

    return 0;
}


