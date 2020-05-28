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
        public override String ToString() {
            return Id.ToString().PadLeft(8) + " \u2551 " + Name;
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
        public override String ToString() {
            return Id.ToString().PadLeft(8) + " \u2551 " + Name.PadRight(60) + " \u2551 " + TicketNo.PadRight(20)+ " \u2551";
        }
    }
    public class Ref : List<RefItem> {
        public int TestDataCount = 20;
        public virtual RefItem LoadFromJSONItem(dynamic AJSONObject) {
            RefItem LResult = new RefItem();

            return LResult;
        }
        public virtual void LoadFromFile(String AFilePath) {
            if(!File.Exists(AFilePath)) {
                GenTest();
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
        public virtual void GenTest() {
            for(int i = 0; i < TestDataCount; i++) {
                Add(new RefItem() { Id = i + 1,  Name = "Item " + ( i + 1 ).ToString()} );
            }
        }
    }
    public class LBAuthors : Ref {
        public override void GenTest() {
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
    }
    public class LBReaders : Ref {
        public override void GenTest() {
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
