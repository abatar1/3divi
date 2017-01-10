#define _USE_MATH_DEFINES
#include <cmath>
#include <random> 
#include <vector>
#include <string> 
#include <fstream>

using namespace std;
using namespace tr1;

struct Point
{
	double x;
	double y;

	Point(double _x, double _y) : x(_x), y(_y) {}
	Point() {}
	Point(int fieldSize)
	{
		random_device rd;
		mt19937 m1(rd());
		mt19937 m2(rd());
		uniform_real<double> distr(0, fieldSize);
		x = distr(m1), y = distr(m2);
	}

	Point operator-(const Point& a)
	{
		return Point(x - a.x, y - a.y);
	}
};

struct Line
{
	Point start;
	Point end;

	Line(Point _start, Point _end) : start(_start), end(_end) {}

	double Length()
	{
		return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	}

	void RotateX()
	{
		Point tmp = start;
		start = end;
		end = tmp;
	}

	void RotateY()
	{
		Point tmp = start;
		start = Point(end.y, end.x);
		end = Point(tmp.y, tmp.x);
	}
};

class MathExtention
{
public:
	static double FloatP(double x)
	{
		if (x < 0)
			return 1 - (x - int(x));
		return x - int(x);
	}

	static double FloatPR(double x)
	{
		return 1 - FloatP(x);
	}

	static int Round(double x)
	{
		return int(x + 0.5);
	}
};

class Bitmap
{
private:
	vector<vector<unsigned char>> bitmap;
	int width;
	int height;

	struct Proxy
	{
		Bitmap& b;
		Point indexer;
		Proxy(Bitmap& _bitmap, Point _indexer) : b(_bitmap), indexer(_indexer) { }

		operator unsigned char()
		{
			return b.bitmap[int(indexer.x)][int(indexer.y)];
		}

		unsigned char& operator=(const unsigned char& other)
		{
			return b.bitmap[int(indexer.x)][int(indexer.y)] = other;
		}
	};

public:
	Bitmap operator=(const Bitmap& b)
	{
		bitmap = b.bitmap;
		width = b.width;
		height = b.height;
		return *this;
	}

	Proxy operator[](Point indexer)
	{
		return Proxy(*this, indexer);
	}

	Bitmap(int _width, int _height) : width(_width), height(_height)
	{
		bitmap = vector<vector<unsigned char>>(
			height,
			vector<unsigned char>(width, 0));
	}

	void Noise(double prob)
	{
		random_device rd;
		mt19937 m(rd());
		uniform_real<double> distr1(0, 1);
		uniform_int<int> distr2(0, 255);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (distr1(m) - prob < 0) bitmap[i][j] = distr2(m);				
	}

	void WriteToPGM(string filename)
	{
		ofstream f(filename, ios_base::out | ios_base::binary);
		int maxColorValue = 255;
		f << "P5\r\n" << width << " " << height << "\r\n" << maxColorValue << "\r\n";

		for (auto line : bitmap)
			for (auto point : line)
				f.write(reinterpret_cast<const char*>(&point), sizeof(unsigned char));

		f.close();
	}

	void ReadFromPGM(string filename)
	{
		ifstream f(filename, ios_base::in | ios_base::binary);
		string inputline;

		f.ignore(256, '\n');
		f.ignore(256, '\n');
		f.ignore(256, '\n');
		for (int i = 0; i < height; i++)
			f.read((char*)&bitmap[i][0], width * sizeof(unsigned char));
	}

	void Clear()
	{
		
	}
};

class WuDrawer
{
private:
	double HandleEndpoint(Point point, double gradient, bool steep, Point& pxl)
	{
		int xend = MathExtention::Round(point.x);
		double yend = point.y + gradient*(xend - point.x);
		double xgap = 1 - MathExtention::FloatP(point.x + 0.5);

		pxl = Point(xend, int(yend));

		if (steep)
		{
			Plot(Point(pxl.y, pxl.x), MathExtention::FloatPR(yend) * xgap);
			Plot(Point(pxl.y + 1, pxl.x), MathExtention::FloatP(yend) * xgap);
		}
		else
		{
			bitmap[Point(pxl.x, pxl.y)] = unsigned char(MathExtention::FloatPR(yend) * xgap);
			bitmap[Point(pxl.x, pxl.y + 1)] = unsigned char(MathExtention::FloatP(yend) * xgap);
		}
		return yend + gradient;
	}

	void Plot(Point pos, double c)
	{
		bitmap[pos] = unsigned char((1 - c) * 255);
	}

public:
	Bitmap bitmap;

	WuDrawer(Bitmap _bitmap) : bitmap(_bitmap) { }

	void Process(Line line)
	{
		bool steep = abs(line.end.y - line.start.y) > abs(line.end.x - line.start.x);

		if (steep)
			line.RotateY();
		if (line.end.x < line.start.x)
			line.RotateX();	

		double dx = line.end.x - line.start.x;
		double dy = line.end.y - line.start.y;

		double gradient = dy / dx;

		Point xpl1, xpl2;
		double intery = HandleEndpoint(line.start, gradient, steep, xpl1);
		HandleEndpoint(line.end, gradient, steep, xpl2);

		if (steep)
		{
			for (int x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
			{
				Plot(Point(int(intery), x), MathExtention::FloatPR(intery));
				Plot(Point(int(intery) + 1, x), MathExtention::FloatP(intery));
				intery = intery + gradient;
			}
		}
		else
		{
			for (int x = int(xpl1.x) + 1; x < xpl2.x - 1; x++)
			{
				Plot(Point(x, int(intery)), MathExtention::FloatPR(intery));
				Plot(Point(x, int(intery) + 1), MathExtention::FloatP(intery));
				intery = intery + gradient;
			}
		}
	}
};

class Triangle
{
private:
	Point a;
	Point b;
	Point c;

	Triangle(Point _a, Point _b, Point _c) : a(_a), b(_b), c(_c) {}

	double FindAngle(Line ab, Line bc)
	{
		Point AB = ab.end - ab.start;
		Point BC = bc.end - bc.start;
		return acos(abs(AB.x*BC.x + AB.y*BC.y) / (sqrt(pow(AB.x, 2) + pow(AB.y, 2)) * sqrt(pow(BC.x, 2) + pow(BC.y, 2)))) * 180.0 / M_PI;
	}

public:	
	Triangle(int fieldSize)
	{
		Triangle t = Triangle(Point(fieldSize), Point(fieldSize), Point(fieldSize));
		while (!t.IsAllowed())
			t = Triangle(Point(fieldSize), Point(fieldSize), Point(fieldSize));
		*this = t;
	}

	bool IsAllowed()
	{
		Line AB = Line(a, b);
		Line AC = Line(a, c);
		Line BC = Line(b, c);
		if (AB.Length() < 100 || AC.Length() < 100 || BC.Length() < 100)
			return false;
		if (FindAngle(AB, AC) < 30 || FindAngle(AB, BC) < 30 || FindAngle(AC, BC) < 30)
			return false;
		return true;
	}

	Bitmap DrawOn(Bitmap bitmap)
	{
		WuDrawer drawer = WuDrawer(bitmap);
		drawer.Process(Line(a, b));
		drawer.Process(Line(a, c));
		drawer.Process(Line(b, c));		
		return drawer.bitmap;
	}
};

int main(int argc, char* argv[])
{
	int fieldSize = 500;
	double prob = 0.01;

	Bitmap bitmap = Bitmap(fieldSize, fieldSize);

	/*if (argv[1] == "generator")
	{*/
		Triangle triangle = Triangle(fieldSize);
		bitmap = triangle.DrawOn(bitmap);
		bitmap.Noise(stod(argv[2]));
		bitmap.WriteToPGM("image.pgm");
	/*}
	else if (argv[1] == "restore")
	{*/
		bitmap.ReadFromPGM(argv[2]);
	/*}*/
	return 0;
}