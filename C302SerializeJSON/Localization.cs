using System;
using System.IO;
using Newtonsoft.Json;

namespace C302SerializeJSON {
    public class MessagesHolder {
        public String StrTowns;
        public String StrRegions;
        public String StrCurrencies;
        public String StrOrgTypes;
        public String StrOrgs;
        public String StrReferences;
        public String StrFile;
        public String StrFileExit;
        public MessagesHolder() {
            StrTowns = "Города";
            StrRegions = "Регионы";
            StrCurrencies = "Валюты";
            StrOrgTypes = "Типы организаций";
            StrOrgs = "Организации";
            StrFile = "Файл";
            StrFileExit = "Выход";
            StrReferences = "Справочники";
        }
        public void SaveToFile(String FileName) {
            String LFileContent = JsonConvert.SerializeObject(this, Formatting.Indented);
            File.WriteAllText(FileName, LFileContent);
        }
        public void LoadFromFile(String FileName) {
            String LFileContent = File.ReadAllText(FileName);
            var LObject = JsonConvert.DeserializeObject<dynamic>(LFileContent);
            foreach(var LObj in LObject) {
                if(((String)LObj.Name).Equals("StrTowns")) StrTowns = LObj.Value;
                if(((String)LObj.Name).Equals("StrRegions")) StrRegions = LObj.Value;
                if(((String)LObj.Name).Equals("StrCurrencies")) StrCurrencies = LObj.Value;
                if(((String)LObj.Name).Equals("StrOrgTypes")) StrOrgTypes = LObj.Value;
                if(((String)LObj.Name).Equals("StrOrgs")) StrOrgs = LObj.Value;
                if(((String)LObj.Name).Equals("StrReferences")) StrReferences = LObj.Value;
                if(((String)LObj.Name).Equals("StrFile")) StrFile = LObj.Value;
                if(((String)LObj.Name).Equals("StrFileExit")) StrFileExit = LObj.Value;
            }
        }
}

}