using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Net.Security;
using System.Text;
using System.Net;
using Newtonsoft.Json;
using NStack;
using Terminal.Gui;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Linq;

namespace C303App {
    class Program {
        // поля для модели данных
        public static String AppDefaultPathData;

        public static String CheckFoldersSettings() {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "AppData"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
            // I.2 устанавливаем текущим путь "AppData"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(Consts.FolderMyApplication)) { // если нет
                Directory.CreateDirectory(Consts.FolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "AppData" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, Consts.FolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            return LDefaultPath;
        }
        public static String CheckFoldersData() {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "Мои Документы"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            // I.2 устанавливаем текущим путь "Мои Документы"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(Consts.FolderMyApplication)) { // если нет
                Directory.CreateDirectory(Consts.FolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "Мои Документы" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, Consts.FolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.5 создаём попдпапку с локализацие приложения "Мои Документы" \ FolderMyApplication \ CFolderLocal
            if(!Directory.Exists(Consts.FolderLocal)) { // если нет
                Directory.CreateDirectory(Consts.FolderLocal); // создаём эту папку
            }
            return LDefaultPath;
        }
        static void Main(string[] args) {
            // II.1. проверка рабочего каталога приложения
            AppDefaultPathData = CheckFoldersData();


            return;
        }
    }
}
