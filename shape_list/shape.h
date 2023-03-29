/*
----------------------------
  Paola Reyes
  3/27/23
  UIC CS 251, Wed 4pm Lab
  Prof. Adam Koehler
----------------------------    
Project 4 - Shape List

Shape List is a program that mimics the storage component of a drawing program. 
There are two main classes: Shape and CanvasList. CanvasList is a linked list of various 
Shapes that we create. 

The Shape properties are:
Shape (base class): x & y position
Circle (derived class): x, y, and radius values
Rectangle (derived class): x, y, width, and height values
RightTriangle (derived class): x, y, base, and height values

The Shape class allows you to set the x, y, etc. values to currate where you want the
Shape to be and with what size dimensions. They are then "placed" onto the canvas.
*/
#pragma once
using namespace std;

//----------------------------------------------------------------------
class Shape
{
    protected:
        int x;
        int y;

    public: 
        Shape();
        Shape(int x, int y);

        virtual ~Shape();
        virtual Shape* copy();

        int getX() const;
        int getY() const;
        void setX(int);
        void setY(int);
        
        virtual void printShape() const;
};


// Default constructor. Set x and y to 0
Shape::Shape() {
    x = 0;
    y = 0;
}


// Parameterized constructor. Sets x and y to the given value
Shape::Shape(int x, int y) {
    this->x = x;
    this->y = y;
}


// Destructor. Leave it empty because we just need it to exist
Shape::~Shape() {
    ; // Deleting the object
}


// Make a copy of the implicit Shape. Store it in a Shape pointer and return the pointer
Shape* Shape::copy() {
    Shape *s = new Shape;   // Allocate a new memory address

    s->setX(x);  // Copy over values
    s->setY(y);

    return s;   // Return a Shape pointer
}


// Return the value of x
int Shape::getX() const {
    return x;
}


// Return the value of y
int Shape::getY() const {
    return y;
}


// Change the value of x
void Shape::setX(int n) {
    x = n;
}


// Change the value of y
void Shape::setY(int n) {
    y = n;
}


// Print a message saying the object type (Shape) and it's x & y values
void Shape::printShape() const {
    cout << "It's a Shape at x: " << x << ", y: " << y << endl;
}


//----------------------------------------------------------------------------------------------
class Circle : public Shape 
{
    private:
        int radius;

    public: 
        Circle();
        Circle(int r);
        Circle(int x, int y, int r);

        virtual ~Circle();
        virtual Circle* copy();
        
        int getRadius() const;
        void setRadius(int);
        
        virtual void printShape() const;
};


// Default constructor. Set x, y, and radius to 0
Circle::Circle() {
    radius = 0;

    // Derived from Shape class
    x = 0;
    y = 0;
}


// Parameterized constructor. Sets radius to the given value
Circle::Circle(int r) {
    radius = r;
    
    // Derived from Shape class
    x = 0;
    y = 0;
}


// Parameterized constructor with x and y. Sets x, y, and radius to the given values
Circle::Circle(int x, int y, int r) {
    radius = r;
    
    // Derived from Shape class
    this->x = x;
    this->y = y;
}


// Destructor. Leave it empty because we just need it to exist
Circle::~Circle() {
    ; // Deleting the object
}


// Make a copy of the implicit Circle. Store it in a Circle pointer and return the pointer
Circle* Circle::copy() {
    Circle *c = new Circle;   // Allocate a new memory address
    c->setRadius(radius);

    // x, y, setX(), and setY() are derived from Shape class
    c->setX(x);
    c->setY(y);

    return c;   // Return a Circle pointer
}


// Return the value of radius
int Circle::getRadius() const {
    return radius;
}


// Change the value of radius
void Circle::setRadius(int r) {
    radius = r;
}


// Print a message saying the object type (Circle) and it's x, y, and radius values
void Circle::printShape() const {
    cout << "It's a Circle at x: " << x << ", y: " << y << ", radius: " << radius << endl;
}


//--------------------------------------------------------------------------------------------------------
class Rectangle : public Shape 
{
    private:
        int width;
        int height;

    public: 
        Rectangle();
        Rectangle(int w, int h);
        Rectangle(int x, int y, int w, int h);
        
        virtual ~Rectangle();
        virtual Rectangle* copy();
        
        int getWidth() const;
        int getHeight() const;
        void setWidth(int);
        void setHeight(int);

        virtual void printShape() const;
};


// Default constructor. Set x, y, width, and height to 0
Rectangle::Rectangle() {
    width = 0;
    height = 0;

    // Derived from Shape class
    x = 0;
    y = 0;
}


// Parameterized constructor. Sets width and height to the given values
Rectangle::Rectangle(int w, int h) {
    width = w;
    height = h;
    
    // Derived from Shape class
    x = 0;
    y = 0;
}


// Parameterized constructor with x and y. Sets x, y, width, and height to the given values
Rectangle::Rectangle(int x, int y, int w, int h) {
    width = w;
    height = h;
    
    // Derived from Shape class
    this->x = x;
    this->y = y;
}


// Destructor. Leave it empty because we just need it to exist
Rectangle::~Rectangle() {
    ; // Deleting the object
}


// Make a copy of the implicit Rectangle. Store it in a Rectangle pointer and return the pointer
Rectangle* Rectangle::copy() {
    Rectangle *r = new Rectangle;   // Allocate a new memory address
    r->setWidth(width);
    r->setHeight(height);

    // x, y, setX(), and setY() are derived from Shape class
    r->setX(x);
    r->setY(y);

    return r;   // Return a Rectangle pointer
}


// Return the value of width
int Rectangle::getWidth() const {
    return width;
}


// Return the value of height
int Rectangle::getHeight() const {
    return height;
}


// Change the value of width
void Rectangle::setWidth(int w) {
    width = w;
}


// Change the value of height
void Rectangle::setHeight(int h) {
    height = h;
}


// Print a message saying the object type (Rectangle) and it's x, y, width, and height values
void Rectangle::printShape() const {
    cout << "It's a Rectangle at x: " << x << ", y: " << y << " with width: " << width << " and height: " << height << endl;
}


//---------------------------------------------------------------------------------------------
class RightTriangle : public Shape 
{
    private:
        int base;
        int height;

    public: 
        RightTriangle();
        RightTriangle(int b, int h);
        RightTriangle(int x, int y, int b, int h);
        
        virtual ~RightTriangle();
        virtual RightTriangle* copy();
        
        int getBase() const;
        int getHeight() const;
        void setBase(int);
        void setHeight(int);

        virtual void printShape() const;
};


// Default constructor. Set x, y, base, and height to 0
RightTriangle::RightTriangle() {
    base = 0;
    height = 0;

    // Derived from Shape class
    x = 0;
    y = 0;
}


// Parameterized constructor. Sets base and height to the given values
RightTriangle::RightTriangle(int b, int h) {
    base = b;
    height = h;
    
    // Derived from Shape class
    x = 0;
    y = 0;
}


// Parameterized constructor with x and y. Sets x, y, base and height to the given values
RightTriangle::RightTriangle(int x, int y, int b, int h) {
    base = b;
    height = h;
    
    // Derived from Shape class
    this->x = x;
    this->y = y;
}


// Destructor. Leave it empty because we just need it to exist
RightTriangle::~RightTriangle() {
    ; // Deleting the object
}


// Make a copy of the implicit Rectangle. Store it in a RightTriangle pointer and return the pointer
RightTriangle* RightTriangle::copy() {
    RightTriangle *t = new RightTriangle;   // Allocate a new memory address
    t->setBase(base);
    t->setHeight(height);

    // x, y, setX(), and setY() are derived from Shape class
    t->setX(x);
    t->setY(y);

    return t;   // Return a RightTriangle pointer
}


// Return the value of base
int RightTriangle::getBase() const {
    return base;
}


// Return the value of height
int RightTriangle::getHeight() const {
    return height;
}


// Change the value of base
void RightTriangle::setBase(int b) {
    base = b;
}


// Change the value of height
void RightTriangle::setHeight(int h) {
    height = h;
}


// Print a message saying the object type (RightTriangle) and it's x, y, width, and height values
void RightTriangle::printShape() const {
    cout << "It's a Right Triangle at x: " << x << ", y: " << y << " with base: " << base << " and height: " << height << endl;
}