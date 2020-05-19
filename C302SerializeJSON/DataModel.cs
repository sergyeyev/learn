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
            return FId.PadLeft(20) + " \u2551 " + FName;
        }
    }
    public class CourceItem {
        public ReferenceItem Currency;
        public float Buy;
        public float Sale;
        public override String ToString() {
            String LResult = "";
            if(null != Currency) {
                LResult += Currency.Id.PadLeft(8);
            } else {
                LResult += " ".PadLeft(8);
            }
            LResult += " \u2551 " + Buy.ToString().PadLeft(10) + " \u2551 " + Sale.ToString().PadLeft(10);
            return LResult;
        }
    }
    public class CourcesList : List<CourceItem> {

    }

    public class OrgsItem : ReferenceItem {
        private ReferenceItem FOrgType;
        private ReferenceItem FRegion;
        private ReferenceItem FCity;
        private String FOldId;
        private String FAddress;
        private String FPhone;
        private String FLink;
        public CourcesList Cources;
        public OrgsItem() {
            Cources = new CourcesList();
        }
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
        public ReferenceItem OrgType {
            get => FOrgType;
            set { FOrgType = value; }
        }
        public ReferenceItem Region {
            get => FRegion;
            set { FRegion = value; }
        }
        public ReferenceItem City {
            get => FCity;
            set { FCity = value; }
        }
        public override String ToString() {
            String LResult = "";
            if(null != FOrgType) {
                LResult += FOrgType.Name.PadRight(10) + " \u2551 ";
            } else {
                LResult += " ".PadRight(10) + " \u2551 ";
            }
            LResult += Name.PadRight(36) + " \u2551 ";
            if(null != FRegion) {
                LResult += FRegion.Name.PadRight(24) + " ";
            } else {
                LResult += " ".PadRight(24) + " ";
            }
            if(null != FCity) {
                LResult += FCity.Name.PadRight(10) + " ";
            } else {
                LResult += " ".PadRight(10) + " ";
            }
            LResult += Address.PadRight(32) + " \u2551 " + Phone;
            return LResult;
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
        public ReferenceItem FindById(String AId) {
            ReferenceItem LResult = null;
            for(int i = 0; i<Count; i++) {
                if(this[i].Id.Equals(AId)) {
                    LResult = this[i];
                    break;
                }
            }
            return LResult;
        }
    }

    public class Organitations : List<OrgsItem> {
        private Reference FOrgTypes;
        private Reference FRegions;
        private Reference FCities;
        private Reference FCurrencies;

        public Organitations(dynamic AObject = null, 
                  Reference AOrgTypes = null, 
                  Reference ARegions = null, 
                  Reference ACities = null,
                  Reference ACurrencies = null
        ) {
            FOrgTypes = AOrgTypes;
            FRegions = ARegions;
            FCities = ACities;
            FCurrencies = ACurrencies;
            if(null != AObject) {
                LoadFromJSON(AObject);
            }
        }
        public void LoadFromJSON(dynamic AObject) {
            Clear();
            foreach(var LObj in AObject) {
                OrgsItem LItem = new OrgsItem();
                LItem.Id   = LObj.id;
                LItem.OldId = LObj.oldId;
                LItem.Name = ( (String)LObj.title );
                LItem.Address = ( (String)LObj.address );
                LItem.Phone   = ( (String)LObj.phone );
                LItem.Link    = ( (String)LObj.link );
                if(null != FOrgTypes) {
                    LItem.OrgType = FOrgTypes.FindById((String)LObj.orgType);
                }
                if(null != FRegions) {
                    LItem.Region = FRegions.FindById((String)LObj.regionId);
                }
                if(null != FCities) {
                    LItem.City = FCities.FindById((String)LObj.cityId);
                }
                LItem.Cources.Clear();
                if(null != FCurrencies) {
                    foreach(var LCource in LObj.currencies) {
                        CourceItem LCrsItem = new CourceItem();
                        LCrsItem.Currency = FCurrencies.FindById((String)LCource.Name);
                        foreach(var LCourceData in LCource.Value) {
                            if(((String)LCourceData.Name).Equals("ask")) {
                                LCrsItem.Buy = LCourceData.Value;
                            }
                            if(((String)LCourceData.Name ).Equals("bid")) {
                                LCrsItem.Sale = LCourceData.Value;
                            }
                        }
                        LItem.Cources.Add(LCrsItem);
                    }
                }
                Add(LItem);
            }
        }
    }
}