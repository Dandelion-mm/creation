using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace calc2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        bool isFIRST = true;
        decimal value1 = 0;
        decimal count = 0;

        private void btnNumber_Click(object sender, EventArgs e)
        {

            if (symbol != 四則演算の記号.NON && isFIRST) {
                value1 = Convert.ToDecimal(txtDisplay.Text);
                txtDisplay.Text = "";
                isFIRST = false;
            }
            if (count == 0)
            {
                String text = txtDisplay.Text + ((Button)sender).Text;

                decimal d = Convert.ToDecimal(text);

                String text2 = d.ToString();

                txtDisplay.Text = text2;
            }
            if(count == 1)
            {
                txtDisplay.Text = "";

                count = 0;

                String text = txtDisplay.Text + ((Button)sender).Text;

                decimal d = Convert.ToDecimal(text);

                String text2 = d.ToString();

                txtDisplay.Text = text2;
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtDisplay.Text = "0";
        }

        private void btnDot_Click(object sender, EventArgs e)
        {
            if (count == 0)
            {
                if (txtDisplay.Text.IndexOf(".") >= 0)
                {
                    return;
                }
                txtDisplay.Text = txtDisplay.Text + ".";
            }
            if (count == 1)
            {
                txtDisplay.Text = "0.";
                count = 0;
            }
        }

        enum 四則演算の記号 {
            NON, ADD, SUB, MUL, DIV
        };

        四則演算の記号 symbol = 四則演算の記号.NON;

        private void btnAdd_Click(object sender, EventArgs e)
        {
            symbol = 四則演算の記号.ADD;
            isFIRST = true;
        }

        private void btnSub_Click(object sender, EventArgs e)
        {
            symbol = 四則演算の記号.SUB;
            isFIRST = true;
        }

        private void btnMul_Click(object sender, EventArgs e)
        {
            symbol = 四則演算の記号.MUL;
            isFIRST = true;
        }

        private void btnDiv_Click(object sender, EventArgs e)
        {
            symbol = 四則演算の記号.DIV;
            isFIRST = true;
        }

        private void btnCalc_Click(object sender, EventArgs e)
        {
            decimal value2 = Convert.ToDecimal(txtDisplay.Text);
            decimal result = 0;

            switch (symbol)
            {
                case 四則演算の記号.ADD:
                    result = value1 + value2;
                    break;
                case 四則演算の記号.SUB:
                    result = value1 - value2;
                    break;
                case 四則演算の記号.MUL:
                    result = value1 * value2;
                    break;
                case 四則演算の記号.DIV:
                    result = value1 / value2;
                    break;
            }

            count = 1;
            txtDisplay.Text = result.ToString();

        }
    }
}
