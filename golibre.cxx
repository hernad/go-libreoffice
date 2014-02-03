#include <sal/config.h>

#include <rtl/strbuf.hxx>
#include <osl/file.hxx>
#include <osl/time.h>

#include "scdll.hxx"
#include "formulacell.hxx"
#include "stringutil.hxx"
#include "scmatrix.hxx"
#include "drwlayer.hxx"
#include "scitems.hxx"
#include "reffind.hxx"
#include "markdata.hxx"
#include "clipparam.hxx"
#include "refundo.hxx"
#include "undoblk.hxx"
#include "undotab.hxx"
#include "queryentry.hxx"
#include "postit.hxx"
#include "attrib.hxx"
#include "dbdata.hxx"
#include "reftokenhelper.hxx"
#include "userdat.hxx"

#include "docsh.hxx"
#include "docfunc.hxx"
#include "dbdocfun.hxx"
#include "funcdesc.hxx"
#include "externalrefmgr.hxx"

#include "calcconfig.hxx"
#include "interpre.hxx"
#include "columniterator.hxx"
#include "types.hxx"
#include "conditio.hxx"
#include "globstr.hrc"
#include "tokenarray.hxx"
#include "scopetools.hxx"
#include "dociter.hxx"
#include "queryparam.hxx"
#include "edittextiterator.hxx"
#include "editutil.hxx"

#include "formula/IFunctionDescription.hxx"

#include <basegfx/polygon/b2dpolygon.hxx>
#include <editeng/boxitem.hxx>
#include <editeng/brushitem.hxx>
#include "editeng/wghtitem.hxx"
#include "editeng/postitem.hxx"

#include <svx/svdograf.hxx>
#include <svx/svdpage.hxx>
#include <svx/svdocirc.hxx>
#include <svx/svdopath.hxx>
#include "svl/srchitem.hxx"
#include "svl/sharedstringpool.hxx"

#include <sfx2/docfile.hxx>
#include <sfx2/sfxmodelfactory.hxx>

#include <iostream>
#include <sstream>
#include <vector>

#include <tools/errinf.hxx>
#include <rtl/strbuf.hxx>
#include <rtl/bootstrap.hxx>
#include <cppuhelper/bootstrap.hxx>
#include <comphelper/processfactory.hxx>

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/document/MacroExecMode.hpp>
#include <com/sun/star/drawing/XDrawPageSupplier.hpp>
#include <com/sun/star/drawing/XShapes.hpp>
#include <com/sun/star/drawing/XShape.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/TextContentAnchorType.hpp>

#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ucb/XUniversalContentBroker.hpp>

#include <vcl/svapp.hxx>
#include <tools/resmgr.hxx>
#include <vcl/graphicfilter.hxx>
#include <unotools/syslocaleoptions.hxx>

#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>


#include <com/sun/star/awt/XTopWindow.hpp> 
#include <com/sun/star/util/URLTransformer.hpp> 
#include <com/sun/star/util/XURLTransformer.hpp> 
#include <com/sun/star/util/XCloseable.hpp> 
#include <com/sun/star/frame/XDispatchProvider.hpp> 
#include <com/sun/star/lang/ServiceNotRegisteredException.hpp> 
#include <com/sun/star/configuration/MissingBootstrapFileException.hpp> 
#include <com/sun/star/configuration/InvalidBootstrapFileException.hpp> 
#include <com/sun/star/configuration/InstallationIncompleteException.hpp> 
#include <com/sun/star/configuration/backend/BackendSetupException.hpp> 
#include <com/sun/star/configuration/backend/BackendAccessException.hpp> 
#include <com/sun/star/task/theJobExecutor.hpp> 
#include <com/sun/star/task/OfficeRestartManager.hpp> 
#include <com/sun/star/task/XRestartManager.hpp> 
#include <com/sun/star/document/XEventListener.hpp> 
#include <com/sun/star/frame/theUICommandDescription.hpp> 
#include <com/sun/star/ui/UIElementFactoryManager.hpp> 
#include <com/sun/star/ui/WindowStateConfiguration.hpp> 
#include <com/sun/star/frame/XUIControllerRegistration.hpp> 
#include <com/sun/star/frame/ToolbarControllerFactory.hpp> 
#include <com/sun/star/frame/PopupMenuControllerFactory.hpp> 
#include <com/sun/star/office/Quickstart.hpp> 

#include <comphelper/processfactory.hxx>
#include <comphelper/synchronousdispatch.hxx>
#include <com/sun/star/util/XCloseable.hpp>
#include <com/sun/star/util/CloseVetoException.hpp>
#include <com/sun/star/task/InteractionHandler.hpp>
#include <com/sun/star/util/URL.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/container/XEnumeration.hpp>
#include <com/sun/star/frame/XFramesSupplier.hpp>
#include <com/sun/star/frame/XDispatch.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/view/XPrintable.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/util/URLTransformer.hpp>
#include <com/sun/star/util/XURLTransformer.hpp>
#include <com/sun/star/document/MacroExecMode.hpp>
#include <com/sun/star/document/UpdateDocMode.hpp>
#include <com/sun/star/frame/XStorable.hpp>

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h> 

#include "golibre.hxx"

#include "sofficemain.h"

void open_calc();

extern "C" int lo_demo_1 ()
{
    GoLibreOffice *pOffice = lo_cpp_init_g( "/usr/local/lib/libreoffice/program" );
    if( !pOffice )
    {
        fprintf( stderr, "inicijalizacija neuspjesna\n" );
        return -1;
    } else
        fprintf( stdout, "inicijalizacija ok\n");
 

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

    //printf("usleep ....\n");
    //usleep(100000000);

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
            fprintf( stderr, "Save pdf  ok\n" );
     }
  

    delete pDocument;
    delete pOffice;

    open_calc();

    return 0;
}
using namespace ::com::sun::star;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::ui;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::container;

void  open_calc() 
{


static Reference <com::sun::star::uno::XComponentContext> xContext;
static Reference <com::sun::star::lang::XMultiServiceFactory> xSFactory;
static Reference <com::sun::star::lang::XMultiComponentFactory> xFactory;


printf("init xContext, xFactory, xSFactory\n");
xContext = cppu::defaultBootstrap_InitialComponentContext();
    fprintf( stderr, "Uno initialized %d\n", xContext.is() );
    xFactory = xContext->getServiceManager();
    xSFactory = uno::Reference<lang::XMultiServiceFactory>(xFactory, uno::UNO_QUERY_THROW);
    comphelper::setProcessServiceFactory(xSFactory);

//const sal_Char SUSPEND_QUICKSTARTVETO[] = "SuspendQuickstartVeto";

Sequence < com::sun::star::beans::PropertyValue > args(1);
args[0].Name = "Hidden";
args[0].Value <<= sal_True;



//Reference< XDesktop2 > xDesktop = css::frame::Desktop::create( xContext );
//Reference< XPropertySet > xPropertySet(xDesktop, UNO_QUERY_THROW);
//xPropertySet->setPropertyValue( OUString(SUSPEND_QUICKSTARTVETO ), Any((sal_Bool)sal_True) );

printf("comploader\n");
Reference < com::sun::star::frame::XDesktop2 > xComponentLoader = com::sun::star::frame::Desktop::create(xContext);

try {
      Reference < com::sun::star::lang::XComponent >  xComp = xComponentLoader->loadComponentFromURL( OUString("private:factory/scalc"), OUString("_blank"), 0, Sequence < com::sun::star::beans::PropertyValue >() );
 

/*
     Reference < ::com::sun::star::calc::XSpreadSheetDocument > xSpreadSheetDoc = UnoRuntime.queryInterface(
                XSpreadsheetDocument.class, xComp);

      //xDoc->close( sal_True );
      xDoc->open( sal_True );
*/

} catch ( const com::sun::star::uno::Exception& )
{
    printf("ne mogu kreirati scalc\n");
}

printf("kreirao scalc doc\n");

soffice_main();

}

