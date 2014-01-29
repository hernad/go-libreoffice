package main

/*

  #cgo CXXFLAGS: -DCPPU_ENV=gcc3 -DLIBO_INTERNAL_ONLY -DLINUX -DNDEBUG -DOPTIMIZE -DOSL_DEBUG_LEVEL=0 -DSUPD=430 -DUNIX -DUNX -DX86_64 -D_PTHREADS -D_REENTRANT  
  #cgo CXXFLAGS: -DRTL_USING   -DSC_DLLIMPLEMENTATION  -DSYSTEM_LIBXML   -DHAVE_GCC_VISIBILITY_FEATURE 
  #cgo CXXFLAGS: -fvisibility=hidden   -Wall -Wendif-labels -Wextra -Wundef -Wunused-macros -fmessage-length=0 -fno-common -pipe  -fvisibility-inlines-hidden -fPIC -Wshadow -Woverloaded-virtual  -Wnon-virtual-dtor -std=gnu++11  -DEXCEPTIONS_ON -fexceptions -fno-enforce-eh-specs -O2
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/include
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/desktop/source/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core//desktop/source/deployment/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/desktop/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/config_host
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/sc/source/core/inc -I/data/dev/libreoffice/core/sc/source/filter/inc
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/sc/source/ui/inc -I/data/dev/libreoffice/core/sc/inc  
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workDir/SdiTarget/sc/sdi
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/udkapi/normal
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workdir/UnoApiHeadersTarget/offapi/normal
  #cgo CXXFLAGS: -I/data/dev/libreoffice/core/workdir/CustomTarget/officecfg/registry

  #cgo LDFLAGS: -L/data/dev/libreoffice/core/workDir/LinkTarget/StaticLibrary 
  #cgo LDFLAGS: -L/data/dev/libreoffice/core/workDir/LinkTarget/Library 
  #cgo LDFLAGS: -L/usr/local/lib/libreoffice/program 
  #cgo LDFLAGS: -L/data/dev/libreoffice/core/instdir/ure/lib
  #cgo LDFLAGS: -L/data/dev/libreoffice/core/instdir/sdk/lib
  #cgo LDFLAGS: -L/usr/local/lib/harbour 
  #cgo LDFLAGS: -lpq -lharbour -lsclo -lscuilo
  #cgo LDFLAGS: -licuuc  -lxml2 
  #cgo LDFLAGS: -lavmedialo -lbasegfxlo -lcomphelper -luno_cppu -luno_cppuhelpergcc3 -ldrawinglayerlo -leditenglo -lforlo -lforuilo -li18nlangtag -lmsfilterlo -looxlo -luno_sal -luno_salhelpergcc3 -lsaxlo -lsblo -lsclo -lsfxlo -lsotlo -lsvllo -lsvtlo -lsvxlo -lsvxcorelo -ltllo -ltklo -lucbhelper -lutllo -lvbahelperlo -lvcllo -lxolo

*/
import "C"


//  $W/UnpackedTarball/liborcus/src/liborcus/.libs/liborcus-0.6.a  $W/UnpackedTarball/liborcus/src/parser/.libs/liborcus-parser-0.6.a  
func main() {
  fmt.Println("go-libreoffice")
  //C.soffice_main()
}
