using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace C320_Notepad {
    public partial class FormMain : Form {
        public FormMain() {
            InitializeComponent();
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
            //
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
    }
}
