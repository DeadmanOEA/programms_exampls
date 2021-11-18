using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace labProj
{
    public partial class fm : Form
    {
        private PictureBox[,] pb;
        private int[,] MinesControl;
        private int inCols;
        private int inRows;
        private int gSt;

        public fm()
        {
            InitializeComponent();
            gSt = 0;
        }

        private void buStart_Click(object sender, EventArgs e)
        {
            if (gSt != 0)
            {
                for (int i = 0; i < inRows; i++)
                {
                    for (int j = 0; j < inCols; j++)
                    {
                        this.Controls.Remove(pb[i, j]);
                    }
                }
                Array.Clear(pb, 0, pb.Length);
                Array.Clear(MinesControl, 0, MinesControl.Length);
            }

            gSt = 1;

            var x = cbLvl.Text;

            var rnd = new Random();

            int xcols = 0, xlines = 0, xmines = 0;

            int xcoord, ycoord, x0height, elwidth;

            int xheight, xwidth;

            string tag;

            int[] minesMas;

            x0height = 35;//стандартные значения
            xcoord = 0;
            ycoord = 35;
            elwidth = 57;
            //данные сложности
            if (x == "Новичок")
            {
                xcols = 9;
                xlines = 9;
                xmines = 10;
            }

            if (x == "Любитель")
            {
                xcols = 16;
                xlines = 16;
                xmines = 40;
            }

            if (x == "Профессионал")
            {
                xcols = 30;
                xlines = 16;
                xmines = 99;
            }
            
            //учет параметров
            xheight = elwidth * xlines + x0height;
            xwidth = elwidth * xcols;
            minesMas = new int[xmines];

            this.Height = xheight + 47;
            this.Width = xwidth + 17;

            pb = new PictureBox[xlines, xcols];
            MinesControl = new int[xlines, xcols];

            for (int i = 0; i < xlines; i++)
            {
                for (int j = 0; j < xcols; j++)
                {
                    MinesControl[i,j] = 0;
                }
            }

            inCols = xcols;
            inRows = xlines;

            lMines.Text = xmines.ToString();
            //генерация мин
            for (int i = 0; i < xmines; i++)
            {
                int nMine = rnd.Next(xcols * xlines);

                bool add = true;

                for (int j = 0; j < i; j++)
                {
                    if (nMine == minesMas[j])
                    {
                        add = false;
                        i--;
                    }
                }

                if (add == true)
                {
                    minesMas[i] = nMine;
                }
            }
            //создание полей
            tag = "0";
            for (int i = 0; i < xlines; i++)
            {
                for (int j = 0; j < xcols; j++)
                {
                    tag = "0";
                    for (int k = 0; k < minesMas.Length; k++)
                    {
                        if ((i * inCols + (j + 1)) == minesMas[k])
                        {
                            tag = "10";
                            MinesControl[i, j] = 1;

                            CreateEl(xcoord, ycoord, tag, (elwidth - 2), i, j);
                        }
                    }

                    xcoord += elwidth;
                }
                xcoord = 0;
                ycoord += elwidth;

            }
            ycoord = 35;
            xcoord = 0;
            for (int i = 0; i < xlines; i++)
            {
                for (int j = 0; j < xcols; j++)
                {
                    tag = "0";
                    for (int k = 0; k < minesMas.Length; k++)
                    {
                        if ((i * inCols + (j + 1)) == minesMas[k])
                        {
                            tag = "10";
                            MinesControl[i, j] = 1;
                        }
                    }


                    if (tag != "10")
                    {
                        int numM = 0;
                        int left = 1, right = 1, up = 1, down = 1;
                        if (j == 0) left = 0;
                        if (j == (inCols - 1)) right = 0;
                        if (i == 0) up = 0;
                        if (i == (inRows - 1)) down = 0;

                        if (up != 0)
                        {
                            if (left != 0)
                                if (MinesControl[i - 1, j - 1] == 1) numM++;
                            if (MinesControl[i - 1, j] == 1) numM++;
                            if (right != 0)
                                if (MinesControl[i - 1, j + 1] == 1) numM++;
                        }
                        {
                            if (left != 0)
                                if (MinesControl[i, j - 1] == 1) numM++;
                            if (right != 0)
                                if (MinesControl[i, j + 1] == 1) numM++;
                        }
                        if (down != 0)
                        {
                            if (left != 0)
                                if (MinesControl[i + 1, j - 1] == 1) numM++;
                            if (MinesControl[i + 1, j] == 1) numM++;
                            if (right != 0)
                                if (MinesControl[i + 1, j + 1] == 1) numM++;
                        }
                        tag = numM.ToString();

                        CreateEl(xcoord, ycoord, tag, (elwidth - 2), i, j);
                    }

                    xcoord += elwidth;
                }
                
                xcoord = 0;
                ycoord += elwidth;
            }
        }

        private void CreateEl(int xel, int yel, string tag, int elsize, int o, int p)//создание элемента pictureBox
        {
            pb[o, p] = new PictureBox();
            pb[o, p].Location = new Point(xel + 1, yel + 1);
            pb[o, p].Width = elsize;
            pb[o, p].Height = elsize;
            pb[o, p].Anchor = (AnchorStyles.Top | AnchorStyles.Left);
            pb[o, p].Tag = tag;
            pb[o, p].Image = Properties.Resources.def;
            pb[o, p].Image.Tag = "1";
            pb[o, p].SizeMode = PictureBoxSizeMode.Zoom;
            pb[o, p].MouseDown += Fm_MouseDown;
            pb[o, p].Name = "PB" + o.ToString() + "_" + p.ToString();
            this.Controls.Add(pb[o, p]);
        }

        private void Fm_MouseDown(object sender, MouseEventArgs e)//обработка событий нажатия на pictureBox
        {
            if (e.Button == MouseButtons.Left)
            {
                if(((PictureBox)sender).Tag.ToString() == "10")
                {
                    ((PictureBox)sender).Image = Properties.Resources.mineLose;
                    ((PictureBox)sender).Image.Tag = "0";
                    Lose(sender);
                }
                else 
                {
                    MakePic(sender);
                }
            }

            if (e.Button == MouseButtons.Right)
            {
                if(((PictureBox)sender).Image.Tag.ToString() == "2")
                {
                    ((PictureBox)sender).Image = Properties.Resources.def;
                    ((PictureBox)sender).Image.Tag = "1";
                    int num = Int32.Parse(lMines.Text);
                    num++;
                    lMines.Text = num.ToString();
                }
                else if (((PictureBox)sender).Image.Tag.ToString() == "3"){} 
                else
                {
                    ((PictureBox)sender).Image = Properties.Resources.flag;
                    ((PictureBox)sender).Image.Tag = "2";
                    int num = Int32.Parse(lMines.Text);
                    num--;
                    lMines.Text = num.ToString();
                    if(num == 0) Win();
                }
            }
        }

        private void MakePic(object sender)
        {
            switch (((PictureBox)sender).Tag.ToString())
            {
                case "0":
                    if (((PictureBox)sender).Image.Tag != "3")
                    {
                        ((PictureBox)sender).Image = Properties.Resources.empty;
                        ((PictureBox)sender).Image.Tag = "3";
                        string xStr = ((PictureBox)sender).Name.ToString();
                        int xLengs = xStr.Length;
                        string str1 = "", str2 = "";
                        int nn = 1;
                        for (int i = 2; i < xLengs; i++)
                        {
                            if (xStr[i] == '_')
                            {
                                i++;
                                nn = 2;
                            }
                            if (nn == 2)
                                str2 += xStr[i];
                            else
                                str1 += xStr[i];
                        }
                        int n1 = Int32.Parse(str1);
                        int n2 = Int32.Parse(str2);

                        int up = 1, down = 1, left = 1, right = 1;

                        if (n1 == 0)
                            up = 0;
                        if (n2 == 0)
                            left = 0;
                        if (n1 == (inRows - 1))
                            down = 0;
                        if (n2 == (inCols - 1))
                            right = 0;

                        if (up != 0)
                        {
                            if (left != 0) MakePic(this.Controls["PB" + (n1 - 1).ToString() + "_" + (n2 - 1).ToString()]);
                            MakePic(this.Controls["PB" + (n1 - 1).ToString() + "_" + (n2).ToString()]);
                            if (right != 0) MakePic(this.Controls["PB" + (n1 - 1).ToString() + "_" + (n2 + 1).ToString()]);

                        }
                        {
                            if (left != 0) MakePic(this.Controls["PB" + (n1).ToString() + "_" + (n2 - 1).ToString()]);
                            if (right != 0) MakePic(this.Controls["PB" + (n1).ToString() + "_" + (n2 + 1).ToString()]);
                        }
                        if (down != 0)
                        {
                            if (left != 0) MakePic(this.Controls["PB" + (n1 + 1).ToString() + "_" + (n2 - 1).ToString()]);
                            MakePic(this.Controls["PB" + (n1 + 1).ToString() + "_" + (n2).ToString()]);
                            if (right != 0) MakePic(this.Controls["PB" + (n1 + 1).ToString() + "_" + (n2 + 1).ToString()]);
                        }
                    }
                    break;
                case "1":
                    ((PictureBox)sender).Image = Properties.Resources._1;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "2":
                    ((PictureBox)sender).Image = Properties.Resources._2;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "3":
                    ((PictureBox)sender).Image = Properties.Resources._3;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "4":
                    ((PictureBox)sender).Image = Properties.Resources._4;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "5":
                    ((PictureBox)sender).Image = Properties.Resources._5;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "6":
                    ((PictureBox)sender).Image = Properties.Resources._6;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "7":
                    ((PictureBox)sender).Image = Properties.Resources._7;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "8":
                    ((PictureBox)sender).Image = Properties.Resources._8;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                case "9":
                    ((PictureBox)sender).Image = Properties.Resources._9;
                    ((PictureBox)sender).Image.Tag = "3";
                    break;
                default:
                    break;
            }
        }

        private void Lose(object sender)
        {
            for (int i = 0; i < inRows; i++)
            {
                for (int j = 0; j < inCols; j++)
                {
                    if (MinesControl[i, j] == 1)
                    {
                        if (((PictureBox)sender).Name != ("PB" + i.ToString() + "_" + j.ToString()))
                        {
                            pb[i, j].Image = Properties.Resources.mine;
                            pb[i, j].Image.Tag = "3";
                        }     
                    }
                    else
                    {
                        pb[i, j].Image.Tag = "3";
                    }  
                }
            }
        }

        private void Win()
        {
            int[,] winMass = new int[inRows, inCols];
            for (int i = 0; i < inRows; i++)
            {
                for (int j = 0; j < inCols; j++)
                {
                    if (pb[i, j].Image.Tag == "2") winMass[i, j] = 1;
                    else winMass[i, j] = 0;
                }
            }

            bool varWin = true;

            for (int i = 0; i < inRows; i++)
            {
                for (int j = 0; j < inCols; j++)
                {
                    if (winMass[i, j] != MinesControl[i, j]) varWin = false;
                }
            }

            if (varWin == true)
            {
                for (int i = 0; i < inRows; i++)
                {
                    for (int j = 0; j < inCols; j++)
                    {
                        pb[i, j].Image.Tag = "3";
                    }
                }

                MessageBox.Show("Победа!!!");
            }
        }
    }
}
