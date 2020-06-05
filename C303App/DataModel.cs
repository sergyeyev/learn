using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using System.IO;
using System.Security.Principal;

namespace C303App {
    public class RefItem {
        public int Id;
        public String Name;
        public RefItem() {
            Id = 0;
            Name = "";
        }
        public override String ToString() {
            return Id.ToString().PadLeft(8) + " \u2551 " + Name;
        }
    }
    public class LBAuthor: RefItem {
    }
    public class LBBook : RefItem {
        public RefItem Author;
        public String ISBN;
        public LBBook() {
            Author = null;
            ISBN = "";
        }
        public override String ToString() {
            String LResult = Id.ToString().PadLeft(8) + " \u2551 " + Name + " \u2551 ";
            if(null == Author) {
                LResult += " ".PadRight(25);
            } else {
                LResult += Author.Name.PadRight(25);
            }
            LResult += " \u2551 " + ISBN.PadRight(20)+ " \u2551";
            return LResult;
        }
    }
    public class LBReader : RefItem {
        public String TicketNo;
        public String Address;
        public String Phone;
        public LBReader() {
            TicketNo = "";
            Address = "";
            Phone = "";
        }
        public override String ToString() {
            return Id.ToString().PadLeft(4) + " \u2551 " + Name.PadRight(40) + " \u2551 " 
                + TicketNo.PadRight(12) + " \u2551 " + Address.PadRight(40) + " \u2551 " + Phone.PadRight(14) + " \u2551";
        }
    }
    public class Ref : List<RefItem> {
        public String FileName = "";
        public int TestDataCount = 20;

        public virtual int MaxId() {
            int LResult = 0;
            for(int i = 0; i < Count; i++) {
                if(this[i].Id > LResult) {
                    LResult = this[i].Id;
                }
            }
            return LResult;
        }

        public virtual int GenId() {
            return MaxId() + 1;
        }

        public virtual RefItem LoadFromJSONItem(dynamic AJSONObject, List<Ref> ARefs = null) {
            RefItem LResult = new RefItem();
            foreach(var LProperty in AJSONObject) {
                if(((String)LProperty.Name ).Equals("Id")) {
                    LResult.Id = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("Name")) {
                    LResult.Name = LProperty.Value;
                }
            }
            return LResult;
        }
        public virtual void LoadFromFile(String AFilePath = null, List<Ref> ARefs = null) {
            String LFilePath = AFilePath;
            if(null == LFilePath) {
                LFilePath = FileName;
            } else {
                FileName = AFilePath;
            }
            if(!File.Exists(LFilePath)) {
                GenTest(ARefs);
                return;
            }
            // очистим список
            Clear();
            // загрузка элементов из файла
            var LJSONList = JsonConvert.DeserializeObject<dynamic>( File.ReadAllText(LFilePath) );
            foreach(var LJSONItem in LJSONList) {
                Add( LoadFromJSONItem(LJSONItem, ARefs) );
            }
        }
        public virtual void SaveToFile(String AFilePath = null) {
            String LFilePath = AFilePath;
            if(null == LFilePath) {
                LFilePath = FileName;
            }
            if( (null != LFilePath) && (LFilePath.Length > 0) ){
                File.WriteAllText(LFilePath, JsonConvert.SerializeObject(this, Formatting.Indented));
            }
        }
        public virtual void GenTest(List<Ref> ARefs = null) {
            for(int i = 0; i < TestDataCount; i++) {
                Add(new RefItem() { Id = i + 1,  Name = "Item " + ( i + 1 ).ToString()} );
            }
        }
    }
    public class LBAuthors : Ref {
        public override void GenTest(List<Ref> ARefs = null) {
            String[] LCAuthors = new String[] {
                  "Джейм Фенимор Купер"
                 ,"Алана По"
                 ,"Артур Конан-Дойль"
                 ,"Беклемишев"
                 ,"Яворский"
                 ,"Агата Кристи"
                 ,"Александр Дюма"
                 ,"Достоевский"
            };
            Random Rnd = new Random();
            for(int i = 0; i < TestDataCount; i++) {
                int LIndx = Rnd.Next(0, LCAuthors.Length);
                LBAuthor LItem = new LBAuthor();
                LItem.Id = i + 1;
                LItem.Name = LCAuthors[LIndx];
                Add(LItem);
            }
        }
    }
    public class LBBooks : Ref {
        public LBBooks() {
            TestDataCount = 200;
        }
        public override RefItem LoadFromJSONItem(dynamic AJSONObject, List<Ref> ARefs = null) {
            LBBook LResult = new LBBook();
            foreach(var LProperty in AJSONObject) {
                if(( (String)LProperty.Name ).Equals("Id")) {
                    LResult.Id = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("Name")) {
                    LResult.Name = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("ISBN")) {
                    LResult.ISBN = LProperty.Value;
                }
                RefItem LAuthor = null;
                if(( (String)LProperty.Name ).Equals("Author")) {
                    int LAuthorId = 0;
                    String LAuthorName = "";
                    foreach(var LAuthorProp in LProperty.Value) {
                        if(( (String)LAuthorProp.Name ).Equals("Id")) {
                            LAuthorId = LAuthorProp.Value;
                        }
                        if(( (String)LAuthorProp.Name ).Equals("Name")) {
                            LAuthorName = LAuthorProp.Value;
                        }
                    }
                    if(null != ARefs) {
                        if(ARefs.Count > 0) {
                            foreach(RefItem LItem in ARefs[0]) {
                                if( (LItem.Id == LAuthorId) && (LItem.Name.Equals(LAuthorName) ) ) {
                                    LAuthor = LItem;
                                    break;
                                }
                            }
                            if(null == LAuthor) {
                                LAuthor = new LBAuthor();
                                LAuthor.Id = LAuthorId;
                                LAuthor.Name = LAuthorName;
                                ARefs[0].Add(LAuthor);
                            }
                        }
                    }
                }
                if(null != LAuthor) {
                    LResult.Author = LAuthor;
                }
            }
            return LResult;
        }
        public override void GenTest(List<Ref> ARefs = null) {
            String[] LCBooks = new String[] {
                  "Название Книги 1 Текст"
                 ,"Название Книги 2 Текст"
                 ,"Название Книги 3 Текст"
                 ,"Название Книги 4 Текст"
                 ,"Название Книги 5 Текст"
                 ,"Название Книги 6 Текст"
            };
            Random Rnd = new Random();
            for(int i = 0; i < TestDataCount; i++) {
                int LIndx = Rnd.Next(0, LCBooks.Length);
                LBBook LItem = new LBBook();
                LItem.Id = i + 1;
                LItem.Name = LCBooks[LIndx];
                if(null != ARefs) {
                    if(ARefs.Count > 0) {
                        int LRandomAuthorIndex = Rnd.Next(0, ARefs[0].Count);
                        LItem.Author = (LBAuthor)ARefs[0][LRandomAuthorIndex];
                    }
                }
                LItem.ISBN = "2-266-11156-6" + i.ToString();
                Add(LItem);
            }
        }
    }
    public class LBReaders : Ref {
        public override RefItem LoadFromJSONItem(dynamic AJSONObject, List<Ref> ARefs = null) {
            LBReader LResult = new LBReader();
            foreach(var LProperty in AJSONObject) {
                if(( (String)LProperty.Name ).Equals("Id")) {
                    LResult.Id = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("Name")) {
                    LResult.Name = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("TicketNo")) {
                    LResult.TicketNo = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("Address")) {
                    LResult.Address = LProperty.Value;
                }
                if(( (String)LProperty.Name ).Equals("Phone")) {
                    LResult.Phone = LProperty.Value;
                }
            }
            return LResult;
        }
        public override void GenTest(List<Ref> ARefs = null) {
            String[] LCReaders = new String[] {
                  "Иванов И.И."
                 ,"Иванов Е.А."
                 ,"Петров С.С."
                 ,"Петров И.П."
                 ,"Сидоров С.С."
                 ,"Сидоров А.В."
                 ,"Кравченко К.Е."
                 ,"Коваленко А.А."
            };
            Random Rnd = new Random();
            for(int i = 0; i < TestDataCount; i++) {
                int LIndx = Rnd.Next(0, LCReaders.Length);
                LBReader LItem = new LBReader();
                LItem.Id = i + 1;
                LItem.Name = LCReaders[LIndx];
                LItem.TicketNo = "18899500" + i.ToString().PadLeft(3).Replace(" ", "0");
                Add(LItem);
            }
        }
    }
}
