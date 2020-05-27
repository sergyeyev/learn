using System;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using System.IO;

namespace C303App {
    public class RefItem {
        public int Id;
        public String Name;
        public RefItem() {
            Id = 0;
            Name = "";
        }
    }
    public class LBAuthor: RefItem {
    }
    public class LBBook : RefItem {
        public LBAuthor Author;
        public String ISBN;
        public LBBook() {
            Author = null;
            ISBN = "";
        }
    }
    public class LBReader : RefItem {
        public String TicketNo;
        public LBReader() {
            TicketNo = "";
        }
    }
    public class Ref : List<RefItem> {
        public virtual RefItem LoadFromJSONItem(dynamic AJSONObject) {
            RefItem LResult = new RefItem();

            return LResult;
        }
        public virtual void LoadFromFile(String AFilePath) {
            if(!File.Exists(AFilePath)) {
                return;
            }
            // очистим список
            Clear();
            // загрузка элементов из файла
            var LJSONList = JsonConvert.DeserializeObject<dynamic>( File.ReadAllText(AFilePath) );
            foreach(var LJSONItem in LJSONList) {
                Add( LoadFromJSONItem(LJSONItem) );
            }
        }
        public virtual void SaveToFile(String AFilePath) {
            File.WriteAllText(AFilePath, JsonConvert.SerializeObject(this));
        }
    }
    public class LBAuthors : Ref { 
    }
    public class LBBooks : Ref {
    }
    public class LBReaders : Ref {
    }

}