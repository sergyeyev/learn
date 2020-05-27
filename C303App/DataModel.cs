using System;
using Newtonsoft.Json;

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
}