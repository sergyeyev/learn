using System;
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
using System.Runtime.CompilerServices;
using System.Linq;

namespace C303App {
    public static class ViewExtension {
        class RefObjectLink {
            public Ref Reference;
        }
        static readonly ConditionalWeakTable<View, RefObjectLink> FHelperRef = new ConditionalWeakTable<View, RefObjectLink>();
        public static Ref GetReference(this View AView) {
            return FHelperRef.GetOrCreateValue(AView).Reference;
        }
        public static void SetReference(this View AView, Ref ARef) {
            FHelperRef.GetOrCreateValue(AView).Reference = ARef;
        }

        class ViewObjectLink {
            public View LinkedControl;
        }
        static readonly ConditionalWeakTable<View, ViewObjectLink> FHelperLinkedControl = new ConditionalWeakTable<View, ViewObjectLink>();
        public static View GetLinkedControl(this View AView) {
            return FHelperLinkedControl.GetOrCreateValue(AView).LinkedControl;
        }
        public static void SetLinkedControl(this View AView, View ALinkedControl) {
            FHelperLinkedControl.GetOrCreateValue(AView).LinkedControl = ALinkedControl;
        }

    };
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
        // Справочник- Авторы
        public static Window WndAuthors;
        public static ListView ListViewAuthors;
        public static FrameView WndAuthorsFrameRight;
        public static TextField TxtFldAuthorId;
        public static TextField TxtFldAuthorName;
        public static Window WndBooks;
        // Справочник- Книги
        public static ListView ListViewBooks;
        public static FrameView WndBooksFrameRight;
        public static TextField TxtFldBooksId;
        public static TextField TxtFldBooksName;
        public static TextField TxtFldBooksAuthor;
        public static TextField TxtFldBooksISBN;
        // Справочник- Читатели
        public static Window WndReaders;
        public static ListView ListViewReaders;
        public static FrameView WndReadersFrameRight;
        public static TextField TxtFldReadersId;
        public static TextField TxtFldReadersName;
        public static TextField TxtFldReadersTicketNo;
        public static TextField TxtFldReadersAddress;
        public static TextField TxtFldReadersPhone;



        public static void ListViewAuthorsOnSelectedChanged() {
            TxtFldAuthorId.Text   = Authors.ElementAt(ListViewAuthors.SelectedItem).Id.ToString();
            TxtFldAuthorName.Text = Authors.ElementAt(ListViewAuthors.SelectedItem).Name;
        }
        public static void ListViewBooksOnSelectedChanged() {
            TxtFldBooksId.Text = Books.ElementAt(ListViewBooks.SelectedItem).Id.ToString();
            TxtFldBooksName.Text = Books.ElementAt(ListViewBooks.SelectedItem).Name;
            TxtFldBooksAuthor.Text = ( (LBBook)Books.ElementAt(ListViewBooks.SelectedItem) ).Author.Name;
            TxtFldBooksISBN.Text = ( (LBBook)Books.ElementAt(ListViewBooks.SelectedItem) ).ISBN;
        }
        public static void ListViewReadersOnSelectedChanged() {
            TxtFldReadersId.Text   = Readers.ElementAt(ListViewReaders.SelectedItem).Id.ToString();
            TxtFldReadersName.Text = Readers.ElementAt(ListViewReaders.SelectedItem).Name;
        }
        public static void TxtFld_OnEnter(object sender, EventArgs e) {
            ( (TextField)sender ).SelectedStart = 0;
            ( (TextField)sender ).SelectedLength = ( (TextField)sender ).Text.ToString().Length;
        }
        public static void TxtFldId_OnLeave(object sender, EventArgs e) {
            ((TextField)sender).GetLinkedControl().GetReference().ElementAt(
                    ( (ListView) ((TextField)sender).GetLinkedControl() ).SelectedItem
            ).Id = int.Parse(( (TextField)sender ).Text.ToString());
        }
        public static void TxtFldName_OnLeave(object sender, EventArgs e) {
            ( (TextField)sender ).GetLinkedControl().GetReference().ElementAt(
                    ( (ListView)( (TextField)sender ).GetLinkedControl() ).SelectedItem
            ).Name = ((TextField)sender).Text.ToString();
        }

        public static void RefSave(Ref ARef) {
            if(null != ARef) {
                ARef.SaveToFile();
            }
        }
        public static void RefDel(Ref ARef, ListView AListView) {
            ARef.Remove( ARef.ElementAt(AListView.SelectedItem) );
            AListView.FocusFirst();
        }

        public static void AuthorsAdd() {
            LBAuthor LItem = new LBAuthor();
            LItem.Id = Authors.GenId();
            Authors.Add(LItem);
            ListViewAuthors.SelectedItem = Authors.Count - 1;
            ListViewAuthorsOnSelectedChanged();
            ListViewAuthors.FocusFirst();
        }

        // методы приложения
        public static Window miRefNewAuthors(String ATtile, Ref ARef) {
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
                ListViewAuthors = new ListView(
                    new Rect() {
                        X = 0,
                        Y = 1,
                        Height = 56,
                        Width = 128
                    },
                    ARef);
                ListViewAuthors.SetReference(ARef);
                ListViewAuthors.SelectedChanged += () => { ListViewAuthorsOnSelectedChanged(); };
                LResult.Add(ListViewAuthors);
                WndAuthorsFrameRight = new FrameView("Автор") {
                    X = 128,
                    Y = 1,
                    Height = 56,
                    Width = 30
                };
                WndAuthorsFrameRight.Add(
                    new Label("Код:") { 
                        X = 1, 
                        Y = 1, 
                        Height = 1, 
                        Width = WndAuthorsFrameRight.Width - 4 
                    }
                );
                TxtFldAuthorId = new TextField("") {
                    X = 1,
                    Y = 2,
                    Height = 1,
                    Width = WndAuthorsFrameRight.Width - 4
                };
                TxtFldAuthorId.SetLinkedControl(ListViewAuthors);
                TxtFldAuthorId.SetReference(ARef);
                TxtFldAuthorId.Enter += TxtFld_OnEnter;
                TxtFldAuthorId.Leave += TxtFldId_OnLeave;
                WndAuthorsFrameRight.Add(TxtFldAuthorId);

                WndAuthorsFrameRight.Add(
                    new Label("Название:") { 
                        X = 1, 
                        Y = 5, 
                        Height = 1, 
                        Width = WndAuthorsFrameRight.Width - 4 
                    }
                );
                TxtFldAuthorName = new TextField("") {
                    X = 1,
                    Y = 6,
                    Height = 1,
                    Width = WndAuthorsFrameRight.Width - 4
                };
                TxtFldAuthorName.SetLinkedControl(ListViewAuthors);
                TxtFldAuthorName.SetReference(ARef);
                TxtFldAuthorName.Enter += TxtFld_OnEnter;
                TxtFldAuthorName.Leave += TxtFldName_OnLeave;  
                WndAuthorsFrameRight.Add(TxtFldAuthorName);

                LResult.Add(WndAuthorsFrameRight);

                LResult.Add(new Button(0, 0, "S Сохранить") {
                    Width = 16,
                    Clicked = () => { RefSave(Authors);  }
                });
                LResult.Add(new Button(17, 0, "A Добавить") {
                    Width = 16,
                    Clicked = () => { AuthorsAdd();  }
                });
                LResult.Add(new Button(32, 0, "D Удалить") {
                    Width = 16,
                    Clicked = () => { RefDel(Authors, ListViewAuthors); }
                });

                Application.Top.Add(LResult);
            }
            ListViewAuthors.FocusFirst();
            Application.Run();
            return LResult;
        }
        public static Window miRefNewBooks(String ATtile, Ref ARef) {
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
                ListViewBooks = new ListView(
                    new Rect() {
                        X = 0,
                        Y = 1,
                        Height = 56,
                        Width = 128
                    },
                    ARef);
                ListViewBooks.SetReference(ARef);
                ListViewBooks.SelectedChanged += () => { ListViewBooksOnSelectedChanged(); };
                LResult.Add(ListViewBooks);
                WndBooksFrameRight = new FrameView("Книга") {
                    X = 128,
                    Y = 1,
                    Height = 56,
                    Width = 30
                };
                WndBooksFrameRight.Add(
                    new Label("Код:") {
                        X = 1,
                        Y = 1,
                        Height = 1,
                        Width = WndBooksFrameRight.Width - 4
                    }
                );
                TxtFldBooksId = new TextField("") {
                    X = 1,
                    Y = 2,
                    Height = 1,
                    Width = WndBooksFrameRight.Width - 4
                };
                TxtFldBooksId.SetLinkedControl(ListViewBooks);
                TxtFldBooksId.Enter += TxtFld_OnEnter;
                TxtFldBooksId.Leave += TxtFldId_OnLeave;
                WndBooksFrameRight.Add(TxtFldBooksId);

                WndBooksFrameRight.Add(
                    new Label("Название:") {
                        X = 1,
                        Y = 5,
                        Height = 1,
                        Width = WndBooksFrameRight.Width - 4
                    }
                );
                TxtFldBooksName = new TextField("") {
                    X = 1,
                    Y = 6,
                    Height = 1,
                    Width = WndBooksFrameRight.Width - 4
                };
                TxtFldBooksName.SetLinkedControl(ListViewBooks);
                TxtFldBooksName.Enter += TxtFld_OnEnter;
                TxtFldBooksName.Leave += TxtFldName_OnLeave;
                WndBooksFrameRight.Add(TxtFldBooksName);

                WndBooksFrameRight.Add(
                    new Label("Автор:") {
                        X = 1,
                        Y = 8,
                        Height = 1,
                        Width = WndBooksFrameRight.Width - 4
                    }
                );
                TxtFldBooksAuthor = new TextField("") {
                    X = 1,
                    Y = 9,
                    Height = 1,
                    Width = WndBooksFrameRight.Width - 4
                };
                TxtFldBooksAuthor.Enter += TxtFld_OnEnter;
                //TxtFldBooksName.Leave += TxtFldAuthorNameLeave;
                WndBooksFrameRight.Add(TxtFldBooksAuthor);

                WndBooksFrameRight.Add(
                    new Label("ISBN:") {
                        X = 1,
                        Y = 11,
                        Height = 1,
                        Width = WndBooksFrameRight.Width - 4
                    }
                );
                TxtFldBooksISBN = new TextField("") {
                    X = 1,
                    Y = 12,
                    Height = 1,
                    Width = WndBooksFrameRight.Width - 4
                };
                TxtFldBooksISBN.Enter += TxtFld_OnEnter;
                //TxtFldBooksISBN.Leave += TxtFldAuthorNameLeave;
                WndBooksFrameRight.Add(TxtFldBooksISBN);

                LResult.Add(WndBooksFrameRight);

                LResult.Add(new Button(0, 0, "S Сохранить") {
                    Width = 16,
                    Clicked = () => { RefSave(Books); }
                });
                LResult.Add(new Button(17, 0, "A Добавить") {
                    Width = 16//,
                    //Clicked = () => { AuthorsAdd(); }
                });
                LResult.Add(new Button(32, 0, "D Удалить") {
                    Width = 16,
                    Clicked = () => { RefDel(ARef, ListViewBooks); }
                });

                Application.Top.Add(LResult);
            }
            ListViewBooks.FocusFirst();
            Application.Run();
            return LResult;
        }
        public static Window miRefNewReaders(String ATtile, Ref ARef) {
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
                ListViewReaders = new ListView(
                    new Rect() {
                        X = 0,
                        Y = 1,
                        Height = 56,
                        Width = 128
                    },
                    ARef);
                ListViewReaders.SetReference(ARef);
                ListViewReaders.SelectedChanged += () => { ListViewReadersOnSelectedChanged(); };
                LResult.Add(ListViewReaders);
                WndReadersFrameRight = new FrameView("Читатель") {
                    X = 128,
                    Y = 1,
                    Height = 56,
                    Width = 30
                };
                WndReadersFrameRight.Add(
                    new Label("Код:") {
                        X = 1,
                        Y = 1,
                        Height = 1,
                        Width = WndReadersFrameRight.Width - 4
                    }
                );
                TxtFldReadersId = new TextField("") {
                    X = 1,
                    Y = 2,
                    Height = 1,
                    Width = WndReadersFrameRight.Width - 4
                };
                TxtFldReadersId.SetLinkedControl(ListViewReaders);
                TxtFldReadersId.Enter += TxtFld_OnEnter;
                TxtFldReadersId.Leave += TxtFldId_OnLeave;
                WndReadersFrameRight.Add(TxtFldReadersId);

                WndReadersFrameRight.Add(
                    new Label("Название:") {
                        X = 1,
                        Y = 5,
                        Height = 1,
                        Width = WndReadersFrameRight.Width - 4
                    }
                );
                TxtFldReadersName = new TextField("") {
                    X = 1,
                    Y = 6,
                    Height = 1,
                    Width = WndReadersFrameRight.Width - 4
                };
                TxtFldReadersName.SetLinkedControl(ListViewReaders);
                TxtFldReadersName.Enter += TxtFld_OnEnter;
                TxtFldReadersName.Leave += TxtFldName_OnLeave;
                WndReadersFrameRight.Add(TxtFldReadersName);

                LResult.Add(WndReadersFrameRight);

                LResult.Add(new Button(0, 0, "S Сохранить") {
                    Width = 16,
                    Clicked = () => { RefSave(Readers); }
                });
                LResult.Add(new Button(17, 0, "A Добавить") {
                    Width = 16//,
                    //Clicked = () => { AuthorsAdd(); }
                });
                LResult.Add(new Button(32, 0, "D Удалить") {
                    Width = 16,
                    Clicked = () => { RefDel(ARef, ListViewReaders); }
                });

                Application.Top.Add(LResult);
            }
            ListViewReaders.FocusFirst();
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
            MIFile     = new MenuBarItem("Файл", new MenuItem[] { MIFileExit });

            MIRefsAuthors = new MenuItem("Авторы книг", "", () => { WndAuthors = miRefNewAuthors("Авторы"  , Authors); });
            MIRefsBooks   = new MenuItem("Книги"      , "", () => { WndBooks   = miRefNewBooks  ("Книги"   , Books  ); });
            MIRefsReaders = new MenuItem("Читатели"   , "", () => { WndReaders = miRefNewReaders("Читатели", Readers); });
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
            Authors = new LBAuthors();  Authors.FileName = Path.Combine(AppDefaultPathData, Consts.FileNameAuthors);
            Books   = new LBBooks  ();  Books.FileName   = Path.Combine(AppDefaultPathData, Consts.FileNameBooks);
            Readers = new LBReaders();  Readers.FileName = Path.Combine(AppDefaultPathData, Consts.FileNameReaders);
            // загрузить справочники из внешних файлов
            Authors.LoadFromFile();
            Books.LoadFromFile  (null, new List<Ref> { Authors });
            Readers.LoadFromFile();


            // создание  интерфейса приложения
            ObjInit();
            Application.Init();
            Application.Top.Add(MainMenu);
            Application.Run();

            // сохраняем данные при выходе из приложения
            if(null != Authors) { Authors.SaveToFile(); }
            if(null != Books  ) { Books.SaveToFile  (); }
            if(null != Readers) { Readers.SaveToFile(); }
            return;
        }
    }
}
