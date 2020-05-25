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
using System.Linq;

namespace C302SerializeJSON {
    class Program {
        const String CFileSettings = "settings.json";
        const String CFolderMyApplication = "WorkJSON";
        const String CFolderLocal = "lang";
        const String CRemoteJSON = "http://resources.finance.ua/ru/public/currency-cash.json";
        const String CLocalJSON = "currency-cash.json";
        // поля для модели данных
        public static String AppDefaultPathData;
        public static Reference Cities;
        public static Reference Regions;
        public static Reference Currencies;
        public static Reference OrgTypes;
        public static Organitations Orgs;
        // служебные поля
        public static AppSettings Settings;
        public static MessagesHolder Msgs;
        // поля для элементов управления
        // главное меню
        public static MenuBar MainMenu;
        public static MenuBarItem MIFile;
        public static MenuItem MIFileExit;
        public static MenuBarItem MIRefs;
        public static MenuItem MIRefsCities;
        public static MenuItem MIRefsRegions;
        public static MenuItem MIRefsCurrencies;
        public static MenuItem MIRefsOrgTypes;
        public static MenuItem MIRefsOrgs;
        public static MenuBarItem MIView;
        public static MenuBarItem MIViewLanguages;
        // окна
        public static Window WndCities;
        public static Window WndRegions;
        public static Window WndCurrencies;
        public static Window WndOrgTypes;
        public static Window WndOrgs;
        // 
        // обработчики событий
        public static void miFileExit() {
            Application.Top.Running = false;
        }
        public static Window miRefNew(String ATtile, Reference ARef) {
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
            LResult.ColorScheme.Normal = Application.Driver.MakeAttribute(Settings.Foreground, Settings.Background);
            //MainMenu.ColorScheme = Colors.Menu;
            Application.Run();
            return LResult;
        }
        public static void miLocal(String LocalLang = "ru") {
            ObjLocal(LocalLang);
            Application.Run();
        }
        public static void ObjInit() {
            // работаем с окнами
            WndCities     = null;
            WndRegions    = null;
            WndCurrencies = null;
            WndOrgTypes   = null;
            // пункты меню главного меню программы
            MIFileExit       = new MenuItem   (Msgs.StrFileExit, "", () => { miFileExit();});
            MIFile           = new MenuBarItem(Msgs.StrFile, new MenuItem[] { MIFileExit });

            MIRefsCities     = new MenuItem(Msgs.StrTowns     , "", () => {WndCities     = miRefNew(Msgs.StrTowns, Cities); });
            MIRefsRegions    = new MenuItem(Msgs.StrRegions   , "", () => {WndRegions    = miRefNew(Msgs.StrRegions, Regions); });
            MIRefsCurrencies = new MenuItem(Msgs.StrCurrencies, "", () => {WndCurrencies = miRefNew(Msgs.StrCurrencies, Currencies);});
            MIRefsOrgTypes   = new MenuItem(Msgs.StrOrgTypes  , "", () => {WndOrgTypes   = miRefNew(Msgs.StrOrgTypes, OrgTypes);});
            MIRefsOrgs       = new MenuItem(Msgs.StrOrgs      , "", () => {WndOrgs       = miRefNew(Msgs.StrOrgs, Orgs); });
            MIRefs           = new MenuBarItem(Msgs.StrReferences, new MenuItem[] {
                MIRefsCities, MIRefsRegions, MIRefsCurrencies, MIRefsOrgTypes, MIRefsOrgs
            });
            
            String[] LLocalFiles = Directory.GetFiles(Path.Combine(AppDefaultPathData, CFolderLocal));
            MenuItem[] LbmiLanguages = new MenuItem[LLocalFiles.Count()];
            int i = 0;
            foreach(String LLocalFile in LLocalFiles) {
                String LLocalName = Path.GetFileNameWithoutExtension(LLocalFile);
                LbmiLanguages[i] = new MenuItem(LLocalName.ToLower(), "", () => { miLocal(LLocalName.ToLower()); });
                i++;
            }
            MIViewLanguages = new MenuBarItem(Msgs.StrViewLanguage, LbmiLanguages);
            MIView          = new MenuBarItem(Msgs.StrView, LbmiLanguages);
            MainMenu        = new MenuBar(new MenuBarItem[] { MIFile, MIRefs, MIView });
            MainMenu.ColorScheme = Colors.Menu;
        }
        public static void ObjLocal(String Localization) {
            if(null == Msgs) {
                Msgs = new MessagesHolder();
            }
            if(File.Exists(Path.Combine(AppDefaultPathData, CFolderLocal, Localization.ToLower() + ".json"))) {
                Msgs.LoadFromFile(Path.Combine(AppDefaultPathData, CFolderLocal, Localization.ToLower() + ".json"));
                MIFile.Title           = Msgs.StrFile;
                MIFileExit.Title       = Msgs.StrFileExit;
                MIRefs.Title           = Msgs.StrReferences;
                MIRefsCities.Title     = Msgs.StrTowns;
                MIRefsRegions.Title    = Msgs.StrRegions;
                MIRefsCurrencies.Title = Msgs.StrCurrencies;
                MIRefsOrgTypes.Title   = Msgs.StrOrgTypes;
                MIRefsOrgs.Title       = Msgs.StrOrgs;
                MIView.Title           = Msgs.StrView;
                MIViewLanguages.Title  = Msgs.StrViewLanguage;
                if(null != WndCities    ) { WndCities.Title     = Msgs.StrTowns; }
                if(null != WndRegions   ) { WndRegions.Title    = Msgs.StrRegions; }
                if(null != WndCurrencies) { WndCurrencies.Title = Msgs.StrCurrencies; }
                if(null != WndOrgTypes  ) { WndOrgTypes.Title   = Msgs.StrOrgTypes; }
            }
        }

        public static void miCources(OrgsItem AItem) {
            Window LWndw = new Window("Курсы валют у "+AItem.Name.PadRight(36));
            LWndw.X = 0;
            LWndw.Y = 1;
            LWndw.Width = Dim.Fill();
            LWndw.Height = Dim.Fill();
            LWndw.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.White, Color.Red);
            ListView LListViewCource = new ListView(
                new Rect() {
                    X = 0,
                    Y = 0,
                    Height = 56,
                    Width = 156
                },
                AItem.Cources);
            LWndw.Add(LListViewCource);
            Application.Top.Add(LWndw);
            Application.Run();
        }
        public static void miRefOrgs() {
            void KeyDown(KeyEvent keyEvent, ListView AListView) {
                if(keyEvent.Key == Key.Enter) {
                    miCources((OrgsItem)Orgs[AListView.SelectedItem]);
                }
            }
            Window LWndw = new Window("Организации");
            LWndw.X = 0;
            LWndw.Y = 1;
            LWndw.Width = Dim.Fill();
            LWndw.Height = Dim.Fill();
            /*
            {
                X = 0,
                Y = 1, // для меню оставим одну строчку
                Width = Dim.Fill(),
                Height = Dim.Fill()
            };
            */
            LWndw.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.White, Color.Blue);
            ListView LListViewRef = new ListView(
                new Rect() {
                    X = 0,
                    Y = 0,
                    Height = 56,
                    Width = 156
                },
                Orgs);
            LListViewRef.OnKeyDown += (KeyEvent keyEvent) => KeyDown(keyEvent, LListViewRef);
            LWndw.Add(LListViewRef);
            Application.Top.Add(LWndw);
            Application.Run();
        }
        public static void DownloadFileText(String ARemoteURL, String ALocalPath) {
            WebRequest LWRQ = WebRequest.Create(ARemoteURL);
            LWRQ.Credentials = CredentialCache.DefaultCredentials;
            WebResponse LWR = LWRQ.GetResponse();
            Stream LStrm = LWR.GetResponseStream();
            StreamReader LReader = new StreamReader(LStrm);
            String LFileBody = LReader.ReadToEnd();
            LReader.Close();
            File.WriteAllText(ALocalPath, LFileBody);
        }
        public static String CheckFoldersSettings() {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "AppData"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
            // I.2 устанавливаем текущим путь "AppData"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(CFolderMyApplication)) { // если нет
                Directory.CreateDirectory(CFolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "AppData" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, CFolderMyApplication);
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
            if(!Directory.Exists(CFolderMyApplication)) { // если нет
                Directory.CreateDirectory(CFolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "Мои Документы" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, CFolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.5 создаём попдпапку с локализацие приложения "Мои Документы" \ FolderMyApplication \ CFolderLocal
            if(!Directory.Exists(CFolderLocal)) { // если нет
                Directory.CreateDirectory(CFolderLocal); // создаём эту папку
            }
            return LDefaultPath;
        }
        public static void Main(string[] args) {
            // I.0 Настройки приложения
            Settings = new AppSettings();
            // I.1 проверка каталога настроек
            String LSettingsPath = CheckFoldersSettings();
            // I.2. проверяем, существует ли файл настроек? (первый запуск приложения)
            if(!File.Exists( Path.Combine(LSettingsPath, CFileSettings) )) {
                // если нет, сохраняем настройки по-умолчанию в файл
                Settings.SaveToFile(Path.Combine(LSettingsPath, CFileSettings));
            }
            // I.3 загружаем настройки
            Settings.LoadFromFile( Path.Combine(LSettingsPath, CFileSettings) );

            // II.1. проверка рабочего каталога приложения
            AppDefaultPathData = CheckFoldersData();
            // II.2. скачать файл из интернета
            if(!File.Exists(Path.Combine(AppDefaultPathData, CLocalJSON))) {
                DownloadFileText(CRemoteJSON, Path.Combine(AppDefaultPathData, CLocalJSON));
            }
            // II.3. загрузить данные из файла
            String LJSON = File.ReadAllText(Path.Combine(AppDefaultPathData, CLocalJSON));
            var LCourceObject = JsonConvert.DeserializeObject<dynamic>(LJSON);
            // II.3.1. загрузка локализации
            Msgs = new MessagesHolder();
            // II.3.1.1 первый запуск приложения
            if(!File.Exists(Path.Combine(AppDefaultPathData, CFolderLocal, Settings.Localization.ToLower()+".json"))) {
                Msgs.SaveToFile(Path.Combine(AppDefaultPathData, CFolderLocal, Settings.Localization.ToLower() + ".json"));
            }
            Msgs.LoadFromFile(Path.Combine(AppDefaultPathData, CFolderLocal, Settings.Localization.ToLower() + ".json"));
            // II.3.2. организовать выбор локализации
            String[] LLocalFiles = Directory.GetFiles(Path.Combine(AppDefaultPathData, CFolderLocal));
            foreach(String LLocalFile  in LLocalFiles) {
                String LLocalName = Path.GetFileNameWithoutExtension(LLocalFile);
                if(LLocalName.ToUpper().Equals(Settings.Localization)) { 
                    Msgs.LoadFromFile(LLocalFile);
                }
            }
            // III.1. создаём справочники
            Cities     = new Reference(LCourceObject.cities);
            Regions    = new Reference(LCourceObject.regions);
            Currencies = new Reference(LCourceObject.currencies);
            OrgTypes   = new Reference(LCourceObject.orgTypes);
            Orgs       = new Organitations(LCourceObject.organizations, OrgTypes, Regions, Cities, Currencies);

            ObjInit();
            ObjLocal(Settings.Localization);

            Application.Init();
            Application.Top.Add(MainMenu);
            Application.Run();

            // ZZZ.1. при выходе из приложения сохраняем настройки
            // потому, что возможно они были изменены пользователем в процессе  работы приложения
            Settings.SaveToFile(Path.Combine(LSettingsPath, CFileSettings));
        }
    }
}
