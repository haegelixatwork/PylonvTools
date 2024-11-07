namespace PylonLiveView
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose( bool disposing )
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.splitContainerImageView = new System.Windows.Forms.SplitContainer();
            this.splitContainerConfiguration = new System.Windows.Forms.SplitContainer();
            this.deviceListView = new System.Windows.Forms.ListView();
            this.imageListForDeviceList = new System.Windows.Forms.ImageList(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.exposureTimeSliderControl = new PylonLiveViewControl.FloatSliderUserControl();
            this.gainSliderControl = new PylonLiveViewControl.FloatSliderUserControl();
            this.heightSliderControl = new PylonLiveViewControl.IntSliderUserControl();
            this.widthSliderControl = new PylonLiveViewControl.IntSliderUserControl();
            this.pixelFormatControl = new PylonLiveViewControl.EnumerationComboBoxUserControl();
            this.testImageControl = new PylonLiveViewControl.EnumerationComboBoxUserControl();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripButtonOneShot = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonContinuousShot = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonStop = new System.Windows.Forms.ToolStripButton();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.updateDeviceListTimer = new System.Windows.Forms.Timer(this.components);
            this.panel3 = new System.Windows.Forms.Panel();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerImageView)).BeginInit();
            this.splitContainerImageView.Panel1.SuspendLayout();
            this.splitContainerImageView.Panel2.SuspendLayout();
            this.splitContainerImageView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerConfiguration)).BeginInit();
            this.splitContainerConfiguration.Panel1.SuspendLayout();
            this.splitContainerConfiguration.Panel2.SuspendLayout();
            this.splitContainerConfiguration.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.toolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainerImageView
            // 
            this.splitContainerImageView.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainerImageView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerImageView.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainerImageView.Location = new System.Drawing.Point(0, 0);
            this.splitContainerImageView.Name = "splitContainerImageView";
            // 
            // splitContainerImageView.Panel1
            // 
            this.splitContainerImageView.Panel1.Controls.Add(this.splitContainerConfiguration);
            this.splitContainerImageView.Panel1.Controls.Add(this.toolStrip);
            // 
            // splitContainerImageView.Panel2
            // 
            this.splitContainerImageView.Panel2.AutoScroll = true;
            this.splitContainerImageView.Panel2.Controls.Add(this.pictureBox);
            this.splitContainerImageView.Size = new System.Drawing.Size(912, 662);
            this.splitContainerImageView.SplitterDistance = 226;
            this.splitContainerImageView.TabIndex = 0;
            this.splitContainerImageView.TabStop = false;
            // 
            // splitContainerConfiguration
            // 
            this.splitContainerConfiguration.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainerConfiguration.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerConfiguration.Location = new System.Drawing.Point(0, 39);
            this.splitContainerConfiguration.Name = "splitContainerConfiguration";
            this.splitContainerConfiguration.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerConfiguration.Panel1
            // 
            this.splitContainerConfiguration.Panel1.Controls.Add(this.deviceListView);
            // 
            // splitContainerConfiguration.Panel2
            // 
            this.splitContainerConfiguration.Panel2.Controls.Add(this.groupBox1);
            this.splitContainerConfiguration.Panel2.Controls.Add(this.exposureTimeSliderControl);
            this.splitContainerConfiguration.Panel2.Controls.Add(this.gainSliderControl);
            this.splitContainerConfiguration.Panel2.Controls.Add(this.heightSliderControl);
            this.splitContainerConfiguration.Panel2.Controls.Add(this.widthSliderControl);
            this.splitContainerConfiguration.Panel2.Controls.Add(this.pixelFormatControl);
            this.splitContainerConfiguration.Panel2.Controls.Add(this.testImageControl);
            this.splitContainerConfiguration.Size = new System.Drawing.Size(226, 623);
            this.splitContainerConfiguration.SplitterDistance = 194;
            this.splitContainerConfiguration.TabIndex = 1;
            this.splitContainerConfiguration.TabStop = false;
            // 
            // deviceListView
            // 
            this.deviceListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.deviceListView.HideSelection = false;
            this.deviceListView.LargeImageList = this.imageListForDeviceList;
            this.deviceListView.Location = new System.Drawing.Point(0, 0);
            this.deviceListView.MultiSelect = false;
            this.deviceListView.Name = "deviceListView";
            this.deviceListView.ShowItemToolTips = true;
            this.deviceListView.Size = new System.Drawing.Size(222, 190);
            this.deviceListView.TabIndex = 0;
            this.deviceListView.UseCompatibleStateImageBehavior = false;
            this.deviceListView.View = System.Windows.Forms.View.Tile;
            this.deviceListView.SelectedIndexChanged += new System.EventHandler(this.deviceListView_SelectedIndexChanged);
            this.deviceListView.KeyDown += new System.Windows.Forms.KeyEventHandler(this.deviceListView_KeyDown);
            // 
            // imageListForDeviceList
            // 
            this.imageListForDeviceList.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageListForDeviceList.ImageSize = new System.Drawing.Size(32, 32);
            this.imageListForDeviceList.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.panel3);
            this.groupBox1.Controls.Add(this.panel2);
            this.groupBox1.Controls.Add(this.panel1);
            this.groupBox1.Location = new System.Drawing.Point(3, 318);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(221, 100);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Result";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.textBox2);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(3, 39);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(215, 23);
            this.panel2.TabIndex = 1;
            this.panel2.Visible = false;
            // 
            // textBox2
            // 
            this.textBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox2.Location = new System.Drawing.Point(100, 0);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(115, 22);
            this.textBox2.TabIndex = 1;
            this.textBox2.Text = "400";
            this.textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // label2
            // 
            this.label2.Dock = System.Windows.Forms.DockStyle.Left;
            this.label2.Location = new System.Drawing.Point(0, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 23);
            this.label2.TabIndex = 0;
            this.label2.Text = "Height";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.textBox1);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(3, 16);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(215, 23);
            this.panel1.TabIndex = 0;
            this.panel1.Visible = false;
            // 
            // textBox1
            // 
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.Location = new System.Drawing.Point(100, 0);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(115, 22);
            this.textBox1.TabIndex = 1;
            this.textBox1.Text = "400";
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // label1
            // 
            this.label1.Dock = System.Windows.Forms.DockStyle.Left;
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 23);
            this.label1.TabIndex = 0;
            this.label1.Text = "Width";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // exposureTimeSliderControl
            // 
            this.exposureTimeSliderControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.exposureTimeSliderControl.DefaultName = "N/A";
            this.exposureTimeSliderControl.Location = new System.Drawing.Point(0, 264);
            this.exposureTimeSliderControl.MinimumSize = new System.Drawing.Size(225, 50);
            this.exposureTimeSliderControl.Name = "exposureTimeSliderControl";
            this.exposureTimeSliderControl.Size = new System.Drawing.Size(229, 50);
            this.exposureTimeSliderControl.TabIndex = 6;
            // 
            // gainSliderControl
            // 
            this.gainSliderControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gainSliderControl.DefaultName = "N/A";
            this.gainSliderControl.Location = new System.Drawing.Point(0, 214);
            this.gainSliderControl.MinimumSize = new System.Drawing.Size(225, 50);
            this.gainSliderControl.Name = "gainSliderControl";
            this.gainSliderControl.Size = new System.Drawing.Size(229, 50);
            this.gainSliderControl.TabIndex = 5;
            // 
            // heightSliderControl
            // 
            this.heightSliderControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.heightSliderControl.DefaultName = "N/A";
            this.heightSliderControl.Location = new System.Drawing.Point(0, 164);
            this.heightSliderControl.MinimumSize = new System.Drawing.Size(225, 50);
            this.heightSliderControl.Name = "heightSliderControl";
            this.heightSliderControl.Size = new System.Drawing.Size(229, 50);
            this.heightSliderControl.TabIndex = 4;
            // 
            // widthSliderControl
            // 
            this.widthSliderControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.widthSliderControl.DefaultName = "N/A";
            this.widthSliderControl.Location = new System.Drawing.Point(0, 114);
            this.widthSliderControl.MinimumSize = new System.Drawing.Size(225, 50);
            this.widthSliderControl.Name = "widthSliderControl";
            this.widthSliderControl.Size = new System.Drawing.Size(229, 50);
            this.widthSliderControl.TabIndex = 3;
            // 
            // pixelFormatControl
            // 
            this.pixelFormatControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pixelFormatControl.DefaultName = "N/A";
            this.pixelFormatControl.Location = new System.Drawing.Point(12, 57);
            this.pixelFormatControl.Name = "pixelFormatControl";
            this.pixelFormatControl.Size = new System.Drawing.Size(201, 57);
            this.pixelFormatControl.TabIndex = 1;
            // 
            // testImageControl
            // 
            this.testImageControl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.testImageControl.DefaultName = "N/A";
            this.testImageControl.Location = new System.Drawing.Point(12, 0);
            this.testImageControl.Name = "testImageControl";
            this.testImageControl.Size = new System.Drawing.Size(201, 57);
            this.testImageControl.TabIndex = 0;
            // 
            // toolStrip
            // 
            this.toolStrip.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonOneShot,
            this.toolStripButtonContinuousShot,
            this.toolStripButtonStop});
            this.toolStrip.Location = new System.Drawing.Point(0, 0);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(226, 39);
            this.toolStrip.TabIndex = 0;
            this.toolStrip.Text = "toolStrip";
            // 
            // toolStripButtonOneShot
            // 
            this.toolStripButtonOneShot.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonOneShot.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonOneShot.Image")));
            this.toolStripButtonOneShot.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonOneShot.Name = "toolStripButtonOneShot";
            this.toolStripButtonOneShot.Size = new System.Drawing.Size(36, 36);
            this.toolStripButtonOneShot.Text = "One Shot";
            this.toolStripButtonOneShot.ToolTipText = "One Shot";
            this.toolStripButtonOneShot.Click += new System.EventHandler(this.toolStripButtonOneShot_Click);
            // 
            // toolStripButtonContinuousShot
            // 
            this.toolStripButtonContinuousShot.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonContinuousShot.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonContinuousShot.Image")));
            this.toolStripButtonContinuousShot.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonContinuousShot.Name = "toolStripButtonContinuousShot";
            this.toolStripButtonContinuousShot.Size = new System.Drawing.Size(36, 36);
            this.toolStripButtonContinuousShot.Text = "Continuous Shot";
            this.toolStripButtonContinuousShot.ToolTipText = "Continuous Shot";
            this.toolStripButtonContinuousShot.Click += new System.EventHandler(this.toolStripButtonContinuousShot_Click);
            // 
            // toolStripButtonStop
            // 
            this.toolStripButtonStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonStop.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonStop.Image")));
            this.toolStripButtonStop.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonStop.Name = "toolStripButtonStop";
            this.toolStripButtonStop.Size = new System.Drawing.Size(36, 36);
            this.toolStripButtonStop.Text = "Stop Grab";
            this.toolStripButtonStop.ToolTipText = "Stop Grab";
            this.toolStripButtonStop.Click += new System.EventHandler(this.toolStripButtonStop_Click);
            // 
            // pictureBox
            // 
            this.pictureBox.Location = new System.Drawing.Point(0, 0);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(480, 480);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox.TabIndex = 0;
            this.pictureBox.TabStop = false;
            // 
            // updateDeviceListTimer
            // 
            this.updateDeviceListTimer.Enabled = true;
            this.updateDeviceListTimer.Interval = 5000;
            this.updateDeviceListTimer.Tick += new System.EventHandler(this.updateDeviceListTimer_Tick);
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.textBox3);
            this.panel3.Controls.Add(this.label3);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(3, 62);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(215, 23);
            this.panel3.TabIndex = 2;
            // 
            // textBox3
            // 
            this.textBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.Location = new System.Drawing.Point(23, 0);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(192, 22);
            this.textBox3.TabIndex = 1;
            this.textBox3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label3
            // 
            this.label3.Dock = System.Windows.Forms.DockStyle.Left;
            this.label3.Location = new System.Drawing.Point(0, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 23);
            this.label3.TabIndex = 0;
            this.label3.Text = "ID";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(912, 662);
            this.Controls.Add(this.splitContainerImageView);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(800, 600);
            this.Name = "MainForm";
            this.Text = "Pylon Live View";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.splitContainerImageView.Panel1.ResumeLayout(false);
            this.splitContainerImageView.Panel1.PerformLayout();
            this.splitContainerImageView.Panel2.ResumeLayout(false);
            this.splitContainerImageView.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerImageView)).EndInit();
            this.splitContainerImageView.ResumeLayout(false);
            this.splitContainerConfiguration.Panel1.ResumeLayout(false);
            this.splitContainerConfiguration.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainerConfiguration)).EndInit();
            this.splitContainerConfiguration.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainerImageView;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripButton toolStripButtonOneShot;
        private System.Windows.Forms.ToolStripButton toolStripButtonContinuousShot;
        private System.Windows.Forms.ToolStripButton toolStripButtonStop;
        private System.Windows.Forms.SplitContainer splitContainerConfiguration;
        private System.Windows.Forms.ListView deviceListView;
        private System.Windows.Forms.Timer updateDeviceListTimer;
        private System.Windows.Forms.ImageList imageListForDeviceList;
        private PylonLiveViewControl.EnumerationComboBoxUserControl testImageControl;
        private PylonLiveViewControl.EnumerationComboBoxUserControl pixelFormatControl;
        private PylonLiveViewControl.IntSliderUserControl widthSliderControl;
        private PylonLiveViewControl.IntSliderUserControl heightSliderControl;
        private PylonLiveViewControl.FloatSliderUserControl gainSliderControl;
        private PylonLiveViewControl.FloatSliderUserControl exposureTimeSliderControl;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label3;
    }
}

