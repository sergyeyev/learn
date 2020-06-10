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
    }
}

