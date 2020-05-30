using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Net.Security;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.Net;
using Newtonsoft.Json;

namespace _301Sales {
    class Program {
        const String FolderMyApplication = "My Student Application";
        const String RemoteURL = "http://resources.finance.ua/ru/public/currency-cash.xml";
        const String LocalFile = "currency-cash.xml";

        private static void ReferenceFill(XmlNode ANode, List<ReferenceItem> AList) {
            // Очищаем список перед загрузкой
            AList.Clear();
            // загружаем все дочерние узлы в в список справочник
            foreach(XmlNode LNodeChild in ANode.ChildNodes) {
                // создаём элемент справочника
                ReferenceItem LReferenceItem = new ReferenceItem();
                // проверяем все аттрибуты текущего дочерниего узла
                foreach(XmlAttribute LAttributesNodeChild in LNodeChild.Attributes) {
                    if(LAttributesNodeChild.Name.Equals("id")) {
                        LReferenceItem.Id = LAttributesNodeChild.Value;
                    }
                    if(LAttributesNodeChild.Name.Equals("title")) {
                        LReferenceItem.Name = LAttributesNodeChild.Value;
                    }
                }
                // Добавляем созданный объект в список-справочник
                AList.Add(LReferenceItem);
            }
        }
        private static void ReferencePrint(String ACaption, List<ReferenceItem> AList, ConsoleColor AColor) {
            Console.ForegroundColor = AColor;
            Console.WriteLine("--------------------------------------------------------------------------");
            Console.WriteLine("| " + ACaption + ": ");
            Console.WriteLine("--------------------------------------------------------------------------");
            foreach(ReferenceItem LItem in AList) {
                Console.WriteLine("|  " + LItem.Id + "  |  " + LItem.Name);
            }
            Console.WriteLine("--------------------------------------------------------------------------");
        }

        private static ReferenceItem ReferenceGet(List<ReferenceItem> AList, String aId) {
            ReferenceItem LResult = null;
            foreach(ReferenceItem LItem in AList) {
                if(LItem.Id.Equals(aId)) {
                    LResult = LItem;
                    break;
                }
            }
            return LResult;
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

            // 12 скачать файл из инетернета
            WebRequest RQ = WebRequest.Create(RemoteURL);
            RQ.Credentials = CredentialCache.DefaultCredentials;
            WebResponse WR = RQ.GetResponse();
            Stream DS = WR.GetResponseStream();
            StreamWriter fileSaver = new StreamWriter(Path.Combine(LDefaultPath, LocalFile));
            StreamReader reader = new StreamReader(DS);
            string Answer = reader.ReadToEnd();
            fileSaver.Write(Answer);
            fileSaver.Close();            //
            reader.Close();
            WR.Close();
            Console.WriteLine("file was downloded....\n");
            // 13. ОБработка файла
            XmlDocument LXMLDoc = new XmlDocument();
            LXMLDoc.Load(Path.Combine(LDefaultPath, LocalFile));
            XmlElement LRoot = LXMLDoc.DocumentElement;

            List<ReferenceItem> LOrgTypes   = new List<ReferenceItem>();
            List<ReferenceItem> LCurrencies = new List<ReferenceItem>();
            List<ReferenceItem> LRegions    = new List<ReferenceItem>();
            List<ReferenceItem> LCities     = new List<ReferenceItem>();
            // 14. Парсинг справочников
            foreach(XmlNode LNode in LRoot) {
                if(LNode.Name.Equals("org_types" )) ReferenceFill(LNode, LOrgTypes); 
                if(LNode.Name.Equals("currencies")) ReferenceFill(LNode, LCurrencies);
                if(LNode.Name.Equals("regions"   )) ReferenceFill(LNode, LRegions);
                if(LNode.Name.Equals("cities"    )) ReferenceFill(LNode, LCities);
            }
            // 15. контрольный вывод
            ReferencePrint("Типы организаций", LOrgTypes  , ConsoleColor.Red    );
            ReferencePrint("Валюты"          , LCurrencies, ConsoleColor.Green  );
            ReferencePrint("Регионы"         , LRegions   , ConsoleColor.Cyan   );
            ReferencePrint("Города"          , LCities    , ConsoleColor.Magenta);

            // создаём списки организаций
            List<OrgsItem> LOrgs = new List<OrgsItem>();
            // 16. грузим курсы валют
            foreach(XmlNode LNodeOrganizations in LRoot) {
                if(LNodeOrganizations.Name.Equals("organizations")) {
                    // загружаем все дочерние узлы
                    foreach(XmlNode LNodeChild in LNodeOrganizations.ChildNodes) {
                        OrgsItem LOrgItem = new OrgsItem();
                        // проверяем все аттрибуты текущего дочерниего узла
                        foreach(XmlAttribute LAttributesNodeChild in LNodeChild.Attributes) {
                            if(LAttributesNodeChild.Name.Equals("id")) {
                                LOrgItem.Id = LAttributesNodeChild.Value;
                            }
                            if(LAttributesNodeChild.Name.Equals("oldid")) {
                                LOrgItem.OldId = LAttributesNodeChild.Value;
                            }
                            if(LAttributesNodeChild.Name.Equals("org_type")) {
                                LOrgItem.OrgType = ReferenceGet(LOrgTypes, LAttributesNodeChild.Value);
                            }
                        }
                        foreach(XmlNode LNode2Level in LNodeChild.ChildNodes) {
                            if(LNode2Level.Name.Equals("title")) {
                                LOrgItem.Name = LNode2Level.Value;
                            }
                            if(LNode2Level.Name.Equals("address")) {
                                LOrgItem.Address = LNode2Level.Value;
                            }
                            if(LNode2Level.Name.Equals("phone")) {
                                LOrgItem.Phone = LNode2Level.Value;
                            }
                            if(LNode2Level.Name.Equals("city id")) {
                                LOrgItem.City = ReferenceGet(LCities, LNode2Level.Value);
                            }
                            if(LNode2Level.Name.Equals("region id")) {
                                LOrgItem.Region = ReferenceGet(LRegions, LNode2Level.Value);
                            }
                        }
                        LOrgs.Add(LOrgItem);
                    }
                }
            }
            // вывод списка организаций
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("---------------------------------------------");
            foreach(OrgsItem LO in LOrgs) {
                Console.WriteLine("  " + LO.Id + "  " + LO.OrgType.Name + " " + LO.Name + " " + LO.Address);
            }


            Console.ReadLine();
        }
    }
}
