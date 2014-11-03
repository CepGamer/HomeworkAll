using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GeomLib;

/*
 * ToDo:
 * 1. MessageBox убрать, поставить что-либо прямо в приложение. - (+-)сделано
 * 2. Переименовать стандартные классы и заголовки. - вроде сделано
 * 3. Рисование по событию OnPaint. - сделано.
 * 4. Отключить/добавить (чтобы не ломалось) Resize. - сделано.
 * */

namespace MainApp
{
    public partial class MainAppForm : Form
    {
        private Drawer img;

        public MainAppForm()
        {
            InitializeComponent();
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox = false;
            img = new Drawer();
            result.Text = "Start by pressing button";
        }
        private void mainButton_Click(object sender, EventArgs e)
        {
            img.createNew(easel.Width, easel.Height);
            easel.Refresh();
            result.Text = img.resText;
        }

        private void MainAppForm_Load(object sender, System.EventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void easel_Click(object sender, System.EventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void easel_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            e.Graphics.Clear(Color.White);

            img.draw(e.Graphics);
        }
    }

    class Drawer
    {
        private Random rand;
        private SolidBrush dot;
        private Pen ellipse;
        private Rectangle borderEllipse;
        private Rectangle borderDot;
        private Size size;
        private Point leftTop;
        private Point dotP;

        public String resText;

        public Drawer()
        {
            rand = new Random();
            ellipse = new Pen(Color.Aquamarine, 3);
            dot = new SolidBrush(Color.Black);
            resText = "";
        }

        public void createNew(int width, int height)
        {
            Point a = new Point(rand.Next(width), rand.Next(height));
            Point b = new Point(rand.Next(width), rand.Next(height));
            dotP = new Point(rand.Next(width), rand.Next(height));

            leftTop = new Point(Math.Min(a.X, b.X), Math.Min(a.Y, b.Y));

            size = new Size(Math.Max(a.X, b.X) - Math.Min(a.X, b.X), Math.Max(a.Y, b.Y) - Math.Min(a.Y, b.Y));
            borderEllipse = new Rectangle(leftTop, size);

            borderDot = new Rectangle(dotP.X - 1, dotP.Y - 1, 3, 3);
            resText = "Dot is " + (GeomLib.Geom.isInEllipse(leftTop, size, dotP) ? "" : "NOT ") + "in ellipse";
        }

        public void draw(System.Drawing.Graphics graph)
        {
            graph.DrawEllipse(ellipse, borderEllipse);
            graph.FillEllipse(dot, borderDot);
        }
    }
}
