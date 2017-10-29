using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Project
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void start_btn_Click(object sender, EventArgs e)
        {
            if(!serialPort1.IsOpen)
                try
                {
                    serialPort1.Open();
                    serialPort1.Write("Start");
                }
            catch
                {
                    MessageBox.Show("Somethink wrong with your Port");
                }
        }

        private void stop_btn_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
                serialPort1.Write("Stop");
                serialPort1.Close();
        }
    }
}
