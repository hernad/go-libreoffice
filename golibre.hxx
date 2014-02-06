#include <stdio.h>
// uzeto iz liblibreffice.hxx
#include <string.h>
#include <osl/module.h>
#include "libre.h"

class GoLODocument
{
    // C struct
    LibreOfficeDocumentG *mpDoc;
public:
    inline GoLODocument( LibreOfficeDocumentG *pDoc ) : mpDoc( pDoc ) {}
    inline ~GoLODocument() { mpDoc->destroy( mpDoc ); }

    // Save as the given format, if format is NULL sniff from ext'n
    inline bool saveAs( const char *url, const char *format = NULL )
    {
        return mpDoc->saveAs( mpDoc, url, format );
    }
};


class GoLibreOffice
{
    // C struct
    LibreOfficeG *mpThis;

public:
    inline GoLibreOffice( LibreOfficeG *pThis ) : mpThis( pThis ) { printf("GoLibreOffice constructor\n"); }
    inline ~GoLibreOffice() { mpThis->destroy( mpThis ); };

    inline bool initialize( const char *installPath )
    {
        printf("GoLibreOffice initialize %s\n", installPath);
        return mpThis->initialize( mpThis, installPath );
    }

    inline GoLODocument *documentLoad( const char *url )
    {
        LibreOfficeDocumentG *pDoc = mpThis->documentLoad( mpThis, url );
        if( !pDoc )
            return NULL;
        return new GoLODocument( pDoc );
    }

    // return the last error as a string, free me.
    inline char *getError() { return mpThis->getError( mpThis ); }
};

inline GoLibreOffice *lo_cpp_init_g( const char *install_path )
{

    printf("lo_cpp_init_g start\n");    
    LibreOfficeG *pThis = libsoffice_init( install_path );

    if( !pThis || pThis->nSize == 0 ) {
        printf("lo_cpp_init_g libsoffice_init vratio null ?!\n");
        return NULL;
    }
    printf("lo_cpp_init_g before return\n");
    return new GoLibreOffice( pThis );
}


OUString getAbsoluteURL( const char *pURL );
