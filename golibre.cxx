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
#include "vcl/lazydelete.hxx"

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
//#include <com/sun/star/task/theJobExecutor.hpp> 
#include <com/sun/star/task/OfficeRestartManager.hpp> 
#include <com/sun/star/task/XRestartManager.hpp> 
#include <com/sun/star/document/XEventListener.hpp> 
//#include <com/sun/star/frame/theUICommandDescription.hpp> 
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
//#include <com/sun/star/frame/theAutoRecovery.hpp>
//#include <com/sun/star/frame/theGlobalEventBroadcaster.hpp>
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

#include <toolkit/helper/vclunohelper.hxx>
#include <comphelper/configuration.hxx>
#include <comphelper/processfactory.hxx>
#include <unotools/bootstrap.hxx>
#include <unotools/configmgr.hxx>
#include <unotools/moduleoptions.hxx>
#include <officecfg/Office/Common.hxx>
#include <officecfg/Office/Recovery.hxx>
#include <officecfg/Setup.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/uri.hxx>
#include <unotools/pathoptions.hxx>
#include <svtools/miscopt.hxx>
#include <svtools/menuoptions.hxx>
#include <rtl/bootstrap.hxx>
#include <vcl/help.hxx>
#include <vcl/msgbox.hxx>
#include <sfx2/sfx.hrc>
#include <sfx2/app.hxx>


#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h> 

#include "golibre.hxx"

#include "dp_gui_shared.hxx"
#include "dp_gui.h"
#include "dp_gui_theextmgr.hxx"
#include "cppuhelper/implbase2.hxx"
#include "cppuhelper/implementationentry.hxx"
#include "unotools/configmgr.hxx"
#include "comphelper/processfactory.hxx"
#include "comphelper/servicedecl.hxx"
#include "comphelper/unwrapargs.hxx"
#include <i18nlangtag/languagetag.hxx>
#include "vcl/svapp.hxx"
#include "vcl/msgbox.hxx"
#include "com/sun/star/lang/XServiceInfo.hpp"
//#include "com/sun/star/task/XJobExecutor.hpp"
#include "com/sun/star/ui/dialogs/XAsynchronousExecutableDialog.hpp"

#include <boost/optional.hpp>
#include <boost/utility.hpp>
#include "license_dialog.hxx"
#include "dp_gui_dialog2.hxx"
#include "dp_gui_extensioncmdqueue.hxx"

#include "vcl/svapp.hxx"
#include "vcl/msgbox.hxx"

#include "vcl/svapp.hxx"
#include <svdata.hxx>
#include "vcl/window.hxx"
#include "vcl/timer.hxx"
#include "vcl/solarmutex.hxx"


using namespace ::dp_misc;

//#include <sofficemain.h>

class MyApp : public Application, private boost::noncopyable
{
public:
    MyApp();
    virtual ~MyApp();

    // Application
    virtual int Main();
    virtual void DeInit();
    virtual void Execute2();
    virtual void Yield2();
    virtual void Macro();
    virtual sal_Bool  QueryExit();

};

//______________________________________________________________________________
MyApp::~MyApp()
{
   printf("MyApp destruktor .......................!!!!!!!!!!!!!!!!!!................!\n");

/*
    ImplDeInitSVData();
    //DeInitSalData();
    ImplGetSVData()->mpApp = NULL;
    ImplDestroySVData();
    //GlobalDeInitTools();
*/

}

sal_Bool MyApp::QueryExit() {
   
    printf("MyApp QUERYEXITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT .......................!!!!!!!!!!!!!!!!!!................!\n");

    this->ShowNativeErrorBox(OUString("nema izlaska"), OUString("x2222222"));
    return sal_True;

}

//______________________________________________________________________________
MyApp::MyApp()
{
   printf("MyApp konstruktor .......................!!!!!!!!!!!!!!!!!!................!\n");
}

//______________________________________________________________________________
int MyApp::Main()
{
    return EXIT_SUCCESS;
}

void MyApp::DeInit()
{
   printf("FAKE MyApp Deinit .......................!!!!!!!!!!!!!!!!!!................!\n");
   return;

   printf("MyApp Deinit .......................!!!!!!!!!!!!!!!!!!................!\n");

    css::uno::Reference< css::uno::XComponentContext > context(
        comphelper::getProcessComponentContext());
    dp_misc::disposeBridges(context);
    css::uno::Reference< css::lang::XComponent >(
        context, css::uno::UNO_QUERY_THROW)->dispose();
    comphelper::setProcessServiceFactory(0);
   printf("MyApp Deinit kraj.......................!!!!!!!!!!!!!!!!!!................!\n");

}
void MyApp::Execute2()
{
       printf(">>>>>>>>>>>>>>>>>> MyApp Execute ...........................--------------------------\n");

       printf("Execute2-1\n");
       ImplSVData* pSVData = ImplGetSVData();
printf("Execute2-2\n");

       pSVData->maAppData.mbInAppExecute = sal_True;


/*

#define DECL_LINK( Method, ArgType ) \
    long Method( ArgType ); \
    static long LinkStub##Method( void* pThis, void* )

#define LINK( Inst, Class, Member ) \
    Link( (Class*)Inst, (PSTUB)&Class::LinkStub##Member )

#define STATIC_LINK( Inst, Class, Member ) \
    Link( (Class*)Inst, (PSTUB)&Class::Member )


svapp.cxx ima:
IMPL_STATIC_LINK_NOINSTANCE( ImplSVAppData, ImplQuitMsg, void*, EMPTYARG )
{
    ImplGetSVData()->maAppData.mbAppQuit = sal_True;
    return 0;
}

void Application::Quit()
{
    printf("FAKE !!!!!!!!!!!!!!!!!!!!!!!!!!11Application quit\n");
    //Application::PostUserEvent( STATIC_LINK( NULL, ImplSVAppData, ImplQuitMsg ) );
}

stvar se dešava u PostEvent
unx/gtk/window/gtksalframe.cxx

a on delegeira 

SalSession
SessionManager-u (sm.cxx)

SessionManagerClient


#define LINK( Inst, Class, Member ) \
    Link( (Class*)Inst, (PSTUB)&Class::LinkStub##Member )

SalGenericDisplay::SendInternalEvent (this=0x102a000, pFrame=0x12c2a20, pData=0x1293b00, nEvent=22)
    at /data/dev/libreoffice/core/vcl/generic/app/gendisp.cxx:100

gtkdata.cxx	    GetGtkSalData()->PostUserEvent();

GtkSalFrame::PostEvent

SfxTerminateListener_Impl::notifyTermination

/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/offapi/normal/com/sun/star/document/EventObject.hdl

SfxTerminateListener_Impl::notifyTermination (this=0x7fffd91bdb48, aEvent=...)
    at /data/dev/libreoffice/core/sfx2/source/appl/appinit.cxx:115
115	    css::uno::Reference< css::document::XEventListener > xGlobalBroadcaster(css::frame::GlobalEventBroadcaster::create(xContext), css::uno::UNO_QUERY_THROW);


SfxTerminateListener_Impl::notifyTermination (this=0x7fffd91bdb48, aEvent=...)
    at /data/dev/libreoffice/core/sfx2/source/appl/appinit.cxx:106
106	    SolarMutexGuard aGuard;
(gdb) s
SolarMutexGuard::~SolarMutexGuard (this=0x7fffffffd280, __in_chrg=<optimized out>)
    at /data/dev/libreoffice/core/include/vcl/svapp.hxx:431
431	        m_solarMutex.release();
(gdb) s
GtkYieldMutex::release (this=0xfe5fd0) at /data/dev/libreoffice/core/vcl/unx/gtk/app/gtkinst.cxx:307
307	    SalYieldMutex::release();
(gdb) s
SalYieldMutex::release (this=0xfe5fd0) at /data/dev/libreoffice/core/vcl/generic/app/geninst.cxx:56
56	    OSL_ENSURE(mnCount > 0, "SalYieldMutex::release() called with zero count");
(gdb) s
57	    if ( mnThreadId == osl::Thread::getCurrentIdentifier() )
(gdb) s
osl::Thread::getCurrentIdentifier () at /data/dev/libreoffice/core/include/osl/thread.hxx:140
140	        return osl_getThreadIdentifier(0);
(gdb) s
osl_getThreadIdentifier (Thread=0x0) at /data/dev/libreoffice/core/sal/osl/unx/thread.c:641
641	    Thread_Impl* pImpl= (Thread_Impl*)Thread


....


vcl::SolarMutexObject::release (this=0xfe5fd0) at /data/dev/libreoffice/core/vcl/source/app/solarmutex.cxx:46
46	}
(gdb) s
SalYieldMutex::release (this=0xfe5fd0) at /data/dev/libreoffice/core/vcl/generic/app/geninst.cxx:64
64	}
(gdb) s
GtkYieldMutex::release (this=0xfe5fd0) at /data/dev/libreoffice/core/vcl/unx/gtk/app/gtkinst.cxx:308
308	}


    at /data/dev/libreoffice/core/sfx2/source/appl/appinit.cxx:122
122	    Application::Quit();
(gdb) list
117	    css::document::EventObject aEvent2;
118	    aEvent2.EventName = "OnCloseApp";
119	    xGlobalBroadcaster->notifyEvent(aEvent2);
120	
121	    delete pApp;
122	    Application::Quit();
123	}

*/

//printf("Application::Quit obara GOLANG app\n");

pSVData->maAppData.mbAppQuit = sal_False;

printf("Execute2-3\n");
       //int exei = 0;
       while ( !pSVData->maAppData.mbAppQuit ) {
             //printf("Execute2-4 %d\n", exei);
             this->Yield2();
             //exei--;
             //if (exei < 0)
             //     break;
       }
printf("Execute2-5\n");
       pSVData->maAppData.mbInAppExecute = sal_False;

}

#include <sal/types.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/plugin/TestPlugIn.h>
#include <test/bootstrapfixture.hxx>
#include <basic/sbstar.hxx>
#include <basic/basrdll.hxx>
#include <basic/sbmod.hxx>
#include <basic/sbmeth.hxx>
#include <basic/basrdll.hxx>
#include <basic/sbuno.hxx>
#include <osl/file.hxx>

class MacroSnippet
{
    private:
    bool mbError;
    SbModuleRef mpMod;
    StarBASICRef mpBasic;

    void InitSnippet()
    {
        //CPPUNIT_ASSERT_MESSAGE( "No resource manager", basicDLL().GetBasResMgr() != NULL );
        mpBasic = new StarBASIC();
        StarBASIC::SetGlobalErrorHdl( LINK( this, MacroSnippet, BasicErrorHdl ) );
    }
    void MakeModule( const OUString& sSource )
    {
        mpMod = mpBasic->MakeModule( OUString( "TestModule" ), sSource );
    }
    public:
    struct ErrorDetail
    {
        OUString sErrorText;
        int nLine;
        int nCol;
        ErrorDetail() : nLine(0), nCol(0) {}
    };

    MacroSnippet( const OUString& sSource ) : mbError(false)
    {
        InitSnippet();
        MakeModule( sSource );
    };
    MacroSnippet() : mbError(false)
    {
        InitSnippet();
    };
    void LoadSourceFromFile( const OUString& sMacroFileURL )
    {
        OUString sSource;
        fprintf(stderr,"loadSource opening macro file %s\n", OUStringToOString( sMacroFileURL, RTL_TEXTENCODING_UTF8 ).getStr() );

        osl::File aFile(sMacroFileURL);
        if(osl::FileBase::E_None == aFile.open(osl_File_OpenFlag_Read))
        {
            sal_uInt64 size;
            sal_uInt64 size_read;
            if(osl::FileBase::E_None == aFile.getSize(size))
            {
                void* buffer = calloc(1, size+1);
                CPPUNIT_ASSERT(buffer);
                if(osl::FileBase::E_None == aFile.read( buffer, size, size_read))
                {
                    if(size == size_read)
                    {
                        OUString sCode((sal_Char*)buffer, size, RTL_TEXTENCODING_UTF8);
                        sSource = sCode;
                    }
                }
            }
        }
        //CPPUNIT_ASSERT_MESSAGE( "Source is empty", ( sSource.getLength() > 0 ) );
        MakeModule( sSource );
    }

    SbxVariableRef Run( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& rArgs )
    {
        SbxVariableRef pReturn = NULL;
        if ( !Compile() )
            return pReturn;
        SbMethod* pMeth = mpMod ? static_cast<SbMethod*>(mpMod->Find( OUString("doMain"),  SbxCLASS_METHOD )) : NULL;
        if ( pMeth )
        {
            if ( rArgs.getLength() )
            {
                SbxArrayRef aArgs = new SbxArray;
                for ( int i=0; i < rArgs.getLength(); ++i )
                {
                    SbxVariable* pVar = new SbxVariable();
                    unoToSbxValue( pVar, rArgs[ i ] );
                    aArgs->Put(  pVar, i + 1 );
                }
                pMeth->SetParameters( aArgs );
            }
            pReturn = new SbxMethod( *((SbxMethod*)pMeth));
        }
        return pReturn;
    }

    SbxVariableRef Run()
    {
        ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any > aArgs;
        return Run( aArgs );
    }

    bool Compile()
    {
        //CPPUNIT_ASSERT_MESSAGE("module is NULL", mpMod != NULL );
        mpMod->Compile();
        return !mbError;
    }

    DECL_LINK( BasicErrorHdl, StarBASIC * );

    ErrorDetail GetError()
    {
        ErrorDetail aErr;
        aErr.sErrorText = StarBASIC::GetErrorText();
        aErr.nLine = StarBASIC::GetLine();
        aErr.nCol = StarBASIC::GetCol1();
        return aErr;
    }

    bool HasError() { return mbError; }

    void ResetError()
    {
        StarBASIC::SetGlobalErrorHdl( Link() );
        mbError = false;
    }

    BasicDLL& basicDLL()
    {
        static BasicDLL maDll; // we need a dll instance for resouce manager etc.
        return maDll;
    }
};

IMPL_LINK( MacroSnippet, BasicErrorHdl, StarBASIC *, /*pBasic*/)
{
    fprintf(stderr,"(%d:%d)\n",
            StarBASIC::GetLine(), StarBASIC::GetCol1());
    fprintf(stderr,"Basic error: %s\n", OUStringToOString( StarBASIC::GetErrorText(), RTL_TEXTENCODING_UTF8 ).getStr() );
    mbError = true;
    return 0;
}

void MyApp::Macro() {

/*
OUString sTestEnableRuntime(
    "Function doUnitTest as Integer\n"
    "Dim Enable as Integer\n"
    "Enable = 1\n"
    "Enable = Enable + 2\n"
    "doUnitTest = Enable\n"
    "End Function\n"
    "MsgBox(\"Helo from Starbasic\")\n"
);
*/

//"MsgBox  'This is a message about ...'\n"
OUString sTestEnableRuntime(
   "Function doMain'\n"
   "Dim mNoArgs()\n"
   "Dim Enable as Integer\n"
   "Dim oDocument as Object\n"
   "Dim oDesktop as Object\n"
   "Dim sUrl as String\n"
   //"MsgBox \"ok\", 64, \"Arr\"\n"
   "sUrl = \"file:///home/bringout/test.ods\"\n"
   "oDesktop  = createUnoService(\"com.sun.star.frame.Desktop\")\n"
   "oDocument = oDesktop.LoadComponentFromURL(sUrl,\"_blank\",0,mNoArgs())\n"
   "Enable= 1\n"
   "doMain = 1\n"
   "End Function\n"
);


MacroSnippet myMacro(sTestEnableRuntime);
myMacro.Compile();
//CPPUNIT_ASSERT_MESSAGE("testEnableRuntime fails with compile error",!myMacro.HasError() );
SbxVariableRef pNew = myMacro.Run();



}

#include "salinst.hxx"

inline void ImplYield( bool i_bWait, bool i_bAllEvents )
{
ImplSVData* pSVData = ImplGetSVData();

// run timers that have timed out
if ( !pSVData->mbNoCallTimer )
   while ( pSVData->mbNotAllTimerCalled )

   Timer::ImplTimerCallbackProc();

    pSVData->maAppData.mnDispatchLevel++;
// do not wait for events if application was already quit; in that
// case only dispatch events already available
// do not wait for events either if the app decided that it is too busy for timers
// (feature added for the slideshow)


    pSVData->mpDefInst->Yield( i_bWait && !pSVData->maAppData.mbAppQuit && !pSVData->maAppData.mbNoYield, i_bAllEvents );
     pSVData->maAppData.mnDispatchLevel--;

//DBG_TESTSOLARMUTEX(); // must be locked on return from Yield

// flush lazy deleted objects
    if( pSVData->maAppData.mnDispatchLevel == 0 )
          vcl::LazyDelete::flush();

// the system timer events will not necessarily come in in non waiting mode
// e.g. on OS X; need to trigger timer checks manually
     if( pSVData->maAppData.mbNoYield && !pSVData->mbNoCallTimer )
     {
        do
           {
              Timer::ImplTimerCallbackProc();
           }
       while( pSVData->mbNotAllTimerCalled );
     }

    //printf("FAKE YieldPostListeners\n");
    // call post yield listeners
    if( pSVData->maAppData.mpPostYieldListeners )
      pSVData->maAppData.mpPostYieldListeners->callListeners( NULL );
    


     
}

void MyApp::Yield2()
{
     ImplYield( true, false );
}


static int already_started = 0;
static GoLibreOffice *pOffice;
static MyApp *app;

extern "C" int lo_liblib_demo ()
{

   


if (already_started == 0) {

    //::std::auto_ptr<Application> app;
    app = new MyApp; 
    //app->reset();
    app->Init();

    pOffice = lo_cpp_init_g( "/opt/knowhowERP/LO/lib/libreoffice/program" );

    
   app->SetDisplayName( OUString(" XXX"));
   //app->SetDisplayName( utl::ConfigManager::getProductName() + OUString(" XXX"));
/*
    AllSettings as = app->GetSettings();
    as.SetUILanguageTag( LanguageTag( utl::ConfigManager::getLocale() ).makeFallback() );
    app->SetSettings( as );
    app->SetDisplayName(
                utl::ConfigManager::getProductName() +
                OUString(" ") +
                utl::ConfigManager::getProductVersion());
    ExtensionCmdQueue::syncRepositories( m_xComponentContext );
*/

    if( !pOffice )
    {
        fprintf( stderr, "inicijalizacija neuspjesna\n" );
        return -1;
    } else
        fprintf( stdout, "inicijalizacija ok\n");
 

    // This separate init is lame I think.
    if( !pOffice->initialize( "/opt/knowhowERP/LO/lib/libreoffice/program" ) )
    {
        fprintf( stderr, "failed to init program\n" );
        return -1;
    }

}

/*
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

*/
//if (!already_started)
    //app->ShowNativeErrorBox(OUString("star app"), OUString("x2222222"));

    app->Macro();

    app->Execute2();
    app->DeInit();


/*

svdata.hxx:

struct ImplSVData
    305 {
    306     SalData*                mpSalData;
    307     SalInstance*            mpDefInst;          // Default SalInstance
    308     Application*            mpApp;              // pApp
    309     WorkWindow*             mpDefaultWin;       // Default-Window
    310     sal_Bool                    mbDeInit;             // Is VCL deinitializing
    311     sal_uLong                   mnThreadCount;      // is VCL MultiThread enabled
    312     ImplConfigData*         mpFirstConfigData;  // Zeiger auf ersten Config-Block
    313     ImplTimerData*          mpFirstTimerData;   // list of all running timers
    314     SalTimer*               mpSalTimer;         // interface to sal event loop/timers
    315     SalI18NImeStatus*       mpImeStatus;        // interface to ime status window
    316     SalSystem*              mpSalSystem;        // SalSystem interface
    317     ResMgr*                 mpResMgr;           // SV-Resource-Manager
    318     sal_uLong                   mnTimerPeriod;      // current timer period
    319     sal_uLong                   mnTimerUpdate;      // TimerCallbackProcs on stack
    320     sal_Bool                    mbNotAllTimerCalled;// sal_True: Es muessen noch Timer abgearbeitet werden
    321     sal_Bool                    mbNoCallTimer;      // sal_True: No Timeout calls
    322     ImplSVAppData           maAppData;          // indepen data for class Application
    323     ImplSVGDIData           maGDIData;          // indepen data for Output classes
    324     ImplSVWinData           maWinData;          // indepen data for Windows classes
    325     ImplSVCtrlData          maCtrlData;         // indepen data for Control classes
    326     ImplSVHelpData          maHelpData;         // indepen data for Help classes
    327     ImplSVNWFData           maNWFData;
    328     UnoWrapperBase*         mpUnoWrapper;
    329     Window*                 mpIntroWindow;      // the splash screen
    330     DockingManager*         mpDockingManager;
    331     BlendFrameCache*        mpBlendFrameCache;
    332     sal_Bool                mbIsTestTool;
    333 
    334     oslThreadIdentifier                     mnMainThreadId;
    335     rtl::Reference< vcl::DisplayConnection >            mxDisplayConnection;
    336 
    337     ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > mxAccessBridge;
    338     ::vcl::SettingsConfigItem*          mpSettingsConfigItem;
    339     std::list< vcl::DeleteOnDeinitBase* >*   mpDeinitDeleteList;
    340     boost::unordered_map< int, OUString >*     mpPaperNames;
    341 };
    342 



    Map: A window has been mapped. (It is now visible on the screen).
    *   Unmap: A window has been unmapped. (It is no longer visible on
    *	    the screen).

*/
    
//    delete pDocument;
//    delete pOffice;

    already_started = 1;
    //delete app;
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


/*
using namespace ::rtl;
using namespace ::osl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
*/

namespace css = com::sun::star;


#include <com/sun/star/sheet/XDimensionsSupplier.hpp>
#include <com/sun/star/sheet/DataResult.hpp>
#include <com/sun/star/sheet/MemberResult.hpp>
#include <com/sun/star/sheet/GeneralFunction.hpp>
#include <com/sun/star/sheet/DataPilotOutputRangeType.hpp>

#include "global.hxx"
#include "address.hxx"

#include "dpfilteredcache.hxx"
#include "dptypes.hxx"

#include <vector>

#include <docsh.hxx>


#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextField.hpp>
#include <com/sun/star/text/XTextFieldsSupplier.hpp>
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>

namespace {

uno::Reference<text::XTextField> getNewField(const uno::Reference<lang::XMultiServiceFactory>& xSM, int num)
{

    //char str[15];
    //sprintf(str, "LibreOffice %d", num);

    uno::Reference<text::XTextField> xField(
        xSM->createInstance("com.sun.star.text.TextField.URL"), UNO_QUERY_THROW);
    uno::Reference<beans::XPropertySet> xPropSet(xField, UNO_QUERY_THROW);
    xPropSet->setPropertyValue("Representation", uno::makeAny(OUString("libreoffice ") + OUString::number(num)));
    xPropSet->setPropertyValue("URL", uno::makeAny(OUString("http://www.libreoffice.org/")));
    return xField;
}

}

static Reference < XDesktop2 > xDesktop;

extern "C" void open_calc() 
{

Sequence < com::sun::star::beans::PropertyValue > args(0);

Reference< XComponentContext > xContext = ::comphelper::getProcessComponentContext();

//OUString aURL =  OUString("private:factory/scalc");

OUString aURL = getAbsoluteURL( "/home/bringout/test.ods" );
      
xDesktop = css::frame::Desktop::create( xContext );


Reference < css::util::XCloseable > xComponent( xDesktop->loadComponentFromURL( aURL, "_blank", 0, args ), UNO_QUERY_THROW );


uno::Reference<sheet::XSpreadsheetDocument> xDoc(xComponent, UNO_QUERY_THROW);

Reference< container::XIndexAccess > xIndex (xDoc->getSheets(), UNO_QUERY_THROW);
uno::Reference< sheet::XSpreadsheet > xSheet( xIndex->getByIndex(0), UNO_QUERY_THROW);

uno::Reference<lang::XMultiServiceFactory> xSM(xComponent, UNO_QUERY_THROW);

for (int i=0;  i < 20; i++) {
	uno::Reference<table::XCell> xCell = xSheet->getCellByPosition(0, i);
	uno::Reference<text::XText> xText(xCell, UNO_QUERY_THROW);
	uno::Reference<text::XTextCursor> xCursor = xText->createTextCursor();
	uno::Reference<text::XTextRange> xRange(xCursor, UNO_QUERY_THROW);


        // Create a new URL field object, and populate it with name and URL.
        uno::Reference<text::XTextField> xField = getNewField(xSM, i);


	// definisemo content objekat kreiran od xField-a
	uno::Reference<text::XTextContent> xContent(xField, UNO_QUERY_THROW);

	// content ubacujemo u gore definisani range
	xText->insertTextContent(xRange, xContent, sal_False);

        printf("Ubacujem field: %d\n", i);
}


//ScDocShellRef xDocSh = loadDoc("/home/bringout/test", ODS);
//ScDocShell& getDocShell();

/*
try {

       //xDoc->close( sal_False );

} catch ( const css::uno::Exception& )
{
    printf("ne mogu kreirati scalc\n");
}
*/


/*
Reference< css::frame::XFrame > xTask = xDesktop->getActiveFrame();
if ( !xTask.is() )
{
      printf("xTask 0\n");
       // get any task if there is no active one
      Reference< css::container::XIndexAccess > xList( xDesktop->getFrames(), ::com::sun::star::uno::UNO_QUERY );
      if ( xList->getCount() > 0 )
      xList->getByIndex(0) >>= xTask;
}

if ( xTask.is() )
{
        printf("xTask 1\n");
        Reference< com::sun::star::awt::XTopWindow > xTop( xTask->getContainerWindow(), UNO_QUERY );
        xTop->toFront();
}


Reference< ::com::sun::star::awt::XWindow > xContainerWindow;
Reference< XFrame > xBackingFrame = xDesktop->findFrame(OUString( "_blank" ), 0);
if (xBackingFrame.is()) {
          printf("nasao _blank frame\n");
          xContainerWindow = xBackingFrame->getContainerWindow();
}

if (xContainerWindow.is())
{
                    css::uno::Reference< css::uno::XComponentContext > xContext = ::comphelper::getProcessComponentContext();

                    Reference< XController > xStartModule = StartModule::createWithParentWindow(xContext, xContainerWindow);
                    Reference< ::com::sun::star::awt::XWindow > xBackingWin(xStartModule, UNO_QUERY);
                    // Attention: You MUST(!) call setComponent() before you call attachFrame().
                    // Because the backing component set the property "IsBackingMode" of the frame
                    // to true inside attachFrame(). But setComponent() reset this state every time ...
                    xBackingFrame->setComponent(xBackingWin, xStartModule);
                    xStartModule->attachFrame(xBackingFrame);
                    xContainerWindow->setVisible(sal_True);

                    Window* pCompWindow = VCLUnoHelper::GetWindow(xBackingFrame->getComponentWindow());
                    if (pCompWindow)
                        pCompWindow->Update();

}
*/

//Application::Execute();
//Application::Abort(OUString("calc kkkkkkkkkkkkkkkraj"));

/*
DeInitVCL();

css::uno::Reference< css::uno::XComponentContext > context(comphelper::getProcessComponentContext());
dp_misc::disposeBridges(context);
css::uno::Reference< css::lang::XComponent >(context, css::uno::UNO_QUERY_THROW)->dispose();
comphelper::setProcessServiceFactory(0);
*/

}


extern "C" void close_desktop() {

printf("xDesktop terminate!\n");
xDesktop->terminate();

}


extern "C" void open_writer() 
{


Sequence < com::sun::star::beans::PropertyValue > args(0);

xDesktop = css::frame::Desktop::create( ::comphelper::getProcessComponentContext() );

//OUString aURL =  OUString("private:factory/writer");

OUString aURL = getAbsoluteURL( "/home/bringout/test.odt" );
try {

       Reference < css::util::XCloseable > xDoc( xDesktop->loadComponentFromURL( aURL, "_blank", 0, args ), UNO_QUERY );
       //xDoc->close( sal_False );

} catch ( const css::uno::Exception& )
{
    printf("ne mogu kreirati swriter\n");
}


/*
Application::Execute();
DeInitVCL();
//Application::Abort(OUString("kkkkkkkkkkkkkkkraj"));
*/

}


extern "C" void nuliraj_command_args()
{
  //char * argv[] = { strdup("go-libre"), strdup("scalc")};
  char * argv[] = { strdup("go-libreoffice")};

  osl_setCommandArgs (1, argv);
  return;
}

