using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication2
{
    class Point
    {
        public int x { get; set; }
        public int y { get; set; }
        public Point(int X, int Y) { x = X; y = Y; }
    }

    class Circle
    {
        public Point cent { get; set; }
        public int radius { get; set; }
        public Circle(Point c, int r) { cent = c; radius = r; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            String line;
            line = Console.ReadLine();
            String[] plist = line.Split(' ');
            List<Circle> cList = new List<Circle>();
            List<Point> pList = new List<Point>();
            setInput(plist, cList, pList);

            int cl = 0;
            for (int i = 0; i < cList.Count; i++)
            {
                Point p1 = pList.ElementAt(2 * i);
                Point p2 = pList.ElementAt(2 * i + 1);
                Circle c = cList.ElementAt(i);
                cl = getPointPosition(c, p1) * getPointPosition(c, p2);
                switch (cl)
                {
                    case 1:
                        Console.Write("A");
                        break;
                    case 2:
                        Console.Write("B");
                        break;
                    case 3:
                        Console.Write("F");
                        break;
                    case 4:
                        Console.Write("C");
                        break;
                    case 6:
                        if (getPointPosition(c, p1) != 2)
                        {
                            Point tmp = p2;
                            p2 = p1;
                            p1 = tmp;
                        }
                        classification2(c, p1, p2);
                        break;
                    case 9:
                        classification1(c, p1,p2);
                        break;
                    default:
                        break;
                }
            }
        }

        static void classification2(Circle c, Point p1, Point p2)
        {
            float qx = (p1.x + p2.x) / 2;
            float qy = (p1.y + p2.y) / 2;
            float E = (float)1, err = 10;
            bool flag = false;
            Point cent = c.cent;
            while (err > E)
            {
                float terx = (qx - cent.x) * (qx - cent.x);
                float tery = (qy - cent.y) * (qy - cent.y);
                if (terx + tery <= c.radius * c.radius)
                {
                    flag = true;
                    Console.Write("D");
                    break;
                }
                qx = (p1.x + qx) / 2;
                qy = (p1.y + qy) / 2;
                err = (p1.x - qx) * (p1.x - qx) + (p1.y - qy) * (p1.y - qy);
            }
            if (!flag) Console.Write("G");
        }

        static void classification1(Circle c, Point p1, Point p2)
        {
            float py = p2.y - p1.y; 
            float px = p2.x - p1.x;
            float d = Math.Abs(py* (c.cent.x-p1.x)-px*(c.cent.y-p1.y));
            if (d / Math.Sqrt(py*py+px*px) - c.radius < 0){
               Console.Write("E or I");
            }
            else if (d / Math.Sqrt(py * py + px * px) - c.radius > 0)
            {
                Console.Write("I");
            }
            else
            {
                Console.Write("H");
            }
        }

        static int getPointPosition(Circle c, Point p)
        {
            long terx = (p.x - c.cent.x) * (p.x - c.cent.x);
            long tery = (p.y - c.cent.y) * (p.y - c.cent.y);
            if (terx + tery < (long)(c.radius * c.radius)) return (1);
            else if (terx + tery > (long)(c.radius * c.radius)) return (3);
            else return (2);
        }

        static void setInput(String[] plist, List<Circle> cList, List<Point> pList)
        {
            foreach (String p in plist)
            {
                String[] str = p.Split('/');
                foreach (String s in str)
                {
                    String[] nums = s.Split('(', ')', ',');
                    List<int> nList = new List<int>();
                    foreach (String n in nums)
                    {
                        if (!string.IsNullOrEmpty(n)) nList.Add(int.Parse(n));
                    }
                    if (nList.Count == 3)
                    {

                        Point point = new Point(nList.ElementAt(0), nList.ElementAt(1));
                        Circle c = new Circle(point, nList.ElementAt(2));
                        cList.Add(c);
                    }
                    else
                    {
                        Point point1 = new Point(nList.ElementAt(0), nList.ElementAt(1));
                        Point point2 = new Point(nList.ElementAt(2), nList.ElementAt(3));
                        pList.Add(point1);
                        pList.Add(point2);
                    }
                }
            }
        }
    }
}
