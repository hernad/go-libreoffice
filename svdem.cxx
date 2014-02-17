/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#include <config_folders.h>


#include <sal/main.h>
#include <tools/extendapplicationenvironment.hxx>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include <vcl/event.hxx>
#include <vcl/svapp.hxx>
#include <vcl/wrkwin.hxx>
#include <vcl/msgbox.hxx>

#include <comphelper/processfactory.hxx>
//#include <cppuhelper/servicefactory.hxx>
#include <cppuhelper/bootstrap.hxx>


#include <cppuhelper/bootstrap.hxx>
#include <comphelper/processfactory.hxx>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ucb/XUniversalContentBroker.hpp>
#include <com/sun/star/ucb/UniversalContentBroker.hpp>

#include <vcl/svapp.hxx>
#include <tools/resmgr.hxx>
#include <vcl/graphicfilter.hxx>
#include <unotools/syslocaleoptions.hxx>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <tools/errinf.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/strbuf.hxx>
#include <rtl/bootstrap.hxx>
#include <cppuhelper/bootstrap.hxx>
#include <comphelper/processfactory.hxx>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ucb/XUniversalContentBroker.hpp>

#include <vcl/svapp.hxx>
#include <tools/resmgr.hxx>
#include <vcl/graphicfilter.hxx>
#include <unotools/syslocaleoptions.hxx>
#include <osl/mutex.hxx>


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

static uno::Reference<uno::XComponentContext> xContext;
static uno::Reference<lang::XMultiComponentFactory> xFactory;
static uno::Reference<lang::XMultiServiceFactory> xSFactory;
static uno::Reference<uno::XInterface> xDesktop;

// Forward declaration
void Main();
//void Main(uno::Reference < XDesktop2 > xDesk)

// Wonder global state ...
//static uno::Reference<css::uno::XComponentContext> xContext;
//static uno::Reference<css::lang::XMultiServiceFactory> xSFactory;
//static uno::Reference<css::lang::XMultiComponentFactory> xFactory;

static int already_started = 0;

osl::Mutex& getMutex()
{
    static osl::Mutex* pMutex = NULL;
    if( pMutex == NULL )
    {
        osl::MutexGuard aGuard( osl::Mutex::getGlobalMutex() );
        if( pMutex == NULL )  {
            printf("kreiram pMutex\n");
            static osl::Mutex aMutex;
            pMutex = &aMutex;
        }
    }
    return *pMutex;
}


extern "C" int svdem()
//SAL_IMPLEMENT_MAIN()
{
//    printf("svdem -1\n");
//    tools::extendApplicationEnvironment();


    rtl::Bootstrap::setIniFilename( "file:///opt/knowhowERP/LO/lib/libreoffice/program/fundamentalrc" );

    rtl::Bootstrap::set( "CONFIGURATION_LAYERS",
                         "xcsxcu:${BRAND_BASE_DIR}/" LIBO_SHARE_FOLDER "/registry "
                         "res:${BRAND_BASE_DIR}/" LIBO_SHARE_FOLDER "/registry "
                         );


    osl::Guard<osl::Mutex> aGuard( getMutex() );

     if (!xContext.is()) {
       xContext = cppu::defaultBootstrap_InitialComponentContext();
    }

     xFactory = xContext->getServiceManager();
     xSFactory = uno::Reference<lang::XMultiServiceFactory> (xFactory, uno::UNO_QUERY_THROW);
     comphelper::setProcessServiceFactory(xSFactory);

     ::ucb::UniversalContentBroker::create(comphelper::getProcessComponentContext() );

     
    //if (!xContext.is()) {
    //   delete &xContext;

 /*  
      xContext = cppu::defaultBootstrap_InitialComponentContext();
      fprintf( stderr, "Uno initialized %d\n", xContext.is() );

      xFactory = xContext->getServiceManager();
      xSFactory = uno::Reference<lang::XMultiServiceFactory>(xFactory, uno::UNO_QUERY_THROW);
      comphelper::setProcessServiceFactory(xSFactory);
*/
    //}

    //if (!already_started) {
/*
     OUString aLangISO( "en-US" );
     LanguageTag aLocale( aLangISO );

     ResMgr::SetDefaultLocale( aLocale );

     SvtSysLocaleOptions aLocalOptions;
     aLocalOptions.SetLocaleConfigString( aLangISO );
     aLocalOptions.SetUILocaleConfigString( aLangISO );
    //}

    xContext = ::comphelper::getProcessComponentContext();
*/

    printf("svdem before initvcl\n");
    InitVCL();

        printf("svdem -4\n");
    ::Main();
    printf("before deinitvcl\n");

    //ResMgr::DestroyAllResMgr();

    //Reference< XComponent > ::query( xSFactory )->dispose();
    //Reference< XComponent > ::query( xFactory )->dispose();
    //Reference< XComponent > ::query( xContext )->dispose();
    DeInitVCL();
    
    already_started = 1;
    return 0;
}


class MyWin : public WorkWindow
{
public:
                MyWin( Window* pParent, WinBits nWinStyle );

    void        MouseMove( const MouseEvent& rMEvt );
    void        MouseButtonDown( const MouseEvent& rMEvt );
    void        MouseButtonUp( const MouseEvent& rMEvt );
    void        KeyInput( const KeyEvent& rKEvt );
    void        KeyUp( const KeyEvent& rKEvt );
    void        Paint( const Rectangle& rRect );
    void        Resize();
};


MyWin::MyWin( Window* pParent, WinBits nWinStyle ) :
    WorkWindow( pParent, nWinStyle )
{
}


void MyWin::MouseMove( const MouseEvent& rMEvt )
{
    WorkWindow::MouseMove( rMEvt );
}


void MyWin::MouseButtonDown( const MouseEvent& rMEvt )
{
    WorkWindow::MouseButtonDown( rMEvt );
}


void MyWin::MouseButtonUp( const MouseEvent& rMEvt )
{
    WorkWindow::MouseButtonUp( rMEvt );
}


void MyWin::KeyInput( const KeyEvent& rKEvt )
{
    WorkWindow::KeyInput( rKEvt );
}


void MyWin::KeyUp( const KeyEvent& rKEvt )
{
    WorkWindow::KeyUp( rKEvt );
}


void MyWin::Paint( const Rectangle& rRect )
{
    WorkWindow::Paint( rRect );
}


void MyWin::Resize()
{
    WorkWindow::Resize();
}

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
#include <com/sun/star/task/OfficeRestartManager.hpp> 
#include <com/sun/star/task/XRestartManager.hpp> 
#include <com/sun/star/document/XEventListener.hpp> 
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

#include <svl/languageoptions.hxx>
#include <svtools/javacontext.hxx>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/SessionListener.hpp>
#include <com/sun/star/frame/XSessionManagerListener.hpp>
#include <com/sun/star/frame/XSynchronousDispatch.hpp>
#include <com/sun/star/document/CorruptedFilterConfigurationException.hpp>
#include <com/sun/star/configuration/CorruptedConfigurationException.hpp>
#include <com/sun/star/configuration/theDefaultProvider.hpp>
#include <com/sun/star/util/XFlushable.hpp>
#include <com/sun/star/system/SystemShellExecuteFlags.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/StartModule.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/view/XPrintable.hpp>
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
#include <com/sun/star/task/OfficeRestartManager.hpp>



//using namespace ::com::sun::star;

//using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::uno;
//using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::task;
//using namespace ::com::sun::star::ui;
//using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::container;

using namespace ::com::sun::star::uno;
//using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::task;
//using namespace ::com::sun::star::ui;
//using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::container;


/*
using namespace ::rtl;
using namespace ::osl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
*/

namespace css = com::sun::star;

void show_license();

void Main()
{

    
    MyWin aMainWin( NULL, WB_APP | WB_STDWORK );
    aMainWin.SetText(OUString("VCL demo window"));
    aMainWin.Show();
    //Sequence < com::sun::star::beans::PropertyValue > args(0);

    show_license();
    //if (xDesktop.is()) {
            //} else {
   //    uno::Reference < XDesktop2 > xDesktop;
   //    xDesktop = css::frame::Desktop::create( xContext );
    
   //    OUString aURL( "file:///home/bringout/test.ods" );
   //    Reference < css::util::XCloseable > xComponent( xDesktop->loadComponentFromURL( aURL, "_blank", 0, args ), UNO_QUERY_THROW );




   //}


    //   printf("><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< already_started = 1\n");
    //   already_started = 1;



    Application::Execute();

    //Reference< XComponent > ::query( xDesktop )->dispose();

    //if (xDesktop.is()) {
       //printf("before xDesktop terminate\n");
       //delete &xDesktop;
       //printf("AFTER xDesktop terminate\n");
       //xDesktop->terminate();
    //}

    //xDesktop->terminate();
}

/*
using namespace ::com::sun::star;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::system;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::document;
*/

/// Find the correct location of the document (LICENSE.fodt, etc.), and return
/// it in rURL if found.
static sal_Bool checkURL( const char *pName, const char *pExt, OUString &rURL )
{
    using namespace osl;
    DirectoryItem aDirItem;

    rURL = "$BRAND_BASE_DIR/" + OUString::createFromAscii( pName ) +
           OUString::createFromAscii( pExt );
    rtl::Bootstrap::expandMacros( rURL );

    if (!rURL.isEmpty())
        return DirectoryItem::get( rURL, aDirItem ) == DirectoryItem::E_None;
    else
        return sal_False;
}

using namespace ::com::sun::star;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::system;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::document;

/// Displays CREDITS or LICENSE in any of the available version
static void showDocument( const char* pBaseName )
{
    //try {


static uno::Reference<frame::XComponentLoader> xLoader;
static uno::Reference<lang::XComponent> xComponent;


        osl::Guard<osl::Mutex> aGuard( getMutex() );
xDesktop = xFactory->createInstanceWithContext(OUString("com.sun.star.frame.Desktop"), xContext);
xLoader = frame::Desktop::create(xContext);


//        Reference < XDesktop2 > xDesktop = Desktop::create( ::comphelper::getProcessComponentContext() );
        Sequence < com::sun::star::beans::PropertyValue > args(2);
        args[0].Name = "ViewOnly";
        args[0].Value <<= sal_True;
        args[1].Name = "ReadOnly";
        args[1].Value <<= sal_True;

        OUString aURL;
        if ( checkURL ( pBaseName, ".fodt", aURL ) ||
             checkURL ( pBaseName, ".html", aURL ) ||
             checkURL ( pBaseName, "", aURL ) ) {



             xComponent.set(xLoader->loadComponentFromURL(aURL, OUString("_blank"), 0, args));

             if (xComponent.get()) {
                 printf("URL load uspjesan valjda\n");
             } else
                 printf("URL load neuspjesan\n");
             
              xComponent->dispose();
              xComponent.clear();

        }
    //} catch (const ::com::sun::star::uno::Exception &) {
    //       printf("negdje imamo exception !\n");
    //}

}

#include <toolkit/helper/vclunohelper.hxx>

//#include <vcl/button.hxx>
//#include <vcl/dialog.hxx>
//#include <vcl/lstbox.hxx>

//namespace
//{
    class LicenseDialog : public ModalDialog
    {
    private:
        //DECL_LINK(ShowHdl, void *);
    public:
        LicenseDialog(Window *pParent=NULL);
    };

    LicenseDialog::LicenseDialog(Window *pParent)
        : ModalDialog(pParent, "LicenseDialog", "sfx/ui/licensedialog.ui")
    {
        //get<PushButton>("show")->SetClickHdl(LINK(this, LicenseDialog, ShowHdl));
    }

/*
    IMPL_LINK_NOARG(LicenseDialog, ShowHdl)
    {
        EndDialog(RET_OK);
        showDocument("LICENSE");
        return 0;
    }
*/

//}


void show_license() {

  printf("show_license\n");
  LicenseDialog aDialog;
  //aDialog.Show(sal_True);
  aDialog.Execute(); 

  showDocument("LICENSE");
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
