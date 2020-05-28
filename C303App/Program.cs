﻿using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Net.Security;
using System.Text;
using System.Net;
using Newtonsoft.Json;
using NStack;
using Terminal.Gui;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Linq;

namespace C303App {
    class Program {
        // поля для модели данных
        public static String    AppDefaultPathData;
        public static LBAuthors Authors;
        public static LBBooks   Books;
        public static LBReaders Readers;
        // главное меню
        public static MenuBar MainMenu;
        public static MenuBarItem MIFile;
        public static MenuItem MIFileExit;
        public static MenuBarItem MIRefs;
        public static MenuItem MIRefsAuthors;
        public static MenuItem MIRefsBooks;
        public static MenuItem MIRefsReaders;
//        public static MenuBarItem MIView;
 //       public static MenuBarItem MIViewLanguages;
        // окна
        public static Window WndAuthors;
        public static Window WndBooks;
        public static Window WndReaders;
        // методы приложения
        public static Window miRefNew(String ATtile, Ref ARef) {
            Window LResult = null;
            for(int i = 0; i < Application.Top.Subviews.Count; i++) {
                if(Application.Top.Subviews[i].Id == ATtile) {
                    LResult = (Window)Application.Top.Subviews[i];
                    Application.Top.RemoveAll();
                    Application.Top.Add(LResult);
                    Application.Top.Add(MainMenu);
                    LResult.FocusFirst();
                    break;
                }
            }
            if(null == LResult) {
                LResult = new Window(ATtile) {
                    Id = ATtile,
                    X = 0,
                    Y = 1, // для меню оставим одну строчку
                    Width = Dim.Fill(),
                    Height = Dim.Fill()
                };
                ListView LListViewRef = new ListView(
                    new Rect() {
                        X = 0,
                        Y = 0,
                        Height = 56,
                        Width = 158
                    },
                    ARef);
                LResult.Add(LListViewRef);
                Application.Top.Add(LResult);
            }
            Application.Run();
            return LResult;
        }
        // обработчики событий
        public static void miFileExit() {
            Application.Top.Running = false;
        }

        public static String CheckFoldersSettings() {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "AppData"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
            // I.2 устанавливаем текущим путь "AppData"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(Consts.FolderMyApplication)) { // если нет
                Directory.CreateDirectory(Consts.FolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "AppData" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, Consts.FolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            return LDefaultPath;
        }
        public static String CheckFoldersData() {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "Мои Документы"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            // I.2 устанавливаем текущим путь "Мои Документы"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(Consts.FolderMyApplication)) { // если нет
                Directory.CreateDirectory(Consts.FolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "Мои Документы" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, Consts.FolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.5 создаём попдпапку с локализацие приложения "Мои Документы" \ FolderMyApplication \ CFolderLocal
            if(!Directory.Exists(Consts.FolderLocal)) { // если нет
                Directory.CreateDirectory(Consts.FolderLocal); // создаём эту папку
            }
            return LDefaultPath;
        }
        public static void ObjInit() {
            // работаем с окнами
            WndAuthors = null;
            WndBooks   = null;
            WndReaders = null;
            // пункты меню главного меню программы
            MIFileExit = new MenuItem("Выход", "", () => { miFileExit(); });
            MIFile = new MenuBarItem("Файл", new MenuItem[] { MIFileExit });

            MIRefsAuthors = new MenuItem("Авторы книг", "", () => { WndAuthors = miRefNew("Авторы"  , Authors); });
            MIRefsBooks   = new MenuItem("Книги"      , "", () => { WndBooks   = miRefNew("Книги"   , Books  ); });
            MIRefsReaders = new MenuItem("Читатели"   , "", () => { WndReaders = miRefNew("Читатели", Readers); });
            MIRefs = new MenuBarItem("Справочники", new MenuItem[] {
                MIRefsAuthors, MIRefsBooks, MIRefsReaders
            });
//            MIView = new MenuBarItem(Msgs.StrView, LbmiLanguages);
            MainMenu = new MenuBar(new MenuBarItem[] { MIFile, MIRefs});
        }
        static void Main(string[] args) {
            // проверка рабочего каталога приложения
            AppDefaultPathData = CheckFoldersData();
            // создаём справочники
            Authors = new LBAuthors();
            Books   = new LBBooks();
            Readers = new LBReaders();
            // загрузить справочники из внешних файлов
            Authors.LoadFromFile(Path.Combine(AppDefaultPathData, Consts.FileNameAuthors));
            Books.LoadFromFile  (Path.Combine(AppDefaultPathData, Consts.FileNameBooks  ));
            Readers.LoadFromFile(Path.Combine(AppDefaultPathData, Consts.FileNameReaders));

            // создание  интерфейса приложения
            ObjInit();
            Application.Init();
            Application.Top.Add(MainMenu);
            Application.Run();

            // сохраняем данные при выходе из приложения
            if(null != Authors) { Authors.SaveToFile(Path.Combine(AppDefaultPathData, Consts.FileNameAuthors)); }
            if(null != Books  ) { Books.SaveToFile  (Path.Combine(AppDefaultPathData, Consts.FileNameBooks  )); }
            if(null != Readers) { Readers.SaveToFile(Path.Combine(AppDefaultPathData, Consts.FileNameReaders)); }
            return;
        }
    }
}
