using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace GeomLib
{
    public class Geom
    {
        static public bool isInEllipse(Point leftTop, Size border, Point point)
        {
            float a = border.Width / 2;
            float b = border.Height / 2;
            float x = point.X - (leftTop.X + a);
            float y = point.Y - (leftTop.Y + b);
            return x * x / (a * a) + y * y / (b * b) <= 1;
        }
    }
}
