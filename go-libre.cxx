/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <sal/config.h>
#include <test/bootstrapfixture.hxx>

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
#include "com/sun/star/util/URLTransformer.hpp" 
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

#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>

#include <liblibreoffice.hxx>

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

static void aBasicErrorFunc( const OUString &rErr, const OUString &rAction )
{
    OStringBuffer aErr( "Unexpected dialog: " );
    aErr.append( OUStringToOString( rAction, RTL_TEXTENCODING_ASCII_US ) );
    aErr.append( " Error: " );
    aErr.append( OUStringToOString( rErr, RTL_TEXTENCODING_ASCII_US ) );
}


void init_lo() {

    printf("init-lo-1\n");
    // force locale (and resource files loaded) to en-US
    OUString aLangISO( "en-US" );
    ResMgr::SetDefaultLocale( LanguageTag( aLangISO) );

    printf("init-lo-2\n");
/*
    SvtSysLocaleOptions aLocalOptions;
    aLocalOptions.SetLocaleConfigString( aLangISO );
    aLocalOptions.SetUILocaleConfigString( aLangISO );
*/
    printf("init-lo-3\n");
    InitVCL();

/*
    Reference< XMultiServiceFactory > xMS;
    xMS = cppu::createRegistryServiceFactory( OUString( "applicat.rdb" ), sal_True );

   com::sun::star::uno::Reference< com::sun::star::lang::XMultiServiceFactory> xMSch;
   com::sun::star::uno::Reference< com::sun::star::uno::XComponentContext > xComponentContext;
           xComponentContext = cppu::defaultBootstrap_InitialComponentContext();
       xMSch.set(xComponentContext->getServiceManager(), com::sun::star::uno::UNO_QUERY);
       comphelper::setProcessServiceFactory(xMSch);

    comphelper::setProcessServiceFactory(xMS);

    InitVCL();
    ::Main();
    DeInitVCL();

*/

    if (Application::IsHeadlessModeRequested())
        Application::EnableHeadlessMode(true);

    printf("init-lo-4\n");
    //if (bAssertOnDialog)
    if (1)
        ErrorHandler::RegisterDisplay( aBasicErrorFunc );

    // Make GraphicConverter work, normally done in desktop::Desktop::Main()
    //Application::SetFilterHdl(
    //        STATIC_LINK(0, test::BootstrapFixture, ImplInitFilterHdl));


/*
    //if (bNeedUCB)
    if (0)
    {
        // initialise unconfigured UCB:
        uno::Reference<ucb::XUniversalContentBroker> xUcb(pSFactory->createInstance("com.sun.star.ucb.UniversalContentBroker"), uno::UNO_QUERY_THROW);
        uno::Reference<ucb::XContentProvider> xFileProvider(pSFactory->createInstance("com.sun.star.ucb.FileContentProvider"), uno::UNO_QUERY_THROW);
        xUcb->registerContentProvider(xFileProvider, "file", sal_True);
        uno::Reference<ucb::XContentProvider> xTdocProvider(pSFactory->createInstance("com.sun.star.ucb.TransientDocumentsContentProvider"), uno::UNO_QUERY);
        if (xTdocProvider.is())
        {
            xUcb->registerContentProvider(xTdocProvider, "vnd.sun.star.tdoc", sal_True);
        }
    }
*/

}

using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::task;
//using namespace ::com::sun::star::system;
using namespace ::com::sun::star::ui;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::container;

extern "C" void calc_1() 
{

const sal_Char SUSPEND_QUICKSTARTVETO[] = "SuspendQuickstartVeto";

Sequence < com::sun::star::beans::PropertyValue > args(1);
args[0].Name = "Hidden";
args[0].Value <<= sal_True;

Reference< XDesktop2 > xDesktop = css::frame::Desktop::create( ::comphelper::getProcessComponentContext() );
Reference< XPropertySet > xPropertySet(xDesktop, UNO_QUERY_THROW);
xPropertySet->setPropertyValue( OUString(SUSPEND_QUICKSTARTVETO ), Any((sal_Bool)sal_True) );

try {
      Reference < ::com::sun::star::util::XCloseable > xDoc( xDesktop->loadComponentFromURL( OUString("private:factory/scalc"), OUString("test.ods"), 0, args ), UNO_QUERY_THROW );
      xDoc->close( sal_True );

} catch ( const com::sun::star::uno::Exception& )
{
    printf("ne mogu kreirati scalc\n");
}

printf("kreirao scalc doc\n");

}

extern "C" void calc_2()
{

    //init_lo();

/*
    m_xCalcComponent =
        getMultiServiceFactory()->createInstance("com.sun.star.comp.Calc.SpreadsheetDocument");
    CPPUNIT_ASSERT_MESSAGE("no calc component!", m_xCalcComponent.is());
*/

   printf("calc_1-1\n");
   com::sun::star::uno::Reference<com::sun::star::uno::XComponentContext> m_xContext;
   com::sun::star::uno::Reference<com::sun::star::lang::XMultiServiceFactory> m_xSFactory;

    
   printf("calc_1-2\n");
    com::sun::star::uno::Reference< com::sun::star::frame::XDesktop2 > mxDesktop;

    ::comphelper::setProcessServiceFactory(m_xSFactory);


    printf("calc_1-3\n");
    m_xContext = comphelper::getComponentContext(m_xSFactory);

   printf("calc_1-4\n");
    mxDesktop = com::sun::star::frame::Desktop::create( m_xContext );
    //CPPUNIT_ASSERT_MESSAGE("no desktop!", mxDesktop.is());


    printf("calc_1-5\n");
    //BootstrapFixture::setUp();
    ScDocShell *pDocShell;

    ScDLL::Init();
    pDocShell = new ScDocShell(
        SFXMODEL_STANDARD |
        SFXMODEL_DISABLE_EMBEDDED_SCRIPTS |
        SFXMODEL_DISABLE_DOCUMENT_RECOVERY);

    printf("calc_1-6\n");
    //ScDocument* pDoc = getDocShell().GetDocument();
    ScDocument* pDoc = pDocShell->GetDocument();

    ScAddress aPos(0,0,0);
    pDoc->SetString(aPos, "test string");

}

extern "C" int lo_main ()
{
    //long start, end;

    //start = getTimeMS();


    // shim.c
    LibLibreOffice *pOffice = lo_cpp_init( "/usr/local/lib/libreoffice/program" );
    if( !pOffice )
    {
        fprintf( stderr, "Failed to initialize\n" );
        return -1;
    }

    // This separate init is lame I think.
    if( !pOffice->initialize( "/usr/local/lib/libreoffice/program"   ) )
    {
        fprintf( stderr, "failed to initialize /usr/local/lib/libreoffice/program\n" );
        return -1;
    }

    //end = getTimeMS();
    //fprintf( stderr, "init time: %ld ms\n", (end-start) );
    //start = end;


    fprintf( stderr, "start to load document '%s'\n", "/home/bringout/test.ods" );
    LODocument *pDocument = pOffice->documentLoad(  "/home/bringout/test.ods" );
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


