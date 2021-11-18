namespace labProj
{
    partial class fm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.buStart = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.lMines = new System.Windows.Forms.Label();
            this.cbLvl = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Controls.Add(this.buStart);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.lMines);
            this.panel1.Controls.Add(this.cbLvl);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(539, 35);
            this.panel1.TabIndex = 0;
            // 
            // buStart
            // 
            this.buStart.Dock = System.Windows.Forms.DockStyle.Left;
            this.buStart.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.buStart.Location = new System.Drawing.Point(253, 0);
            this.buStart.Name = "buStart";
            this.buStart.Size = new System.Drawing.Size(79, 35);
            this.buStart.TabIndex = 4;
            this.buStart.Text = "Начать";
            this.buStart.UseVisualStyleBackColor = true;
            this.buStart.Click += new System.EventHandler(this.buStart_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Right;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label3.Location = new System.Drawing.Point(354, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(140, 28);
            this.label3.TabIndex = 3;
            this.label3.Text = "Мин осталось";
            // 
            // lMines
            // 
            this.lMines.AutoSize = true;
            this.lMines.Dock = System.Windows.Forms.DockStyle.Right;
            this.lMines.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.lMines.ForeColor = System.Drawing.Color.Red;
            this.lMines.Location = new System.Drawing.Point(494, 0);
            this.lMines.Name = "lMines";
            this.lMines.Size = new System.Drawing.Size(45, 28);
            this.lMines.TabIndex = 2;
            this.lMines.Text = "000";
            // 
            // cbLvl
            // 
            this.cbLvl.Dock = System.Windows.Forms.DockStyle.Left;
            this.cbLvl.FormattingEnabled = true;
            this.cbLvl.Items.AddRange(new object[] {
            "Новичок",
            "Любитель",
            "Профессионал"});
            this.cbLvl.Location = new System.Drawing.Point(129, 0);
            this.cbLvl.Name = "cbLvl";
            this.cbLvl.Size = new System.Drawing.Size(124, 28);
            this.cbLvl.TabIndex = 1;
            this.cbLvl.Text = "Новичок";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Left;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Padding = new System.Windows.Forms.Padding(10, 0, 0, 10);
            this.label1.Size = new System.Drawing.Size(129, 38);
            this.label1.TabIndex = 0;
            this.label1.Text = "Сложность";
            // 
            // fm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(539, 94);
            this.Controls.Add(this.panel1);
            this.Name = "fm";
            this.Text = "Saper";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbLvl;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lMines;
        private System.Windows.Forms.Button buStart;
    }
}

