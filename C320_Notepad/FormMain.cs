using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace C320_Notepad {
    public partial class FormMain : Form {
        private const String CDefaultFaileName = "noname.txt";


        private String FFileName = "";
        protected void SetFileNameStatus(String AFileName, bool AChanged = false) {
            FFileName = AFileName;
            String LTopText = FFileName;
            if(AChanged) {
                LTopText = "*" + LTopText;
                StatusLabelChanged.Text = "Changed";
            } else {
                StatusLabelChanged.Text = "";
            }
            StatusLabelKeyIns.Text = "INS";
            Text = LTopText;
        }

        protected void SetFileName(String AFileName) {
            if(!AFileName.ToUpper().Equals(FFileName.ToUpper())) {
                SetFileNameStatus(AFileName);
            }
        }
        public String FileName {
            get => FFileName;
            set{ SetFileName(value); }
        }

        public FormMain() {
            InitializeComponent();
            SetFileNameStatus(CDefaultFaileName);
            StatusLabelKeyIns.Text = "";
        }

        private void FormMain_Load(object sender, EventArgs e) {
            miFormatWordWrap.Checked = TextBoxMain.WordWrap;
            miViewStatusBar.Checked = MainStatusStrip.Visible;
        }
        private void miEditUndo_Click(object sender, EventArgs e) {
            TextBoxMain.Undo();
        }

        private void miEditCut_Click(object sender, EventArgs e) {
            TextBoxMain.Cut();
        }

        private void miEditCopy_Click(object sender, EventArgs e) {
            TextBoxMain.Copy();
        }

        private void miEditPaste_Click(object sender, EventArgs e) {
            TextBoxMain.Paste();
        }

        private void miEditDelete_Click(object sender, EventArgs e) {
            TextBoxMain.SelectedText = "";
        }

        private void miEditSelectAll_Click(object sender, EventArgs e) {
            TextBoxMain.SelectAll();
        }

        private void miFormatWordWrap_Click(object sender, EventArgs e) {
            TextBoxMain.WordWrap = !TextBoxMain.WordWrap;
            miFormatWordWrap.Checked = TextBoxMain.WordWrap;
        }

        private void miFormatFont_Click(object sender, EventArgs e) {
            FontDlg.Font = TextBoxMain.Font;
            FontDlg.Color = TextBoxMain.ForeColor;
            if(FontDlg.ShowDialog() == DialogResult.OK) {
                TextBoxMain.Font = FontDlg.Font;
                TextBoxMain.ForeColor = FontDlg.Color;
            }
        }

        private void miViewStatusBar_Click(object sender, EventArgs e) {
            MainStatusStrip.Visible = !MainStatusStrip.Visible;
            miViewStatusBar.Checked = MainStatusStrip.Visible;
            if(MainStatusStrip.Visible) {
                TextBoxMain.Height = this.ClientSize.Height - MainStatusStrip.Height - MainMenu.Height;
            } else {
                TextBoxMain.Height = this.ClientSize.Height - MainMenu.Height;
            }
        }

        private void miHelpHelp_Click(object sender, EventArgs e) {
            //
        }

        private void miHelpAbout_Click(object sender, EventArgs e) {
            //
        }

        private void miFileNew_Click(object sender, EventArgs e) {

        }

        private void miFileOpen_Click(object sender, EventArgs e) {
            OpenFileDlg.Title = "Открыть текстовый файл";
            OpenFileDlg.Filter = 
                 "Текстовые файлы (*.txt)|*.txt"+                     // 1
                "|Файлы данных (*.dat)|*.dat"+                        // 2
                "|Файлы JSON (*.json)|*.json" +                       // 3
                "|Файлы XML (*.xml)|*.xml" +                          // 4
                "|Файлы JSON и XML (*.xml; *.json)|*.xml;*.json" +    // 5
                "|Все файлы (*.*)|*.*";                               // 6 
            OpenFileDlg.FilterIndex = 6;
            //OpenFileDlg.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            if(OpenFileDlg.ShowDialog() == DialogResult.OK) {
                FileName = OpenFileDlg.FileName;
                TextBoxMain.Text = File.ReadAllText(FileName, Encoding.Default);
                TextBoxMain.Modified = false;
            }
        }

        private void miFileSave_Click(object sender, EventArgs e) {
            if(FileName.ToUpper().Equals(CDefaultFaileName.ToUpper())) {
                miFileSaveAs_Click(sender, e);
            } else {
                File.WriteAllText(FileName, TextBoxMain.Text);
                TextBoxMain.Modified = false;
                SetFileNameStatus(FileName, TextBoxMain.Modified);
            }
        }

        private void miFileSaveAs_Click(object sender, EventArgs e) {
            SaveFileDlg.Title = "Сохнаить файл как...";
            SaveFileDlg.Filter =
                 "Текстовые файлы (*.txt)|*.txt" +                     // 1
                "|Все файлы (*.*)|*.*";                               // 6 
            SaveFileDlg.FilterIndex = 1;
            SaveFileDlg.FileName = this.FileName;
            //OpenFileDlg.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            if(SaveFileDlg.ShowDialog() == DialogResult.OK) {
                File.WriteAllText(SaveFileDlg.FileName, TextBoxMain.Text);
                FileName = SaveFileDlg.FileName;
                TextBoxMain.Modified = false;
                SetFileNameStatus(FileName, TextBoxMain.Modified);
            }
        }

        private void miFilePrint_Click(object sender, EventArgs e) {

        }

        private void miFileExit_Click(object sender, EventArgs e) {
            if(TextBoxMain.Modified) {
                DialogResult LResult = MessageBox.Show(
                    "Сохранить изменения в файле \""+FileName+"\"?"
                   ,"Выход из программы"
                   , MessageBoxButtons.YesNoCancel
                   ,MessageBoxIcon.Question);
                if(LResult == DialogResult.Yes) {
                    miFileSave_Click(sender, e);
                } else if(LResult == DialogResult.Cancel) {
                    return;
                }
            }
            Close();
        }

        private void TextBoxMain_TextChanged(object sender, EventArgs e) {
            SetFileNameStatus(FileName, TextBoxMain.Modified);
        }

        private void TextBoxMain_KeyUp(object sender, KeyEventArgs e) {
        }

        private void TextBoxMain_KeyPress(object sender, KeyPressEventArgs e) {
            if(e.KeyChar == (char)Keys.Insert) {
                StatusLabelKeyIns.Text = "  ";
            } else {
                StatusLabelKeyIns.Text = "INS";
            }
        }

        private void miViewColor_Click(object sender, EventArgs e) {
            ColorDlg.Color = TextBoxMain.BackColor;
            if(ColorDlg.ShowDialog() == DialogResult.OK) {
                TextBoxMain.BackColor = ColorDlg.Color;
            }
        }
    }
}
