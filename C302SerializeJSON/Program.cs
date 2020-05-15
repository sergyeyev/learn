using System;
using NStack;
using Terminal.Gui;

namespace C302SerializeJSON {
    class Program {
        public static void Main(string[] args) {
            Application.Init();
            // Creates the top-level window to show
            var win = new Window("Наше окно тестовго приложения") {
               X = 0,
               Y = 1, // для меню оставим одну строчку
               Width = Dim.Fill(),
               Height = Dim.Fill()
            };
            Application.Top.Add(win);

            // Creates a menubar, the item "New" has a help menu.
            var menu = new MenuBar(new MenuBarItem[] {
                new MenuBarItem ("_File", new MenuItem [] {
                    new MenuItem ("_New"  , "Creates new file", null),
                    new MenuItem ("_Close", "", null),
                    new MenuItem ("Выход" , "", () => {
                        Application.Top.Running = false;
                    } 
                    )
                }),
                new MenuBarItem ("_Edit", new MenuItem [] {
                    new MenuItem ("_Copy", "", null),
                    new MenuItem ("C_ut", "", null),
                    new MenuItem ("_Paste", "", null)
                })
            });
            Application.Top.Add(menu);

 
             Application.Run();
        }
    }
}
