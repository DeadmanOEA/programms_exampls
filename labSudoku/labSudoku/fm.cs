using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace labSudoku
{
    public partial class fm : Form
    {
        const int n = 3;
        const int sizeButton = 50;
        public int[,] map = new int[n * n, n * n];
        public Button[,] buttons = new Button[n * n, n * n];
        private int width = 650;
        private int height = 456;
        private int nCells;
        private Button pressedButton;

        public fm()
        {
            InitializeComponent();

            this.Width = width;
            this.Height = height + 48;

            Label LLev = new Label();
            LLev.Text = "Выберите сложность";
            LLev.AutoSize = true;
            LLev.Location = new Point(width - 190, 10);
            this.Controls.Add(LLev);

            Button bBut = new Button();
            bBut.Text = "Сгенерировать";
            bBut.Location = new Point(width - 190, 170);
            bBut.AutoSize = true;
            bBut.Click += clickGen;
            this.Controls.Add(bBut);

            for (int i = 0; i < 3; i++)
            {
                RadioButton RBut = new RadioButton();
                switch (i)
                {
                    case 0:
                        RBut.Text = "Новичок";
                        RBut.Checked = true;
                        break;
                    case 1:
                        RBut.Text = "Средний";
                        break;
                    case 2:
                        RBut.Text = "Сложный";
                        break;
                }
                RBut.Location = new Point(width - 180, 50 + 40 * i);
                RBut.Click += makeLvl;
                this.Controls.Add(RBut);
            }
            nCells = 30;
            GenerateMap();
            this.KeyUp += new KeyEventHandler(butPress);
            findWin();
        }

        private void makeLvl(object sender, EventArgs e)
        {
            RadioButton pressedButton = sender as RadioButton;
            if (pressedButton.Text == "Новичок") nCells = 30;
            if (pressedButton.Text == "Средний") nCells = 40;
            if (pressedButton.Text == "Сложный") nCells = 50;
        }

        private void clickGen(object sender, EventArgs e)
        {
            for (int i = 0; i < n * n; i++)
            {
                for (int j = 0; j < n * n; j++)
                {
                    this.Controls.Remove(buttons[i, j]);
                }
            }
            GenerateMap();
        }

        private void findWin()
        {
            bool win = true;
            for (int i = 0; i < n * n; i++)
            {
                for (int j = 0; j < n * n; j++)
                {
                    if (buttons[i, j].Text == "") win = false;
                }
            }

            if (win == true)
            {
                MessageBox.Show("ПОБЕДА!!!!! ╰( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ");
                for (int i = 0; i < n * n; i++)
                {
                    for (int j = 0; j < n * n; j++)
                    {
                        this.Controls.Remove(buttons[i, j]);
                    }
                }
                GenerateMap();
            }
        }

        public void GenerateMap()
        {
            for (int i = 0; i < n * n; i++)
            {
                for (int j = 0; j < n * n; j++)
                {
                    map[i, j] = (i * n + i / n + j) % (n * n) + 1;
                    buttons[i, j] = new Button();
                }
            }
            
            Random r = new Random();
            for (int i = 0; i < 40; i++)
            {
                ShuffleMap(r.Next(0, 5));
            }

            CreateMap();
            HideCells();

            for (int i = 0; i < 2; i++)
            {
                PictureBox pic = new PictureBox();
                pic.BackColor = Color.Black;
                pic.Location = new Point(0, 151 + 153 * i);
                pic.Size = new Size(width - 193, 1);
                this.Controls.Add(pic);
            }

            for (int i = 0; i < 3; i++)
            {
                PictureBox pic = new PictureBox();
                pic.BackColor = Color.Black;
                pic.Location = new Point(151 + 153 * i, 0);
                pic.Size = new Size(1, height);
                this.Controls.Add(pic);
            }
        }

        public void HideCells()
        {
            int N = nCells;
            Random r = new Random();
            while (N > 0)
            {
                for (int i = 0; i < n * n; i++)
                {
                    for (int j = 0; j < n * n; j++)
                    {
                        if (!string.IsNullOrEmpty(buttons[i, j].Text))
                        {
                            int a = r.Next(0, 3);
                            buttons[i, j].Text = a == 0 ? "" : buttons[i, j].Text;
                            
                            if (a == 0)
                                N--;
                            if (N <= 0)
                                break;
                        }
                    }
                    if (N <= 0)
                        break;
                }
            }
            for (int i = 0; i < n * n; i++)
            {
                for (int j = 0; j < n * n; j++)
                {

                    buttons[i, j].Enabled = buttons[i, j].Text == "" ? true : false;
                    if (buttons[i, j].Enabled == false)
                    {
                        buttons[i, j].BackColor = Color.CornflowerBlue;
                    }
                    if (buttons[i, j].Enabled == true)
                    {
                        buttons[i, j].BackColor = Color.DarkSalmon;
                    }
                }
            }
        }

        public void ShuffleMap(int i)
        {
            switch (i)
            {
                case 0:
                    MatrixTransposition();
                    break;
                case 1:
                    SwapRowsInBlock();
                    break;
                case 2:
                    SwapColumnsInBlock();
                    break;
                case 3:
                    SwapBlocksInRow();
                    break;
                case 4:
                    SwapBlocksInColumn();
                    break;
                default:
                    MatrixTransposition();
                    break;
            }
        }

        public void SwapBlocksInColumn()
        {
            Random r = new Random();
            var block1 = r.Next(0, n);
            var block2 = r.Next(0, n);
            while (block1 == block2)
                block2 = r.Next(0, n);
            block1 *= n;
            block2 *= n;
            for (int i = 0; i < n * n; i++)
            {
                var k = block2;
                for (int j = block1; j < block1 + n; j++)
                {
                    var temp = map[i, j];
                    map[i, j] = map[i, k];
                    map[i, k] = temp;
                    k++;
                }
            }
        }

        public void SwapBlocksInRow()
        {
            Random r = new Random();
            var block1 = r.Next(0, n);
            var block2 = r.Next(0, n);
            while (block1 == block2)
                block2 = r.Next(0, n);
            block1 *= n;
            block2 *= n;
            for (int i = 0; i < n * n; i++)
            {
                var k = block2;
                for (int j = block1; j < block1 + n; j++)
                {
                    var temp = map[j, i];
                    map[j, i] = map[k, i];
                    map[k, i] = temp;
                    k++;
                }
            }
        }

        public void SwapRowsInBlock()
        {
            Random r = new Random();
            var block = r.Next(0, n);
            var row1 = r.Next(0, n);
            var line1 = block * n + row1;
            var row2 = r.Next(0, n);
            while (row1 == row2)
                row2 = r.Next(0, n);
            var line2 = block * n + row2;
            for (int i = 0; i < n * n; i++)
            {
                var temp = map[line1, i];
                map[line1, i] = map[line2, i];
                map[line2, i] = temp;
            }
        }

        public void SwapColumnsInBlock()
        {
            Random r = new Random();
            var block = r.Next(0, n);
            var row1 = r.Next(0, n);
            var line1 = block * n + row1;
            var row2 = r.Next(0, n);
            while (row1 == row2)
                row2 = r.Next(0, n);
            var line2 = block * n + row2;
            for (int i = 0; i < n * n; i++)
            {
                var temp = map[i, line1];
                map[i, line1] = map[i, line2];
                map[i, line2] = temp;
            }
        }

        public void MatrixTransposition()
        {
            int[,] tMap = new int[n * n, n * n];
            for (int i = 0; i < n * n; i++)
            {
                for (int j = 0; j < n * n; j++)
                {
                    tMap[i, j] = map[j, i];
                }
            }
            map = tMap;
        }

        public void CreateMap()
        {
            int ystep = 0;
            for (int i = 0; i < n * n; i++)
            {
                if ((i == 3) || (i == 6))
                {
                    ystep += 1;
                }
                int xstep = 0;
                for (int j = 0; j < n * n; j++)
                {
                    Button button = new Button();
                    buttons[i, j] = button;
                    button.Size = new Size(sizeButton, sizeButton);
                    button.Text = map[i, j].ToString();
                    button.Click += OnCellPressed;
                    button.KeyDown += butPress;

                    if ((j == 3) || (j == 6))
                    {
                        xstep += 1;
                    }

                    button.Location = new Point(j * sizeButton + 3 * xstep, i * sizeButton + 3 * ystep);

                    this.Controls.Add(button);
                }
            }
        }

        public void OnCellPressed(object sender, EventArgs e)
        {
            pressedButton = sender as Button;
        }

        private void butPress(object sender, KeyEventArgs e)
        {
            if (pressedButton != null)
            {
                switch (e.KeyCode)
                {
                    case Keys.D1:
                    case Keys.NumPad1:
                        pressedButton.Text = "1";
                        break;
                    case Keys.D2:
                    case Keys.NumPad2:
                        pressedButton.Text = "2";
                        break;
                    case Keys.D3:
                    case Keys.NumPad3:
                        pressedButton.Text = "3";
                        break;
                    case Keys.D4:
                    case Keys.NumPad4:
                        pressedButton.Text = "4";
                        break;
                    case Keys.D5:
                    case Keys.NumPad5:
                        pressedButton.Text = "5";
                        break;
                    case Keys.D6:
                    case Keys.NumPad6:
                        pressedButton.Text = "6";
                        break;
                    case Keys.D7:
                    case Keys.NumPad7:
                        pressedButton.Text = "7";
                        break;
                    case Keys.D8:
                    case Keys.NumPad8:
                        pressedButton.Text = "8";
                        break;
                    case Keys.D9:
                    case Keys.NumPad9:
                        pressedButton.Text = "9";
                        break;
                }
            }

            findWin();
        }
    }
}
