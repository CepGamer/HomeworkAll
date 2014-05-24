namespace LocalizationApp
{
    partial class ElfsBuilderForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void ChangeLanguage()
        {
            string locale = "en";
            switch (System.Threading.Thread.CurrentThread.CurrentCulture.EnglishName)
            {
                case "Russian (Russia)":
                    locale = "en";
                    break;
                case "English":
                    locale = "ru-RU";
                    break;
                default:
                    locale = "en";
                    break;
            }
            System.Threading.Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo(locale, false);
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo(locale, false);
            Renew();
        }

        private void ApplyRes(System.Windows.Forms.Control control, System.ComponentModel.ComponentResourceManager mgr)
        {
            mgr.ApplyResources(control, control.Name);
            foreach (System.Windows.Forms.Control item in control.Controls)
            {
                ApplyRes(item, mgr);
            }
            if(control is System.Windows.Forms.ComboBox)
            {
                System.Windows.Forms.ComboBox item = control as System.Windows.Forms.ComboBox;
                for (int i = 0; i < item.Items.Count; i++ )
                {
                    string appendix = i.ToString();
                    if (i == 0)
                        appendix = "";
                    try
                    {
                        item.Items[i] = mgr.GetString(item.Name + ".Items" + appendix);
                    }
                    catch (System.ArgumentNullException)
                    {
                    }
                }
            }
            if(control is System.Windows.Forms.ListBox)
            {
                System.Windows.Forms.ListBox item = control as System.Windows.Forms.ListBox;
                for (int i = 0; i < item.Items.Count; i++)
                {
                    string appendix = i.ToString();
                    if (i == 0)
                        appendix = "";
                    try
                    {
                        item.Items[i] = mgr.GetString(item.Name + ".Items" + appendix);
                    }
                    catch (System.ArgumentNullException)
                    {
                    }
                }
            }
        }

        private void Renew()
        {
            System.ComponentModel.ComponentResourceManager resources = 
                new System.ComponentModel.ComponentResourceManager(typeof(ElfsBuilderForm));
            ApplyRes(this, resources);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ElfsBuilderForm));
            this.ButtonOK = new System.Windows.Forms.Button();
            this.ButtonCancel = new System.Windows.Forms.Button();
            this.ChangeLanguageButton = new System.Windows.Forms.Button();
            this.NameLabel = new System.Windows.Forms.Label();
            this.NameTextBox = new System.Windows.Forms.TextBox();
            this.SurnameLabel = new System.Windows.Forms.Label();
            this.SurnameTextbox = new System.Windows.Forms.TextBox();
            this.GenderLabel = new System.Windows.Forms.Label();
            this.GenderCombobox = new System.Windows.Forms.ComboBox();
            this.AgeLabel = new System.Windows.Forms.Label();
            this.AgeUpDown = new System.Windows.Forms.NumericUpDown();
            this.BodyBox = new System.Windows.Forms.GroupBox();
            this.HeightUpdown = new System.Windows.Forms.NumericUpDown();
            this.HeightLabel = new System.Windows.Forms.Label();
            this.SkinCombobox = new System.Windows.Forms.ComboBox();
            this.SkinLabel = new System.Windows.Forms.Label();
            this.BuildCombobox = new System.Windows.Forms.ComboBox();
            this.BuildLabel = new System.Windows.Forms.Label();
            this.GeneralBox = new System.Windows.Forms.GroupBox();
            this.LegsBox = new System.Windows.Forms.GroupBox();
            this.BuildLegsCombobox = new System.Windows.Forms.ComboBox();
            this.BuildLegsLabel = new System.Windows.Forms.Label();
            this.PantsCombobox = new System.Windows.Forms.ComboBox();
            this.PantsLabel = new System.Windows.Forms.Label();
            this.CanChecklistbox = new System.Windows.Forms.CheckedListBox();
            ((System.ComponentModel.ISupportInitialize)(this.AgeUpDown)).BeginInit();
            this.BodyBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.HeightUpdown)).BeginInit();
            this.GeneralBox.SuspendLayout();
            this.LegsBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // ButtonOK
            // 
            resources.ApplyResources(this.ButtonOK, "ButtonOK");
            this.ButtonOK.Name = "ButtonOK";
            this.ButtonOK.UseVisualStyleBackColor = true;
            this.ButtonOK.Click += new System.EventHandler(this.OKButton_Click);
            // 
            // ButtonCancel
            // 
            resources.ApplyResources(this.ButtonCancel, "ButtonCancel");
            this.ButtonCancel.Name = "ButtonCancel";
            this.ButtonCancel.UseVisualStyleBackColor = true;
            this.ButtonCancel.Click += new System.EventHandler(this.ButtonCancel_Click);
            // 
            // ChangeLanguageButton
            // 
            resources.ApplyResources(this.ChangeLanguageButton, "ChangeLanguageButton");
            this.ChangeLanguageButton.BackColor = System.Drawing.SystemColors.Control;
            this.ChangeLanguageButton.Name = "ChangeLanguageButton";
            this.ChangeLanguageButton.UseVisualStyleBackColor = false;
            this.ChangeLanguageButton.Click += new System.EventHandler(this.ChangeLanguageButton_Click);
            // 
            // NameLabel
            // 
            resources.ApplyResources(this.NameLabel, "NameLabel");
            this.NameLabel.Name = "NameLabel";
            // 
            // NameTextBox
            // 
            resources.ApplyResources(this.NameTextBox, "NameTextBox");
            this.NameTextBox.ForeColor = System.Drawing.SystemColors.GrayText;
            this.NameTextBox.Name = "NameTextBox";
            // 
            // SurnameLabel
            // 
            resources.ApplyResources(this.SurnameLabel, "SurnameLabel");
            this.SurnameLabel.Name = "SurnameLabel";
            // 
            // SurnameTextbox
            // 
            resources.ApplyResources(this.SurnameTextbox, "SurnameTextbox");
            this.SurnameTextbox.ForeColor = System.Drawing.SystemColors.GrayText;
            this.SurnameTextbox.Name = "SurnameTextbox";
            // 
            // GenderLabel
            // 
            resources.ApplyResources(this.GenderLabel, "GenderLabel");
            this.GenderLabel.Name = "GenderLabel";
            // 
            // GenderCombobox
            // 
            resources.ApplyResources(this.GenderCombobox, "GenderCombobox");
            this.GenderCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.GenderCombobox.FormattingEnabled = true;
            this.GenderCombobox.Items.AddRange(new object[] {
            resources.GetString("GenderCombobox.Items"),
            resources.GetString("GenderCombobox.Items1")});
            this.GenderCombobox.Name = "GenderCombobox";
            // 
            // AgeLabel
            // 
            resources.ApplyResources(this.AgeLabel, "AgeLabel");
            this.AgeLabel.Name = "AgeLabel";
            // 
            // AgeUpDown
            // 
            resources.ApplyResources(this.AgeUpDown, "AgeUpDown");
            this.AgeUpDown.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.AgeUpDown.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.AgeUpDown.Name = "AgeUpDown";
            this.AgeUpDown.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // BodyBox
            // 
            resources.ApplyResources(this.BodyBox, "BodyBox");
            this.BodyBox.Controls.Add(this.HeightUpdown);
            this.BodyBox.Controls.Add(this.HeightLabel);
            this.BodyBox.Controls.Add(this.SkinCombobox);
            this.BodyBox.Controls.Add(this.SkinLabel);
            this.BodyBox.Controls.Add(this.BuildCombobox);
            this.BodyBox.Controls.Add(this.BuildLabel);
            this.BodyBox.Name = "BodyBox";
            this.BodyBox.TabStop = false;
            // 
            // HeightUpdown
            // 
            resources.ApplyResources(this.HeightUpdown, "HeightUpdown");
            this.HeightUpdown.Maximum = new decimal(new int[] {
            250,
            0,
            0,
            0});
            this.HeightUpdown.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.HeightUpdown.Name = "HeightUpdown";
            this.HeightUpdown.Tag = "cm";
            this.HeightUpdown.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // HeightLabel
            // 
            resources.ApplyResources(this.HeightLabel, "HeightLabel");
            this.HeightLabel.Name = "HeightLabel";
            // 
            // SkinCombobox
            // 
            resources.ApplyResources(this.SkinCombobox, "SkinCombobox");
            this.SkinCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.SkinCombobox.FormattingEnabled = true;
            this.SkinCombobox.Items.AddRange(new object[] {
            resources.GetString("SkinCombobox.Items"),
            resources.GetString("SkinCombobox.Items1"),
            resources.GetString("SkinCombobox.Items2"),
            resources.GetString("SkinCombobox.Items3")});
            this.SkinCombobox.Name = "SkinCombobox";
            // 
            // SkinLabel
            // 
            resources.ApplyResources(this.SkinLabel, "SkinLabel");
            this.SkinLabel.Name = "SkinLabel";
            // 
            // BuildCombobox
            // 
            resources.ApplyResources(this.BuildCombobox, "BuildCombobox");
            this.BuildCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.BuildCombobox.FormattingEnabled = true;
            this.BuildCombobox.Items.AddRange(new object[] {
            resources.GetString("BuildCombobox.Items"),
            resources.GetString("BuildCombobox.Items1"),
            resources.GetString("BuildCombobox.Items2")});
            this.BuildCombobox.Name = "BuildCombobox";
            // 
            // BuildLabel
            // 
            resources.ApplyResources(this.BuildLabel, "BuildLabel");
            this.BuildLabel.Name = "BuildLabel";
            // 
            // GeneralBox
            // 
            resources.ApplyResources(this.GeneralBox, "GeneralBox");
            this.GeneralBox.Controls.Add(this.NameTextBox);
            this.GeneralBox.Controls.Add(this.NameLabel);
            this.GeneralBox.Controls.Add(this.AgeUpDown);
            this.GeneralBox.Controls.Add(this.SurnameLabel);
            this.GeneralBox.Controls.Add(this.AgeLabel);
            this.GeneralBox.Controls.Add(this.SurnameTextbox);
            this.GeneralBox.Controls.Add(this.GenderCombobox);
            this.GeneralBox.Controls.Add(this.GenderLabel);
            this.GeneralBox.Name = "GeneralBox";
            this.GeneralBox.TabStop = false;
            // 
            // LegsBox
            // 
            resources.ApplyResources(this.LegsBox, "LegsBox");
            this.LegsBox.Controls.Add(this.BuildLegsCombobox);
            this.LegsBox.Controls.Add(this.BuildLegsLabel);
            this.LegsBox.Controls.Add(this.PantsCombobox);
            this.LegsBox.Controls.Add(this.PantsLabel);
            this.LegsBox.Name = "LegsBox";
            this.LegsBox.TabStop = false;
            // 
            // BuildLegsCombobox
            // 
            resources.ApplyResources(this.BuildLegsCombobox, "BuildLegsCombobox");
            this.BuildLegsCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.BuildLegsCombobox.FormattingEnabled = true;
            this.BuildLegsCombobox.Items.AddRange(new object[] {
            resources.GetString("BuildLegsCombobox.Items"),
            resources.GetString("BuildLegsCombobox.Items1"),
            resources.GetString("BuildLegsCombobox.Items2")});
            this.BuildLegsCombobox.Name = "BuildLegsCombobox";
            // 
            // BuildLegsLabel
            // 
            resources.ApplyResources(this.BuildLegsLabel, "BuildLegsLabel");
            this.BuildLegsLabel.Name = "BuildLegsLabel";
            // 
            // PantsCombobox
            // 
            resources.ApplyResources(this.PantsCombobox, "PantsCombobox");
            this.PantsCombobox.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.PantsCombobox.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
            this.PantsCombobox.FormattingEnabled = true;
            this.PantsCombobox.Items.AddRange(new object[] {
            resources.GetString("PantsCombobox.Items"),
            resources.GetString("PantsCombobox.Items1"),
            resources.GetString("PantsCombobox.Items2"),
            resources.GetString("PantsCombobox.Items3"),
            resources.GetString("PantsCombobox.Items4"),
            resources.GetString("PantsCombobox.Items5"),
            resources.GetString("PantsCombobox.Items6"),
            resources.GetString("PantsCombobox.Items7")});
            this.PantsCombobox.Name = "PantsCombobox";
            // 
            // PantsLabel
            // 
            resources.ApplyResources(this.PantsLabel, "PantsLabel");
            this.PantsLabel.Name = "PantsLabel";
            // 
            // CanChecklistbox
            // 
            resources.ApplyResources(this.CanChecklistbox, "CanChecklistbox");
            this.CanChecklistbox.BackColor = System.Drawing.SystemColors.Control;
            this.CanChecklistbox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.CanChecklistbox.CheckOnClick = true;
            this.CanChecklistbox.FormattingEnabled = true;
            this.CanChecklistbox.Items.AddRange(new object[] {
            resources.GetString("CanChecklistbox.Items"),
            resources.GetString("CanChecklistbox.Items1"),
            resources.GetString("CanChecklistbox.Items2")});
            this.CanChecklistbox.Name = "CanChecklistbox";
            // 
            // ElfsBuilderForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.CanChecklistbox);
            this.Controls.Add(this.LegsBox);
            this.Controls.Add(this.GeneralBox);
            this.Controls.Add(this.BodyBox);
            this.Controls.Add(this.ChangeLanguageButton);
            this.Controls.Add(this.ButtonCancel);
            this.Controls.Add(this.ButtonOK);
            this.Name = "ElfsBuilderForm";
            ((System.ComponentModel.ISupportInitialize)(this.AgeUpDown)).EndInit();
            this.BodyBox.ResumeLayout(false);
            this.BodyBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.HeightUpdown)).EndInit();
            this.GeneralBox.ResumeLayout(false);
            this.GeneralBox.PerformLayout();
            this.LegsBox.ResumeLayout(false);
            this.LegsBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ButtonOK;
        private System.Windows.Forms.Button ButtonCancel;
        private System.Windows.Forms.Button ChangeLanguageButton;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.TextBox NameTextBox;
        private System.Windows.Forms.Label SurnameLabel;
        private System.Windows.Forms.TextBox SurnameTextbox;
        private System.Windows.Forms.Label GenderLabel;
        private System.Windows.Forms.ComboBox GenderCombobox;
        private System.Windows.Forms.Label AgeLabel;
        private System.Windows.Forms.NumericUpDown AgeUpDown;
        private System.Windows.Forms.GroupBox BodyBox;
        private System.Windows.Forms.GroupBox GeneralBox;
        private System.Windows.Forms.ComboBox BuildCombobox;
        private System.Windows.Forms.Label BuildLabel;
        private System.Windows.Forms.ComboBox SkinCombobox;
        private System.Windows.Forms.Label SkinLabel;
        private System.Windows.Forms.NumericUpDown HeightUpdown;
        private System.Windows.Forms.Label HeightLabel;
        private System.Windows.Forms.GroupBox LegsBox;
        private System.Windows.Forms.ComboBox PantsCombobox;
        private System.Windows.Forms.Label PantsLabel;
        private System.Windows.Forms.ComboBox BuildLegsCombobox;
        private System.Windows.Forms.Label BuildLegsLabel;
        private System.Windows.Forms.CheckedListBox CanChecklistbox;
    }
}

