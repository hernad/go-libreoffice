// Basic Layout Example
// http://qt-project.org/doc/qt-5.1/qtquickcontrols/basiclayouts.html

package main

import (
	"fmt"
	"github.com/niemeyer/qml"
	"os"
)

func main() {
	qml.Init(nil)
	engine := qml.NewEngine()
	engine.On("quit", func() {
		fmt.Println("quit")
		os.Exit(0) 
	})
	
	
	component, err := engine.LoadFile("basiclayout.qml")
	if err != nil {
		fmt.Println(err)
		return
	}

        ctrl := Control{Polje1: "Hello from Go!",  Polje2: "tekst2"}
	context := engine.Context()
	context.SetVar("ctrl", &ctrl)

	window := component.CreateWindow(nil)
	ctrl.Root = window.Root()
	
	window.Show()
	window.Wait()
}

type Control struct {
        Root    qml.Object
        Polje1 string
        Polje2 string
}

func (ctrl *Control) ChangedPolje1(text qml.Object) {

        fmt.Printf("changed %#v\n", text.String("text"))
}

