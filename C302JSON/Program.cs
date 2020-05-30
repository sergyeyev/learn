using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Net.Security;
using System.Runtime.CompilerServices;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.Net;
using Newtonsoft.Json;
using Microsoft.DocAsCode.Common;

namespace _301Sales {


    class Program {
        const String FolderMyApplication = "My Student Application";
        const String RemoteJSON = "http://resources.finance.ua/ru/public/currency-cash.json";
        const String LocalJSON  = "currency-cash.json";
        // JSON = JavaScript Object Notation

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

        static List<ReferenceItem> RefrerenceFromJSON(dynamic AObject) {
            List<ReferenceItem> LResult = new List<ReferenceItem>();
            foreach(var LObj in AObject) {
                ReferenceItem LItem = new ReferenceItem();
                LItem.Id   = LObj.Name;
                LItem.Name = ( (String)LObj.Value );
                LResult.Add(LItem);
            }
            return LResult;
        }

        static void ReferencePrint(String ACaption, List<ReferenceItem> AReference, ConsoleColor AColor = ConsoleColor.White) {
            int LMaxLenId   = 0;
            int LMaxLenName = 0;
            foreach(ReferenceItem LItem in AReference) {
                if(LItem.Id.Length   > LMaxLenId  ) LMaxLenId   = LItem.Id.Length;
                if(LItem.Name.Length > LMaxLenName) LMaxLenName = LItem.Name.Length;
            }
            // как будем выводить:
            // "+-----------+"  A1
            // "| ACaption  |"  A2 
            // "-------------"  A3
            // "| ID | NAME |"  A4
            // "-------------"  A5
            // "| 1  | .... |"  A6
            // "-------------"  A7
            int LSummaryLen = 2 + LMaxLenId + 3 + LMaxLenName + 2;
            while(LSummaryLen < (ACaption.Length + 4)) {
                LMaxLenId++;
                LMaxLenName++;
                LSummaryLen = 2 + LMaxLenId + 3 + LMaxLenName + 2;
            }
            // начинаем вывод
            Console.ForegroundColor = AColor;
            // A1 верхняя рамка A1
            Console.Write("\u2554");
            for(int i=0; i < (LSummaryLen - 2); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2557");
            Console.WriteLine();
            // A2 заголовок справочника
            Console.WriteLine("\u2551 " + ACaption.PadRight(LSummaryLen - 4) + " \u2551");
            // A3 рамка разделитель
            Console.Write("\u2560");
            for(int i = 0; i < ( LMaxLenId + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2566");
            for(int i = 0; i < ( LMaxLenName + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2563");
            Console.WriteLine();
            // A4 заголовки колонок
            Console.WriteLine("\u2551 " + "Id".PadRight(LMaxLenId) + " \u2551 " + "Name".PadRight(LMaxLenName) + " \u2551");
            // A5 разделитель
            Console.Write("\u2560");
            for(int i = 0; i < ( LMaxLenId + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u256C");
            for(int i = 0; i < ( LMaxLenName + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2563");
            Console.WriteLine();
            // A6 вывод самих данных
            foreach(ReferenceItem LItem in AReference) {
                Console.WriteLine("\u2551 " + LItem.Id.PadRight(LMaxLenId) + " \u2551 " + LItem.Name.PadRight(LMaxLenName) + " \u2551");
            }
            // A7 вывод завершающую рамку
            Console.Write("\u255A");
            for(int i = 0; i < ( LMaxLenId + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2569");
            for(int i = 0; i < ( LMaxLenName + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u255D");
            Console.WriteLine();
        }

        static void ReferencePrintCource(String ACaption, List<CourceItem> AReference, ConsoleColor AColor = ConsoleColor.White) {
            int LFloatWidth    = 8; // всего на вывод вещественного поля
            int LFloatWidthDec = 4; // символов после запятой
            int LMaxLenId   = 0;
            int LMaxLenName = 0;
            foreach(CourceItem LItem in AReference) {
                if(LItem.Currency.Id.Length   > LMaxLenId  ) LMaxLenId   = LItem.Currency.Id.Length;
                if(LItem.Currency.Name.Length > LMaxLenName) LMaxLenName = LItem.Currency.Name.Length;
            }
            // как будем выводить:
            // "+-------------------------+"  A1
            // "| ACaption                |"  A2 
            // "---------------------------"  A3
            // "| ID | NAME | Buy  | Sale |"  A4
            // "------------------+------+"  A5
            // "| 1  | .... | 0.00 | 0.00 |"  A6
            // "---------------------------"  A7
            int LSummaryLen = 2 + LMaxLenId + 3 + LMaxLenName + 3 + LFloatWidth + 3 + LFloatWidth + 2;
            while(LSummaryLen < ( ACaption.Length + 4 )) {
                LMaxLenId++;
                LMaxLenName++;
                LFloatWidth++;
                LSummaryLen = 2 + LMaxLenId + 3 + LMaxLenName + 3 + LFloatWidth + 3 + LFloatWidth + 2;
            }
            // начинаем вывод
            Console.ForegroundColor = AColor;
            // A1 верхняя рамка A1
            Console.Write("\u2554");
            for(int i = 0; i < ( LSummaryLen - 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2557");
            Console.WriteLine();
            // A2 заголовок справочника
            Console.WriteLine("\u2551 " + ACaption.PadRight(LSummaryLen - 4) + " \u2551");
            // A3 рамка разделитель
            Console.Write("\u2560");
            for(int i = 0; i < ( LMaxLenId + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2566");
            for(int i = 0; i < ( LMaxLenName + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2566");
            for(int i = 0; i < LFloatWidth+2; i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2566");
            for(int i = 0; i < LFloatWidth+2; i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2563");
            Console.WriteLine();
            // A4 заголовки колонок
            Console.WriteLine("\u2551 " + "Id".PadRight(LMaxLenId) + " \u2551 " + "Name".PadRight(LMaxLenName) + 
                " \u2551 " + "Buy".PadRight(LFloatWidth) + " \u2551 " + "Sale".PadRight(LFloatWidth) + " \u2551");
            // A5 разделитель
            Console.Write("\u2560");
            for(int i = 0; i < ( LMaxLenId + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u256C");
            for(int i = 0; i < ( LMaxLenName + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u256C");
            for(int i = 0; i < LFloatWidth+2; i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u256C");
            for(int i = 0; i < LFloatWidth+2; i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2563");
            Console.WriteLine();
            // A6 вывод самих данных
            foreach(CourceItem LItem in AReference) {
                Console.WriteLine("\u2551 " + 
                    LItem.Currency.Id.PadRight(LMaxLenId) + " \u2551 " + 
                    LItem.Currency.Name.PadRight(LMaxLenName) + " \u2551 "+
                    String.Format("{0,"+ LFloatWidth + ":F"+ LFloatWidthDec+ "}", LItem.Buy) + " \u2551 " +
                    String.Format("{0," + LFloatWidth + ":F" + LFloatWidthDec + "}", LItem.Sale) + " \u2551 ");
            }
            // A7 вывод завершающую рамку
            Console.Write("\u255A");
            for(int i = 0; i < ( LMaxLenId + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2569");
            for(int i = 0; i < ( LMaxLenName + 2 ); i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2569");
            for(int i = 0; i < LFloatWidth+2; i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u2569");
            for(int i = 0; i < LFloatWidth+2; i++) {
                Console.Write("\u2550");
            }
            Console.Write("\u255D");
            Console.WriteLine();
        }

        static void Main(string[] args) {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "Мои Документы"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            // I.2 устанавливаем текущим путь "Мои Документы"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(FolderMyApplication)) { // если нет
                Directory.CreateDirectory(FolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "Мои Документы" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, FolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            // 4.1 скачать файл из интернета
            if(!File.Exists(Path.Combine(LDefaultPath, LocalJSON))) {
                DownloadFileText(RemoteJSON, Path.Combine(LDefaultPath, LocalJSON));
            }
            // 4.2. загрузить данные из файла
            String LJSON = File.ReadAllText(Path.Combine(LDefaultPath, LocalJSON));
            // 4.3. контрольный вывод в консоль
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("---------------------------\n");
            //Console.WriteLine(LJSON);
            Console.WriteLine("---------------------------\n");
            // 4.5 неизвестный объект - список курса валют
            var LCourceObject = JsonConvert.DeserializeObject<dynamic>(LJSON);
            // 4.7. парсинг справочников
            List<ReferenceItem> LValutes  = RefrerenceFromJSON(LCourceObject.currencies);
            List<ReferenceItem> LRegions  = RefrerenceFromJSON(LCourceObject.regions);
            List<ReferenceItem> LCities   = RefrerenceFromJSON(LCourceObject.cities);
            List<ReferenceItem> LOrgTypes = RefrerenceFromJSON(LCourceObject.orgTypes);

            ReferencePrint("Виды организаций", LOrgTypes, ConsoleColor.Yellow);
            ReferencePrint("Регионы"         , LRegions , ConsoleColor.Gray);
            ReferencePrint("Города"          , LCities  , ConsoleColor.Red);
            ReferencePrint("Валюты"          , LValutes , ConsoleColor.Green);

            List<CourceItem> LCources = new List<CourceItem>();
            foreach(ReferenceItem LVal in LValutes) {
                CourceItem LCourceItem = new CourceItem();
                LCourceItem.Currency = LVal;
                LCourceItem.Buy      = 0;
                LCourceItem.Sale     = 0;
                LCources.Add(LCourceItem);
            }
            //ReferencePrintCource("Курсы валют:", LCources, ConsoleColor.Magenta);

            // 4.6. обрабатываем раздел "organizations"
            foreach(var LOrg in LCourceObject.organizations) {
            }


            Console.ReadLine();
        }
    }
}
