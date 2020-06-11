namespace C320_Notepad {
    partial class FormMain {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if(disposing && ( components != null )) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.TextBoxMain = new System.Windows.Forms.TextBox();
            this.MainMenu = new System.Windows.Forms.MenuStrip();
            this.miMainFile = new System.Windows.Forms.ToolStripMenuItem();
            this.miMainEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.miEditUndo = new System.Windows.Forms.ToolStripMenuItem();
            this.miEditN001 = new System.Windows.Forms.ToolStripSeparator();
            this.miEditCut = new System.Windows.Forms.ToolStripMenuItem();
            this.miEditCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.miEditPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.miEditDelete = new System.Windows.Forms.ToolStripMenuItem();
            this.miEditN002 = new System.Windows.Forms.ToolStripSeparator();
            this.miEditSelectAll = new System.Windows.Forms.ToolStripMenuItem();
            this.miMainFormat = new System.Windows.Forms.ToolStripMenuItem();
            this.miFormatWordWrap = new System.Windows.Forms.ToolStripMenuItem();
            this.miFormatFont = new System.Windows.Forms.ToolStripMenuItem();
            this.miMainView = new System.Windows.Forms.ToolStripMenuItem();
            this.miViewStatusBar = new System.Windows.Forms.ToolStripMenuItem();
            this.miMainHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.MainStatusStrip = new System.Windows.Forms.StatusStrip();
            this.miHelpHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.miHelpAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.miFileNew = new System.Windows.Forms.ToolStripMenuItem();
            this.miFileN001 = new System.Windows.Forms.ToolStripSeparator();
            this.miFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.miFileSave = new System.Windows.Forms.ToolStripMenuItem();
            this.miFileSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.miFilePrint = new System.Windows.Forms.ToolStripMenuItem();
            this.miFileN002 = new System.Windows.Forms.ToolStripSeparator();
            this.miFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenFileDlg = new System.Windows.Forms.OpenFileDialog();
            this.SaveFileDlg = new System.Windows.Forms.SaveFileDialog();
            this.MainMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // TextBoxMain
            // 
            this.TextBoxMain.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TextBoxMain.BackColor = System.Drawing.SystemColors.Window;
            this.TextBoxMain.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TextBoxMain.Location = new System.Drawing.Point(0, 25);
            this.TextBoxMain.Multiline = true;
            this.TextBoxMain.Name = "TextBoxMain";
            this.TextBoxMain.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.TextBoxMain.Size = new System.Drawing.Size(805, 416);
            this.TextBoxMain.TabIndex = 0;
            // 
            // MainMenu
            // 
            this.MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miMainFile,
            this.miMainEdit,
            this.miMainFormat,
            this.miMainView,
            this.miMainHelp});
            this.MainMenu.Location = new System.Drawing.Point(0, 0);
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(805, 24);
            this.MainMenu.TabIndex = 1;
            this.MainMenu.Text = "menuStrip1";
            // 
            // miMainFile
            // 
            this.miMainFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miFileNew,
            this.miFileN001,
            this.miFileOpen,
            this.miFileSave,
            this.miFileSaveAs,
            this.toolStripMenuItem3,
            this.miFilePrint,
            this.miFileN002,
            this.miFileExit});
            this.miMainFile.Name = "miMainFile";
            this.miMainFile.Size = new System.Drawing.Size(37, 20);
            this.miMainFile.Text = "File";
            // 
            // miMainEdit
            // 
            this.miMainEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miEditUndo,
            this.miEditN001,
            this.miEditCut,
            this.miEditCopy,
            this.miEditPaste,
            this.miEditDelete,
            this.miEditN002,
            this.miEditSelectAll});
            this.miMainEdit.Name = "miMainEdit";
            this.miMainEdit.Size = new System.Drawing.Size(39, 20);
            this.miMainEdit.Text = "Edit";
            // 
            // miEditUndo
            // 
            this.miEditUndo.Name = "miEditUndo";
            this.miEditUndo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.miEditUndo.Size = new System.Drawing.Size(180, 22);
            this.miEditUndo.Text = "Undo";
            this.miEditUndo.Click += new System.EventHandler(this.miEditUndo_Click);
            // 
            // miEditN001
            // 
            this.miEditN001.Name = "miEditN001";
            this.miEditN001.Size = new System.Drawing.Size(177, 6);
            // 
            // miEditCut
            // 
            this.miEditCut.Name = "miEditCut";
            this.miEditCut.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Shift | System.Windows.Forms.Keys.Delete)));
            this.miEditCut.Size = new System.Drawing.Size(180, 22);
            this.miEditCut.Text = "Cut";
            this.miEditCut.Click += new System.EventHandler(this.miEditCut_Click);
            // 
            // miEditCopy
            // 
            this.miEditCopy.Name = "miEditCopy";
            this.miEditCopy.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Insert)));
            this.miEditCopy.Size = new System.Drawing.Size(180, 22);
            this.miEditCopy.Text = "Copy";
            this.miEditCopy.Click += new System.EventHandler(this.miEditCopy_Click);
            // 
            // miEditPaste
            // 
            this.miEditPaste.Name = "miEditPaste";
            this.miEditPaste.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Shift | System.Windows.Forms.Keys.Insert)));
            this.miEditPaste.Size = new System.Drawing.Size(180, 22);
            this.miEditPaste.Text = "Paste";
            this.miEditPaste.Click += new System.EventHandler(this.miEditPaste_Click);
            // 
            // miEditDelete
            // 
            this.miEditDelete.Name = "miEditDelete";
            this.miEditDelete.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Delete)));
            this.miEditDelete.Size = new System.Drawing.Size(180, 22);
            this.miEditDelete.Text = "Delete";
            this.miEditDelete.Click += new System.EventHandler(this.miEditDelete_Click);
            // 
            // miEditN002
            // 
            this.miEditN002.Name = "miEditN002";
            this.miEditN002.Size = new System.Drawing.Size(177, 6);
            // 
            // miEditSelectAll
            // 
            this.miEditSelectAll.Name = "miEditSelectAll";
            this.miEditSelectAll.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.miEditSelectAll.Size = new System.Drawing.Size(180, 22);
            this.miEditSelectAll.Text = "Select All";
            this.miEditSelectAll.Click += new System.EventHandler(this.miEditSelectAll_Click);
            // 
            // miMainFormat
            // 
            this.miMainFormat.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miFormatWordWrap,
            this.miFormatFont});
            this.miMainFormat.Name = "miMainFormat";
            this.miMainFormat.Size = new System.Drawing.Size(57, 20);
            this.miMainFormat.Text = "Format";
            // 
            // miFormatWordWrap
            // 
            this.miFormatWordWrap.Name = "miFormatWordWrap";
            this.miFormatWordWrap.Size = new System.Drawing.Size(180, 22);
            this.miFormatWordWrap.Text = "WordWrap";
            this.miFormatWordWrap.Click += new System.EventHandler(this.miFormatWordWrap_Click);
            // 
            // miFormatFont
            // 
            this.miFormatFont.Name = "miFormatFont";
            this.miFormatFont.Size = new System.Drawing.Size(180, 22);
            this.miFormatFont.Text = "Font";
            this.miFormatFont.Click += new System.EventHandler(this.miFormatFont_Click);
            // 
            // miMainView
            // 
            this.miMainView.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miViewStatusBar});
            this.miMainView.Name = "miMainView";
            this.miMainView.Size = new System.Drawing.Size(44, 20);
            this.miMainView.Text = "View";
            // 
            // miViewStatusBar
            // 
            this.miViewStatusBar.Name = "miViewStatusBar";
            this.miViewStatusBar.Size = new System.Drawing.Size(180, 22);
            this.miViewStatusBar.Text = "Status Bar";
            this.miViewStatusBar.Click += new System.EventHandler(this.miViewStatusBar_Click);
            // 
            // miMainHelp
            // 
            this.miMainHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miHelpHelp,
            this.toolStripMenuItem1,
            this.miHelpAbout});
            this.miMainHelp.Name = "miMainHelp";
            this.miMainHelp.Size = new System.Drawing.Size(44, 20);
            this.miMainHelp.Text = "Help";
            // 
            // MainStatusStrip
            // 
            this.MainStatusStrip.Location = new System.Drawing.Point(0, 441);
            this.MainStatusStrip.Name = "MainStatusStrip";
            this.MainStatusStrip.Size = new System.Drawing.Size(805, 22);
            this.MainStatusStrip.TabIndex = 2;
            this.MainStatusStrip.Text = "statusStrip1";
            // 
            // miHelpHelp
            // 
            this.miHelpHelp.Name = "miHelpHelp";
            this.miHelpHelp.Size = new System.Drawing.Size(180, 22);
            this.miHelpHelp.Text = "Help";
            this.miHelpHelp.Click += new System.EventHandler(this.miHelpHelp_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(177, 6);
            // 
            // miHelpAbout
            // 
            this.miHelpAbout.Name = "miHelpAbout";
            this.miHelpAbout.Size = new System.Drawing.Size(180, 22);
            this.miHelpAbout.Text = "About";
            this.miHelpAbout.Click += new System.EventHandler(this.miHelpAbout_Click);
            // 
            // miFileNew
            // 
            this.miFileNew.Name = "miFileNew";
            this.miFileNew.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.miFileNew.Size = new System.Drawing.Size(186, 22);
            this.miFileNew.Text = "New";
            this.miFileNew.Click += new System.EventHandler(this.miFileNew_Click);
            // 
            // miFileN001
            // 
            this.miFileN001.Name = "miFileN001";
            this.miFileN001.Size = new System.Drawing.Size(183, 6);
            // 
            // miFileOpen
            // 
            this.miFileOpen.Name = "miFileOpen";
            this.miFileOpen.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.miFileOpen.Size = new System.Drawing.Size(186, 22);
            this.miFileOpen.Text = "Open";
            this.miFileOpen.Click += new System.EventHandler(this.miFileOpen_Click);
            // 
            // miFileSave
            // 
            this.miFileSave.Name = "miFileSave";
            this.miFileSave.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.miFileSave.Size = new System.Drawing.Size(186, 22);
            this.miFileSave.Text = "Save";
            this.miFileSave.Click += new System.EventHandler(this.miFileSave_Click);
            // 
            // miFileSaveAs
            // 
            this.miFileSaveAs.Name = "miFileSaveAs";
            this.miFileSaveAs.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt) 
            | System.Windows.Forms.Keys.S)));
            this.miFileSaveAs.Size = new System.Drawing.Size(186, 22);
            this.miFileSaveAs.Text = "Save As...";
            this.miFileSaveAs.Click += new System.EventHandler(this.miFileSaveAs_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(183, 6);
            // 
            // miFilePrint
            // 
            this.miFilePrint.Name = "miFilePrint";
            this.miFilePrint.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.miFilePrint.Size = new System.Drawing.Size(186, 22);
            this.miFilePrint.Text = "Print";
            this.miFilePrint.Click += new System.EventHandler(this.miFilePrint_Click);
            // 
            // miFileN002
            // 
            this.miFileN002.Name = "miFileN002";
            this.miFileN002.Size = new System.Drawing.Size(183, 6);
            // 
            // miFileExit
            // 
            this.miFileExit.Name = "miFileExit";
            this.miFileExit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.miFileExit.Size = new System.Drawing.Size(186, 22);
            this.miFileExit.Text = "Exit";
            this.miFileExit.Click += new System.EventHandler(this.miFileExit_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(805, 463);
            this.Controls.Add(this.MainStatusStrip);
            this.Controls.Add(this.TextBoxMain);
            this.Controls.Add(this.MainMenu);
            this.MainMenuStrip = this.MainMenu;
            this.Name = "FormMain";
            this.Text = "Блокнот";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.MainMenu.ResumeLayout(false);
            this.MainMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TextBoxMain;
        private System.Windows.Forms.MenuStrip MainMenu;
        private System.Windows.Forms.ToolStripMenuItem miMainFile;
        private System.Windows.Forms.ToolStripMenuItem miMainEdit;
        private System.Windows.Forms.ToolStripMenuItem miEditUndo;
        private System.Windows.Forms.ToolStripSeparator miEditN001;
        private System.Windows.Forms.ToolStripMenuItem miEditCut;
        private System.Windows.Forms.ToolStripMenuItem miEditCopy;
        private System.Windows.Forms.ToolStripMenuItem miEditPaste;
        private System.Windows.Forms.ToolStripMenuItem miEditDelete;
        private System.Windows.Forms.ToolStripSeparator miEditN002;
        private System.Windows.Forms.ToolStripMenuItem miEditSelectAll;
        private System.Windows.Forms.ToolStripMenuItem miMainFormat;
        private System.Windows.Forms.ToolStripMenuItem miFormatWordWrap;
        private System.Windows.Forms.ToolStripMenuItem miFormatFont;
        private System.Windows.Forms.ToolStripMenuItem miMainView;
        private System.Windows.Forms.ToolStripMenuItem miViewStatusBar;
        private System.Windows.Forms.ToolStripMenuItem miMainHelp;
        private System.Windows.Forms.StatusStrip MainStatusStrip;
        private System.Windows.Forms.ToolStripMenuItem miHelpHelp;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem miHelpAbout;
        private System.Windows.Forms.ToolStripMenuItem miFileNew;
        private System.Windows.Forms.ToolStripSeparator miFileN001;
        private System.Windows.Forms.ToolStripMenuItem miFileOpen;
        private System.Windows.Forms.ToolStripMenuItem miFileSave;
        private System.Windows.Forms.ToolStripMenuItem miFileSaveAs;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem miFilePrint;
        private System.Windows.Forms.ToolStripSeparator miFileN002;
        private System.Windows.Forms.ToolStripMenuItem miFileExit;
        private System.Windows.Forms.OpenFileDialog OpenFileDlg;
        private System.Windows.Forms.SaveFileDialog SaveFileDlg;
    }
}

