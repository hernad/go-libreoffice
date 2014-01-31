// uzeto iz shim.c
#include "libre.h"

#include <stdio.h>
#include <string.h>

#include <osl/module.h>
#include <sal/types.h>

#include <dlfcn.h>
#ifdef AIX
#  include <sys/ldr.h>
#endif


#define TARGET_LIB SAL_MODULENAME( "sofficeapp" )
// definise se tip HookFunction
typedef LibreOfficeG *(HookFunction)(void);

SAL_DLLPUBLIC_EXPORT LibreOfficeG *libsoffice_init( const char *install_path )
{
    char *imp_lib;
    void *dlhandle;
    HookFunction *pSym;

/*
    printf("libsoffice_init loads shared library with liblibreoffice_hook function\n");

    if( !install_path )
        return NULL;
    if( !( imp_lib = (char *) malloc( strlen (install_path) + sizeof( TARGET_LIB ) + 2 ) ) )
    {
        fprintf( stderr, "failed to open library : not enough memory\n");
        return NULL;
    }

    strcpy( imp_lib, install_path );
    strcat( imp_lib, "/" );
    //libsofficeapp.so
    strcat( imp_lib, TARGET_LIB );

    if( !( dlhandle = dlopen( imp_lib, RTLD_LAZY ) ) )

    pSym = (HookFunction *) dlsym( dlhandle, "liblibreoffice_hook" );
    if( !pSym ) {
        fprintf( stderr, "failed to find hook in library '%s'\n", imp_lib );
        free( imp_lib );
        return NULL;
    } else
        printf("nasao liblibreoffice_hook\n");

    free( imp_lib );
*/
    pSym = libreoffice_hook_g;
    printf("return liblibreoffice_hook symbol_g\n");
    return pSym();
}


