namespace MainApp
{
    partial class MainAppForm
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

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainButton = new System.Windows.Forms.Button();
            this.easel = new System.Windows.Forms.PictureBox();
            this.result = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.easel)).BeginInit();
            this.SuspendLayout();
            // 
            // mainButton
            // 
            this.mainButton.Font = new System.Drawing.Font("Comic Sans MS", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.mainButton.Location = new System.Drawing.Point(605, 144);
            this.mainButton.Name = "mainButton";
            this.mainButton.Size = new System.Drawing.Size(327, 138);
            this.mainButton.TabIndex = 0;
            this.mainButton.Text = "Click to Test!";
            this.mainButton.UseVisualStyleBackColor = true;
            this.mainButton.Click += new System.EventHandler(this.mainButton_Click);
            // 
            // easel
            // 
            this.easel.Location = new System.Drawing.Point(12, 12);
            this.easel.Name = "easel";
            this.easel.Size = new System.Drawing.Size(580, 270);
            this.easel.TabIndex = 1;
            this.easel.TabStop = false;
            this.easel.Click += new System.EventHandler(this.easel_Click);
            this.easel.Paint += new System.Windows.Forms.PaintEventHandler(this.easel_Paint);
            // 
            // result
            // 
            this.result.BackColor = System.Drawing.SystemColors.Menu;
            this.result.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.result.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.result.Location = new System.Drawing.Point(605, 12);
            this.result.Multiline = true;
            this.result.Name = "textBox1";
            this.result.Size = new System.Drawing.Size(327, 126);
            this.result.TabIndex = 3;
            this.result.Text = "Press to start fun!";
            this.result.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // MainAppForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(944, 295);
            this.Controls.Add(this.result);
            this.Controls.Add(this.easel);
            this.Controls.Add(this.mainButton);
            this.Name = "MainAppForm";
            this.Text = "MainApp by Me Myself";
            this.Load += new System.EventHandler(this.MainAppForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.easel)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void textBox1_TextChanged(object sender, System.EventArgs e)
        {
            //throw new System.NotImplementedException();
        }

        #endregion

        private System.Windows.Forms.Button mainButton;
        private System.Windows.Forms.PictureBox easel;
        private System.Windows.Forms.TextBox result;
    }
}

