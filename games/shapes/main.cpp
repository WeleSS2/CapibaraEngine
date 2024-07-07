#include "raylib.h"
#include <iostream>
#include <cmath>

const int screenWidth = 800;
const int screenHeight = 450;

class Point {

private:

    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() { return x; };
    int getY() { return y; };

    void setX(int s_x) {
        x = s_x;
    }
    
    void setY(int s_y) {
        y = s_y;
    }
    
    void setCords(int _x, int _y) {
        x = _x;
        y = _y;
    }

    friend class Circle;
    friend class RectangleClass;
    friend class Square;
};

class Shape {
public:
    virtual void Draw() {
        std::cout << "Drawing a shape" << "\n";
    }
    
    virtual double Area() {
        return 0.0;
    }
    
    double Area(double radius) {
        const double pi = 3.14159265358979323846;
        return pi * radius * radius;
    }
    
    double Area(double width, double height) {
        return width * height;
    }

};

class Circle : public Shape {

    private:
        double radius;
        Point point;
    
    public:
        Circle() {};
        Circle(double _radius) : radius(_radius) {};
        Circle(Point _cords) : point(_cords) {};

        void Draw() override {
            DrawCircle(point.getX(), point.getY(), radius, RED);
            DrawCircleGradient(point.getX(), point.getY(), radius, MAROON, GOLD);
            DrawCircleLines(point.getX(), point.getY(), radius, BLUE);
        }
        
        double Area() override {
            return Shape::Area(radius);
        }
        
        void get_radius() {
            std::cout << "Enter the radius of the circle: ";
            std::cin >> radius;
            std::cout << "\n";
        }

};



class RectangleClass : public Shape {

    private:
            double width, height;
            Point point;
    public:
        RectangleClass() {};
        RectangleClass(double _width, double _height) : width(_width), height(_height) {};
        RectangleClass(Point _cords) : point(_cords) {};

        void Draw() override {
            DrawRectangle(point.getX(), point.getY(), width, height, RED);
            DrawRectangleGradientH(point.getX(), point.getY(), width, height, MAROON, GOLD);
            DrawRectangleLines(point.getX(), point.getY(), width, height, ORANGE);
        }
        double Area() override {
            return Shape::Area(width, height);
        }
        void get_width() {
            std::cout << "Enter the width of the rectangle: ";
            std::cin >> width;
            std::cout << "\n";
        }
        void get_height() {
            std::cout << "Enter the height of the rectangle: ";
            std::cin >> height;
            std::cout << "\n";
        }
};

class Square : public Shape {

    private:
        double side;
        Point point;
    public:
        Square() {};
        Square(double _side) : side(_side) {};
        Square(Point _cords) : point(_cords) {};

        void Draw() override {
            DrawRectangle(point.getX(), point.getY(), side, side, RED);
            DrawRectangleGradientH(point.getX(), point.getY(), side, side, MAROON, GOLD);
            DrawRectangleLines(point.getX(), point.getY(), side, side, ORANGE);
        }
        double Area() override {
            return Shape::Area(side, side);
        }
        void get_side() {
            std::cout << "Enter the side of the square: ";
            std::cin >> side;
            std::cout << "\n";
        }
};



int main() {
    
    std::cout << "Chose a shape to draw: \n";
    std::cout << "1. Circle \n";
    std::cout << "2. Rectangle \n";
    std::cout << "3. Square \n";

    int choice;

    std::cin >> choice;

    std::cout << "Enter the coordinates of the shape: \n";
    int x, y;
    std::cin >> x >> y;

    Point point(x, y);

    Circle c(point);
    RectangleClass r(point);
    Square s(point);

    switch (choice) {
        case 1: {
            c.get_radius();
            std::cout << "Area of the circle: " << c.Area() << "\n";
            break;
        }
        case 2: {
            r.get_width();
            r.get_height();
            std::cout << "Area of the rectangle: " << r.Area() << "\n";
            break;
        }
        case 3: {
            s.get_side();
            std::cout << "Area of the square: " << s.Area() << "\n";
            break;
        }
    }

    InitWindow(screenWidth, screenHeight, "Shapes");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (choice) {
            case 1: {
                c.Draw();
                break;
            }
            case 2: {
                r.Draw();
                break;
            }
            case 3: {
                s.Draw();
                break;
            }
        }
        EndDrawing(); 
    }

    return 0;
}