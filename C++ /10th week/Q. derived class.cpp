#include <iostream>
using namespace std;

class Shape
{
public:
    virtual ~Shape() {}
    void ProcessShape()
    {
        Input();
        Print();
    }
    virtual void Input() = 0;   // 해당 객체에 대한 정보 입력
    virtual void Print() = 0;   // 해당 객체에 대한 정보 출력    

protected:
    char name_[20];
};

class Point : public Shape
{
public:
    Point(int x = 0, int y = 0) : x_(x), y_(y) {}
    virtual void Input()
    {
        cout << ">> 점(Point)의 이름, x값, y값 입력 : ";
        cin >> name_ >> x_ >> y_;
    }
    virtual void Print()
    {
        cout << "**********************" << endl;
        cout << "* 종류 : 점(Point)" << endl;
        cout << "* 이름 : " << name_ << endl;
        cout << "* 좌표 : (" << x_ << ", " << y_ << ")" << endl;
        cout << "**********************" << endl;
    }
    void setXY(int x, int y)
    {
        x_ = x; y_ = y;
    }
    int GetX() { return x_; } int GetY() { return y_; }

protected:
    int x_;
    int y_;
};

class Line : public Point
{
public:
    Line(Point p1 = (0,0), Point p2 = (0,0)) : p1_(p1), p2_(p2) {}
    virtual void Input()
    {
        int x1, x2, y1, y2;
        cout << ">> 직선(Line)의 이름, 시작점의 x y값과 끝점의 x y값을 입력 : ";
        cin >> name_ >> x1 >> y1 >> x2 >> y2;
        p1_.setXY(x1, y1); p2_.setXY(x2, y2);
        len_ = sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
    }
    virtual void Print()
    {
        cout << "**********************" << endl;
        cout << "* 종류 : 직선(Line)" << endl;
        cout << "* 이름 : " << name_ << endl;
        cout << "* 시점의 좌표 : (" << p1_.GetX() << ", " << p1_.GetY() << ")" << endl;
        cout << "* 종점의 좌표 : (" << p2_.GetX() << ", " << p2_.GetY() << ")" << endl;
        cout << "* 직선의 길이 : " << len_ << endl;
        cout << "**********************" << endl;
    }
private:
    Point p1_;
    Point p2_;
    double len_;
};

class Triangle : public Point
{
public:
    Triangle(Point p1 = (0, 0), Point p2 = (0, 0), Point p3 = (0, 0)) : p1_(p1), p2_(p2), p3_(p3) {}
    virtual void Input()
    {
        int x1, x2, x3, y1, y2, y3;
        cout << ">> 삼각형(Triangle)의 이름, 3개의 점의 좌표를 총 6개 입력 : ";
        cin >> name_ >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        p1_.setXY(x1, y1); p2_.setXY(x2, y2); p3_.setXY(x3, y3);
    }
    virtual void Print()
    {
        cout << "**********************" << endl;
        cout << "* 종류 : 삼각형(Triangle)" << endl;
        cout << "* 이름 : " << name_ << endl;
        cout << "* 점1의 좌표 : (" << p1_.GetX() << ", " << p1_.GetY() << ")" << endl;
        cout << "* 점2의 좌표 : (" << p2_.GetX() << ", " << p2_.GetY() << ")" << endl;
        cout << "* 점3의 좌표 : (" << p3_.GetX() << ", " << p3_.GetY() << ")" << endl;
        cout << "* 삼각형의 넓이 : " << GetArea(p1_, p2_, p3_) << endl;
        cout << "**********************" << endl;
    }
    double GetArea(Point pt1, Point pt2, Point pt3)
    {
        return (abs(pt1.GetX() * pt2.GetY() + pt2.GetX() * pt3.GetY() + pt3.GetX() * pt1.GetY() - pt1.GetY() * pt2.GetX() - pt2.GetY() * pt3.GetX() - pt3.GetY() * pt1.GetX()) / 2);
    }
private:
    Point p1_;
    Point p2_;
    Point p3_;
};

int main()
{
    Shape* shape = NULL;
    int input;

    cout << ">> 도형의 종류 입력(0:종료, 1:점, 2:선, 3:삼각형) : ";
    cin >> input;

    while (input != 0)
    {
        if (input == 1)
            shape = new Point;

        else if (input == 2)
            shape = new Line;

        else if (input == 3)
            shape = new Triangle;

        else
            continue;

        shape->ProcessShape();

        cout << ">> 도형의 종류 입력(0:종료, 1:점, 2:선, 3: 삼각형) : ";
        cin >> input;

        delete shape;
    }

    return 0;
}

