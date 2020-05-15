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

namespace C302SerializeJSON {
    class Program {
        const String CFolderMyApplication = "WorkJSON";
        const String CRemoteJSON = "http://resources.finance.ua/ru/public/currency-cash.json";
        const String CLocalJSON = "currency-cash.json";
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
            return LDefaultPath;
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
            // 4. создаём справочники
            Reference LCities = new Reference();
            LCities.LoadFromJSON(LCourceObject.cities);



            Application.Init();
            // Creates the top-level window to show
            var win = new Window("Наше окно тестовго приложения") {
               X = 0,
               Y = 1, // для меню оставим одну строчку
               Width = Dim.Fill(),
               Height = Dim.Fill()
            };
            Application.Top.Add(win);

            //MenuBarItem bmiFile = new MenuBarItem("_File", null);            
            //MenuBarItem bmiRef  = new MenuBarItem("_File", null);


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
