using System;
using NStack;
using Terminal.Gui;

namespace C302SerializeJSON {
    class Program {
        unsafe public static void Main(string[] args) {
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
                    new MenuItem ("_Quit" , "", () => {Application.Top.Running = false;} )
                }),
                new MenuBarItem ("_Edit", new MenuItem [] {
                    new MenuItem ("_Copy", "", null),
                    new MenuItem ("C_ut", "", null),
                    new MenuItem ("_Paste", "", null)
                })
            });
            Application.Top.Add(menu);

            var LLabel1 = new Label(0, 0, "Элемент класса Label с координатами (0,0) ");
            var LLabel2 = new Label(1, 1, "Элемент класса Label с координатами (1,1) ");
            var LLabel3 = new Label(2, 2, "Элемент класса Label с координатами (2,2) ");
            var LLabel4 = new Label(3, 18, "Элемент класса Label с координатами (3,18) ");
            var LLabel11 = new Label(-1, 4, "Элемент класса Label с координатами (-1,4) ");
            var LLabel12 = new Label(-3, 5, "Элемент класса Label с координатами (-3,5) ");
            var LLabel13 = new Label(150, 6, "Элемент класса Label с координатами (150,6) ");

            win.Add( LLabel1, LLabel2, LLabel3, LLabel4, LLabel11, LLabel12, LLabel13);

            Application.Run();
        }
    }
}
