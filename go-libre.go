package main

/*
  #cgo CXXFLAGS: -DOSL_DEBUG_LEVEL=1 -DSAL_LOG_INFO -DSAL_LOG_WARN  -D_DEBUG -D_GLIBCXX_DEBUG
  #cgo CFLAGS: -DOSL_DEBUG_LEVEL=1 -DSAL_LOG_INFO -DSAL_LOG_WARN  -D_DEBUG -D_GLIBCXX_DEBUG
  #cgo CXXFLAGS: -DGOLANG -DDBG_UTIL
  #cgo CXXFLAGS: -DCPPU_ENV=gcc3 -DLIBO_INTERNAL_ONLY -DLINUX -DSUPD=430 -DUNIX -DUNX -DX86_64 -D_PTHREADS -D_REENTRANT  
  #cgo CXXFLAGS: -DRTL_USING   -DSC_DLLIMPLEMENTATION  -DSYSTEM_LIBXML   -DHAVE_GCC_VISIBILITY_FEATURE 
  #cgo CXXFLAGS: -fvisibility=hidden   -Wall -Wendif-labels -Wextra -Wundef -Wunused-macros -fmessage-length=0 -fno-common -pipe  -fvisibility-inlines-hidden -fPIC -Wshadow -Woverloaded-virtual  -Wnon-virtual-dtor -std=gnu++11  -DEXCEPTIONS_ON -fexceptions -fno-enforce-eh-specs -O2
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/include
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/desktop/source/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/desktop/source/deployment/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/desktop/source/deployment/gui
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/sd/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/desktop/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/config_host
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/sc/source/core/inc -I/data/dev/libreoffice/core/sc/source/filter/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/sc/source/ui/inc -I/data/dev/libreoffice/core/sc/inc  
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/include/framework
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workDir/SdiTarget/sc/sdi
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/udkapi/normal
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/offapi/normal
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workdir/CustomTarget/officecfg/registry
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core//workdir/UnpackedTarball/mdds/include/

  #cgo LDFLAGS: -L/data/dev/libreoffice/core/workDir/LinkTarget/StaticLibrary 
  #cgo LDFLAGS: -L/data/dev/libreoffice/core/workDir/LinkTarget/Library 
  #cgo LDFLAGS: -L/usr/local/lib/libreoffice/program 
  #cgo LDFLAGS: -L/data/dev/libreoffice/core/instdir/ure/lib
  #cgo LDFLAGS: -L/data/dev/libreoffice/core/instdir/sdk/lib
  #cgo LDFLAGS: -L/usr/local/lib/harbour 
  #cgo LDFLAGS: -lpq -lharbour -lsclo -lscuilo
  #cgo LDFLAGS: -licuuc  -lxml2 
  #cgo LDFLAGS: -lavmedialo -lbasegfxlo -lcomphelper -ldrawinglayerlo -leditenglo -lforlo -lforuilo -li18nlangtag -lmsfilterlo -looxlo -lsaxlo -lsblo -lsclo -lsfxlo -lsotlo -lsvllo -lsvtlo -lsvxlo -lsvxcorelo -ltllo -ltklo -lucbhelper -lutllo -lvbahelperlo -lvcllo -lxolo
  #cgo LDFLAGS: -lsofficeapp  -lfwelo -lfwilo -lfwklo -lfwllo -lfwmlo
  #cgo LDFLAGS: -lxmlreaderlo -lxmlscriptlo
  #cgo LDFLAGS: -lvclcanvaslo -lcppcanvaslo -lcanvastoolslo
  #cgo LDFLAGS: -lvclplug_gtklo -lvclplug_svplo -ldesktop_detectorlo -ldeploymentmisclo
  #cgo LDFLAGS: -li18nutil -l:libicudata.so.52 -l:libicui18n.so.52 -l:libicuuc.so.52
  #cgo LDFLAGS: -luno_cppu -luno_cppuhelpergcc3 -lunoidllo  -luno_sal -luno_salhelpergcc3 -lbinaryurplo -lreglo -lstorelo
  #cgo LDFLAGS: -lsdlo -lsduilo -lsddlo -lsdfiltlo
  #cgo LDFLAGS: -lsblo -lsfxlo -lsotlo -lsvllo -lsvtlo -lsvxcorelo -lsvxlo -ltklo -ltllo -lucbhelper -lutllo -lvcllo -lxolo
  #cgo LDFLAGS: -lstdc++ -lm -ldl


  #cgo CFLAGS: -DGOLANG -DDBG_UTIL
  #cgo CFLAGS: -DCPPU_ENV=gcc3 -DLIBO_INTERNAL_ONLY -DLINUX -DSUPD=430 -DUNIX -DUNX -DX86_64 -D_PTHREADS -D_REENTRANT  
  #cgo CFLAGS: -DRTL_USING   -DSC_DLLIMPLEMENTATION  -DSYSTEM_LIBXML   -DHAVE_GCC_VISIBILITY_FEATURE 
 
  #cgo CFLAGS: -I/data/dev/libreoffice/core/include
  #cgo CFLAGS: -I/data/dev/libreoffice/core/desktop/source/inc
  #cgo CFLAGS: -I/data/dev/libreoffice/core//desktop/source/deployment/inc
  #cgo CFLAGS: -I/data/dev/libreoffice/core/desktop/inc
  #cgo CFLAGS: -I/data/dev/libreoffice/core/desktop/source/app
  #cgo CFLAGS: -I/data/dev/libreoffice/core/config_host
  #cgo CFLAGS: -I/data/dev/libreoffice/core/sc/source/core/inc -I/data/dev/libreoffice/core/sc/source/filter/inc
  #cgo CFLAGS: -I/data/dev/libreoffice/core/sc/source/ui/inc -I/data/dev/libreoffice/core/sc/inc  
  #cgo CFLAGS: -I/data/dev/libreoffice/core/workDir/SdiTarget/sc/sdi
  #cgo CFLAGS: -I/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/udkapi/normal
  #cgo CFLAGS: -I/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/offapi/normal
  #cgo CFLAGS: -I/data/dev/libreoffice/core/workdir/CustomTarget/officecfg/registry
  #cgo CFLAGS: -I/data/dev/libreoffice/core/include/framework


  #include "go-libre.h"
*/
import "C"

import (
  "fmt"
  "time"
)

//  $W/UnpackedTarball/liborcus/src/liborcus/.libs/liborcus-0.6.a  $W/UnpackedTarball/liborcus/src/parser/.libs/liborcus-parser-0.6.a  
func main() {

//  gtk_main("run-1");



  fmt.Println("go-libreoffice")

  fmt.Println("definisi urebootstrao varijablu kao npr URE_BOOTSTRAP=file:///usr/local/lib/libreoffice/program/fundamentalrc")

//  C.lo_main() - ucitava shared library

//    C.libre_bootstrap()

    //C.nuliraj_command_args()

//  C.calc_1()


    fmt.Println("libreoffice main desktop application")
    C.libre_main()


/*
    C.nuliraj_command_args() 
    C.app_init(C.int(1))
    //writer()
    calc()
    C.app_init(C.int(0))
*/

 
    fmt.Println("kraj priče")
    time.Sleep(1 * 1e9)


    //C.vcl_1_test()
    //C.sd_test_1()

//    gtk_main("run-2");

    fmt.Println("libreoffice main desktop application -2")
    C.libre_main()


}


func calc() {
    fmt.Println("calc")
    C.open_calc()  
}

func writer() {
    fmt.Println("writer")
    C.open_writer()
}
