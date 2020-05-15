using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace C302SerializeJSON {
    // 1. класс - элемент универсального справочника
    public class ReferenceItem {
        private String FId;
        private String FName;
        public ReferenceItem() {
            FId = "";
            FName = "";
        }
        public String Id {
            get => FId;
            set { FId = value; }
        }
        public String Name {
            get => FName;
            set { FName = value; }
        }
    }

    public class CourceItem {
        public ReferenceItem Currency;
        public float Buy;
        public float Sale;
    }

    public class OrgsItem : ReferenceItem {
        private String FOldId;
        private String FAddress;
        private String FPhone;
        private String FLink;

        public String OldId {
            get => FOldId;
            set { FOldId = value; }
        }
        public String Address {
            get => FAddress;
            set { FAddress = value; }
        }
        public String Phone {
            get => FPhone;
            set { FPhone = value; }
        }
        public String Link {
            get => FLink;
            set { FLink = value; }
        }
    }

}