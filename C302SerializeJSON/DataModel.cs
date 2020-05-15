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
        public override String ToString() {
            return FId.PadLeft(40) + ". " + FName;
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
    public class Reference : List<ReferenceItem> {
        public Reference(dynamic AObject = null) {
            if(null != AObject) {
                LoadFromJSON(AObject);
            }
        }
        public void LoadFromJSON(dynamic AObject) {
            Clear();
            foreach(var LObj in AObject) {
                ReferenceItem LItem = new ReferenceItem();
                LItem.Id   = LObj.Name;
                LItem.Name = ( (String)LObj.Value );
                Add(LItem);
            }
        }
        public String[] ToStringArray() {
            String[] LResult = new String[Count];
            for(int i =0; i<Count; i++) {
                LResult[i] = this[i].Id.ToString() + ". " + this[i].Name;
            }
            return LResult;
        }
    }
}