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

namespace C302SerializeJSON {
    class Program {
        const String CFolderMyApplication = "WorkJSON";
        const String CFolderLocal = "lang";
        const String CRemoteJSON = "http://resources.finance.ua/ru/public/currency-cash.json";
        const String CLocalJSON = "currency-cash.json";
        // поля для модели данных
        public static Reference Cities;
        public static Reference Regions;
        public static Reference Currencies;
        public static Reference OrgTypes;
        public static Organitations Orgs;
        // служебные поля
        public static MessagesHolder Msgs;
        // поля для элементов управления
        public static MenuBar MainMenu;
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
            LResult.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.Green, Color.Black);
            return LResult;
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
        public static String CheckFolders() {
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
        public static MenuBar AppMainMenu() {
            MenuItem LmiFileExit = new MenuItem(Msgs.StrFileExit, "", () => {
                miFileExit();
            });
            MenuItem LmiRefsCities = new MenuItem(Msgs.StrTowns, "", () => {
                WndCities = miRefNew(Msgs.StrTowns, Cities);
                Application.Run();
            });
            MenuItem LmiRefsRegions = new MenuItem(Msgs.StrRegions, "", () => {
                WndRegions = miRefNew(Msgs.StrRegions, Regions);
                Application.Run();
            });
            MenuItem LmiRefsCurrencies = new MenuItem(Msgs.StrCurrencies, "", () => {
                WndCurrencies = miRefNew(Msgs.StrCurrencies, Currencies);
                Application.Run();
            });
            MenuItem LmiRefsOrgTypes = new MenuItem(Msgs.StrOrgTypes, "", () => {
                WndOrgTypes = miRefNew(Msgs.StrOrgTypes, OrgTypes);
                Application.Run();
            });
            MenuItem LmiRefsOrgs = new MenuItem(Msgs.StrOrgs, "", () => {
                WndOrgs = miRefNew(Msgs.StrOrgs, Orgs);
                Application.Run();
            });

            MenuBarItem LbmiFile = new MenuBarItem(Msgs.StrFile, new MenuItem[] { LmiFileExit });
            MenuBarItem LbmiRefs = new MenuBarItem(Msgs.StrReferences, new MenuItem[] {
                LmiRefsCities, LmiRefsRegions, LmiRefsCurrencies, LmiRefsOrgTypes, LmiRefsOrgs
            });
            MenuBar LResult = new MenuBar(new MenuBarItem[] { LbmiFile, LbmiRefs });
            //LResult.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.Cyan, Color.Black);
            return LResult;
        }
        public static void Main(string[] args) {
            // 1. проверка рабочего каталога приложения
            String LDefaultPath = CheckFolders();
            // 2. скачать файл из интернета
            if(!File.Exists(Path.Combine(LDefaultPath, CLocalJSON))) {
                DownloadFileText(CRemoteJSON, Path.Combine(LDefaultPath, CLocalJSON));
            }
            // 3. загрузить данные из файла
            String LJSON = File.ReadAllText(Path.Combine(LDefaultPath, CLocalJSON));
            var LCourceObject = JsonConvert.DeserializeObject<dynamic>(LJSON);
            // 3.1. загрузка локализации
            Msgs = new MessagesHolder();
            String[] LLocalFiles = Directory.GetFiles(Path.Combine(LDefaultPath, CFolderLocal));
            // 3.2. организовать выбор локализации
            foreach(String LLocalFile  in LLocalFiles) {
                String LLocalName = Path.GetFileNameWithoutExtension(LLocalFile);
                if(LLocalName.ToUpper().Equals("BL")) { // заглушка, строку "EN" мы будем брать из настроек
                    Msgs.LoadFromFile(LLocalFile);
                }
            }
            // 4. создаём справочники
            Cities     = new Reference(LCourceObject.cities);
            Regions    = new Reference(LCourceObject.regions);
            Currencies = new Reference(LCourceObject.currencies);
            OrgTypes   = new Reference(LCourceObject.orgTypes);
            Orgs       = new Organitations(LCourceObject.organizations, OrgTypes, Regions, Cities, Currencies);
            // 5. зануляем переменные - указатели на объекты окна
            WndCities = null;
            WndRegions = null;
            WndCurrencies = null;
            WndOrgTypes = null;

            MainMenu = AppMainMenu();

            Application.Init();
            Application.Top.Add(MainMenu);
            Application.Run();
        }
    }
}
