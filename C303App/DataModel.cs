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