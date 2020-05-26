using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
using Newtonsoft.Json;
using Terminal.Gui;

namespace C302SerializeJSON {
    public class AppSettings {
        public String Localization;
        public Terminal.Gui.Color Background;
        public Terminal.Gui.Color Foreground;
        public AppSettings() {
            Localization = "RU".ToUpper();
            Background   = Terminal.Gui.Color.Black;
            Foreground   = Terminal.Gui.Color.BrightGreen;
        }
        public void SaveToFile(String FileName) {
            File.WriteAllText(FileName, JsonConvert.SerializeObject(this, Formatting.Indented));
        }
        public void LoadFromFile(String FileName) {
            String LFileContent = File.ReadAllText(FileName);
            var LObject = JsonConvert.DeserializeObject<dynamic>(LFileContent);
            foreach(var LObj in LObject) {
                if(( (String)LObj.Name).ToUpper().Equals("LOCALIZATION")) Localization = LObj.Value;
                if(( (String)LObj.Name).ToUpper().Equals("BACKGROUND"  )) Background   = LObj.Value;
                if(( (String)LObj.Name).ToUpper().Equals("FOREGROUND"  )) Foreground   = LObj.Value;
            }
        }
    }
}