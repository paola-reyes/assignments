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
/// Provided testing file to implement
/// framework based tests in. The example
/// below uses the Catch testing framework
/// version that uses a single .hpp file.

// This tells Catch to provide a main()
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "shape.h"
#include "canvaslist.h"
using namespace std;


//---------------------------------------------------------------------------------------
// Tests Shape default constructor sets x and y to 0
TEST_CASE("Shape default constructor") 
{
  Shape s;
  REQUIRE(s.getX() == 0);
  REQUIRE(s.getY() == 0); 
}


// Test if parametized constructor changes x and y values
TEST_CASE("Shape parameterized constructor") 
{
  Shape s(1, 2);
  REQUIRE(s.getX() == 1);
  REQUIRE(s.getY() == 2);
}


// Test if Shape copy() works on default constructor
TEST_CASE("Shape copy() for default constructor")
{
  Shape s1;
  Shape *s2 = s1.copy();

  REQUIRE(s2->getX() == 0);
  REQUIRE(s2->getY() == 0);

  delete s2;  // Free heap memory
}


// Test if Shape copy() works on parameterized constructor
TEST_CASE("Shape copy() for parameterized constructor")
{
  Shape s1(1, 2);
  Shape *s2 = s1.copy();

  REQUIRE(s2->getX() == 1);
  REQUIRE(s2->getY() == 2);

  delete s2;  // Free heap memory
}


// Test if Shape copy() words after using setX() and setY()
TEST_CASE("Shape copy() after setX() and setY()")
{
  Shape s1(1, 2);
  Shape *s2 = s1.copy();

  s2->setX(3);
  s2->setY(5);

  REQUIRE(s2->getX() == 3);
  REQUIRE(s2->getY() == 5);

  delete s2;  // Free heap memory
}


// Test that Shape copy doesn't change if the original shape is changed
TEST_CASE("Shape copy() doesn't change alongside it's original shape") 
{
  Shape s1(1, 2);
  Shape *s2 = s1.copy();

  // Switch up the values
  s2->setX(3);  
  s2->setY(5);

  s1.setX(7);
  s1.setY(9); 

  REQUIRE(s2->getX() == 3);
  REQUIRE(s2->getY() == 5);

  delete s2;  // Free heap memory
}


// Test if Shape getX() works after setX()
TEST_CASE("Shape getX() after setX()")
{
  Shape s1;
  Shape s2(1, 0);

  s1.setX(5);
  s2.setX(3);

  REQUIRE(s1.getX() == 5);
  REQUIRE(s2.getX() == 3);
}


// Test if Shape getY() works after setY()
TEST_CASE("Shape getY() after setY()")
{
  Shape s1;
  Shape s2(0, 1);

  s1.setY(5);
  s2.setY(3);

  REQUIRE(s1.getY() == 5);
  REQUIRE(s2.getY() == 3);
}


//---------------------------------------------------------------------------------------
// Tests Circle default constructor sets x, y, and radius to 0
TEST_CASE("Circle default constructor getX()") 
{
  Circle c;

  REQUIRE(c.getX() == 0);
  REQUIRE(c.getY() == 0); 
  REQUIRE(c.getRadius() == 0);
}


// Test if Circle parametized constructor changes x, y, and radius values
TEST_CASE("Circle partial parameterized constructor") 
{
  Circle c(3);

  REQUIRE(c.getX() == 0);
  REQUIRE(c.getY() == 0);
  REQUIRE(c.getRadius() == 3);
}


// Test if Circle parameterized constructor changes x, y, and radious values
TEST_CASE("Circle full parameterized construcor") {
  Circle c(1, 2, 3);

  REQUIRE(c.getX() == 1);
  REQUIRE(c.getY() == 2);
  REQUIRE(c.getRadius() == 3);
}


// Test if Circle copy() works on default constructor
TEST_CASE("Circle copy() for default constructor")
{
  Circle c1;
  Circle *c2 = c1.copy();

  REQUIRE(c2->getX() == 0);
  REQUIRE(c2->getY() == 0);
  REQUIRE(c2->getRadius() == 0);

  delete c2;  // Free heap memory
}


// Test if Circle copy() works on partial parameterized constructor
TEST_CASE("Circle copy() for partial parameterized constructor")
{
  Circle c1(3);
  Circle *c2 = c1.copy();

  REQUIRE(c2->getX() == 0);
  REQUIRE(c2->getY() == 0);
  REQUIRE(c2->getRadius() == 3);

  delete c2;  // Free heap memory
}


// Test if Circle copy() words with full paramaterized constructor
TEST_CASE("Circle copy() for full parameterized constructor") {
  Circle c1(4, 5, 6);
  Circle *c2 = c1.copy();

  REQUIRE(c1.getX() == 4);
  REQUIRE(c1.getY() == 5);
  REQUIRE(c1.getRadius() == 6);

  delete c2;
}


// Test if Circle copy() words after using setX(), setY(), and setRadius()
TEST_CASE("Circle copy() after setX(), setY(), and setRadius()")
{
  Circle c1;
  Circle *c2 = c1.copy();

  c2->setX(1);
  c2->setY(3);
  c2->setRadius(5);

  REQUIRE(c2->getX() == 1);
  REQUIRE(c2->getY() == 3);
  REQUIRE(c2->getRadius() == 5);

  delete c2;  // Free heap memory
}


// Test that Circle copy doesn't change if the original shape is changed
TEST_CASE("Circle copy() doesn't change alongside it's original shape") 
{
  Circle c1(3);
  Circle *c2 = c1.copy();

  // Switch up the values
  c2->setX(1);  
  c2->setY(3);
  c2->setRadius(5);

  c1.setX(7);
  c1.setY(9); 
  c1.setRadius(11);

  REQUIRE(c2->getX() == 1);
  REQUIRE(c2->getY() == 3);
  REQUIRE(c2->getRadius() == 5);

  delete c2;  // Free heap memory
}


// Test Circle's derived functions setX() and setY()
TEST_CASE("Circle setX() and setY()")
{
  Circle c;

  c.setX(1);
  c.setY(3);

  REQUIRE(c.getX() == 1);
  REQUIRE(c.getY() == 3);
} 


// Test if Circle getRadius() works after setRadius()
TEST_CASE("Circle getRadius() after setRadius()")
{
  Circle c1;
  Circle c2(3);

  c1.setRadius(5);
  c2.setRadius(3);

  REQUIRE(c1.getRadius() == 5);
  REQUIRE(c2.getRadius() == 3);
}


//---------------------------------------------------------------------------------------
// Tests Rectangle default constructor sets x, y, width, and height to 0
TEST_CASE("Rectangle default constructor getX()") 
{
  Rectangle r;

  REQUIRE(r.getX() == 0);
  REQUIRE(r.getY() == 0); 
  REQUIRE(r.getWidth() == 0);
  REQUIRE(r.getHeight() == 0);
}


// Test if Rectangle parametized constructor changes x, y, width, and height values
TEST_CASE("Rectangle partial parameterized constructor") 
{
  Rectangle r(1, 2);

  REQUIRE(r.getX() == 0);
  REQUIRE(r.getY() == 0);
  REQUIRE(r.getWidth() == 1);
  REQUIRE(r.getHeight() == 2);
}


// Test if Rectangle parameterized constructor changes x, y, width, and height values
TEST_CASE("Rectangle full parameterized construcor") {
  Rectangle r(1, 2, 3, 4);

  REQUIRE(r.getX() == 1);
  REQUIRE(r.getY() == 2);
  REQUIRE(r.getWidth() == 3);
  REQUIRE(r.getHeight() == 4);
}


// Test if Rectangle copy() works on default constructor
TEST_CASE("Rectangle copy() for default constructor")
{
  Rectangle r1;
  Rectangle *r2 = r1.copy();

  REQUIRE(r2->getX() == 0);
  REQUIRE(r2->getY() == 0);
  REQUIRE(r2->getWidth() == 0);
  REQUIRE(r2->getHeight() == 0);

  delete r2;  // Free heap memory
}


// Test if Rectangle copy() works on parameterized constructor
TEST_CASE("Rectangle copy() for parameterized constructor")
{
  Rectangle r1(1, 3);
  Rectangle *r2 = r1.copy();

  REQUIRE(r2->getX() == 0);
  REQUIRE(r2->getY() == 0);
  REQUIRE(r2->getWidth() == 1);
  REQUIRE(r2->getHeight() == 3);

  delete r2;  // Free heap memory
}


// Test if Circle copy() words with full paramaterized constructor
TEST_CASE("Rectangle copy() for full parameterized constructor") {
  Rectangle r1(4, 5, 6, 7);
  Rectangle *r2 = r1.copy();

  REQUIRE(r1.getX() == 4);
  REQUIRE(r1.getY() == 5);
  REQUIRE(r1.getWidth() == 6);
  REQUIRE(r1.getHeight() == 7);

  delete r2;
}


// Test if Rectangle copy() words after using setX(), setY(), setWidth(), and setHeight()
TEST_CASE("Rectangle copy() after setX(), setY(), setWidth(), setHeight()")
{
  Rectangle r1;
  Rectangle *r2 = r1.copy();

  r2->setX(1);
  r2->setY(3);
  r2->setWidth(5);
  r2->setHeight(7);

  REQUIRE(r2->getX() == 1);
  REQUIRE(r2->getY() == 3);
  REQUIRE(r2->getWidth() == 5);
  REQUIRE(r2->getHeight() == 7);

  delete r2;  // Free heap memory
}


// Test that Rectangle copy doesn't change if the original shape is changed
TEST_CASE("Rectangle copy() doesn't change alongside it's original shape") 
{
  Rectangle r1(1, 3);
  Rectangle *r2 = r1.copy();

  // Switch up the values
  r2->setX(1);  
  r2->setY(3);
  r2->setWidth(5);
  r2->setHeight(7);

  r1.setX(7);
  r1.setY(9); 
  r1.setWidth(11);
  r1.setHeight(13);

  REQUIRE(r2->getX() == 1);
  REQUIRE(r2->getY() == 3);
  REQUIRE(r2->getWidth() == 5);
  REQUIRE(r2->getHeight() == 7);

  delete r2;  // Free heap memory
}


// Test Rectangle's derived functions setX() and setY()
TEST_CASE("Rectangle setX() and setY()")
{
  Rectangle r;

  r.setX(1);
  r.setY(3);

  REQUIRE(r.getX() == 1);
  REQUIRE(r.getY() == 3);
} 


// Test if Rectangle getWidth() and getHeight() works after setwidth() and setHeight()
TEST_CASE("Rectangle getWidth() and getHeight() after setWidth() and setHeight()")
{
  Rectangle r1;
  Rectangle r2(1, 3);

  r1.setWidth(5);
  r1.setHeight(7);

  r2.setWidth(9);
  r2.setHeight(11);

  REQUIRE(r1.getWidth() == 5);
  REQUIRE(r1.getHeight() == 7);
  REQUIRE(r2.getWidth() == 9);
  REQUIRE(r2.getHeight() == 11);
}


//---------------------------------------------------------------------------------------
// Tests RightTriangle default constructor sets x, y, base, and height to 0
TEST_CASE("RightTriangle default constructor getX()") 
{
  RightTriangle t;

  REQUIRE(t.getX() == 0);
  REQUIRE(t.getY() == 0); 
  REQUIRE(t.getBase() == 0);
  REQUIRE(t.getHeight() == 0);
}


// Test if RightTriangle parametized constructor changes x, y, base, and height values
TEST_CASE("RightTriangle parameterized constructor") 
{
  RightTriangle t(1, 2);

  REQUIRE(t.getX() == 0);
  REQUIRE(t.getY() == 0);
  REQUIRE(t.getBase() == 1);
  REQUIRE(t.getHeight() == 2);
}


// Test if RightTriangle parameterized constructor changes x, y, base, width values
TEST_CASE("RightTriangle full parameterized construcor") {
  RightTriangle t(1, 2, 3, 4);

  REQUIRE(t.getX() == 1);
  REQUIRE(t.getY() == 2);
  REQUIRE(t.getBase() == 3);
  REQUIRE(t.getHeight() == 4);
}


// Test if RightTriangle copy() works on default constructor
TEST_CASE("RightTriangle copy() for default constructor")
{
  RightTriangle t1;
  RightTriangle *t2 = t1.copy();

  REQUIRE(t2->getX() == 0);
  REQUIRE(t2->getY() == 0);
  REQUIRE(t2->getBase() == 0);
  REQUIRE(t2->getHeight() == 0);

  delete t2;  // Free heap memory
}


// Test if RightTriangle copy() works on parameterized constructor
TEST_CASE("RightTriangle copy() for parameterized constructor")
{
  RightTriangle t1(1, 3);
  RightTriangle *t2 = t1.copy();

  REQUIRE(t2->getX() == 0);
  REQUIRE(t2->getY() == 0);
  REQUIRE(t2->getBase() == 1);
  REQUIRE(t2->getHeight() == 3);

  delete t2;  // Free heap memory
}


// Test if Circle copy() words with full paramaterized constructor
TEST_CASE("RightTriangle copy() for full parameterized constructor") {
  RightTriangle t1(4, 5, 6, 7);
  RightTriangle *t2 = t1.copy();

  REQUIRE(t1.getX() == 4);
  REQUIRE(t1.getY() == 5);
  REQUIRE(t1.getBase() == 6);
  REQUIRE(t1.getHeight() == 7);

  delete t2;
}


// Test if RightTriangle copy() words after using setX(), setY(), setBase(), and setHeight()
TEST_CASE("RightTriangle copy() after setX(), setY(), and setRadius()")
{
  RightTriangle t1;
  RightTriangle *t2 = t1.copy();

  t2->setX(1);
  t2->setY(3);
  t2->setBase(5);
  t2->setHeight(7);

  REQUIRE(t2->getX() == 1);
  REQUIRE(t2->getY() == 3);
  REQUIRE(t2->getBase() == 5);
  REQUIRE(t2->getHeight() == 7);

  delete t2;  // Free heap memory
}


// Test that RightTriangle copy doesn't change if the original shape is changed
TEST_CASE("RightTriangle copy() doesn't change alongside it's original shape") 
{
  RightTriangle t1(1, 3);
  RightTriangle *t2 = t1.copy();

  // Switch up the values
  t2->setX(1);  
  t2->setY(3);
  t2->setBase(5);
  t2->setHeight(7);

  t1.setX(7);
  t1.setY(9); 
  t1.setBase(11);
  t1.setHeight(13);

  REQUIRE(t2->getX() == 1);
  REQUIRE(t2->getY() == 3);
  REQUIRE(t2->getBase() == 5);
  REQUIRE(t2->getHeight() == 7);

  delete t2;  // Free heap memory
}


// Test RightTriangle's derived functions setX() and setY()
TEST_CASE("RightTriangle setX() and setY()")
{
  RightTriangle t;

  t.setX(1);
  t.setY(3);

  REQUIRE(t.getX() == 1);
  REQUIRE(t.getY() == 3);
} 


// Test if RightTriangle getBase() and getHeight() works after setBase() and setHeight()
TEST_CASE("RightTriangle getBase() and getHeight() after setBase() and setHeight()")
{
  RightTriangle t1;
  RightTriangle t2(1, 3);

  t1.setBase(5);
  t1.setHeight(7);

  t2.setBase(9);
  t2.setHeight(11);

  REQUIRE(t1.getBase() == 5);
  REQUIRE(t1.getHeight() == 7);
  REQUIRE(t2.getBase() == 9);
  REQUIRE(t2.getHeight() == 11);
}


//---------------------------------------------------------------------------------------
// Test CanvasLsit default constructor. Size and listFront should have default values
TEST_CASE("CanvasList default constructor") {
  CanvasList c;

  REQUIRE(c.size() == 0);
  REQUIRE(c.isempty());
}

// Copy default constructor values into a parameterized constructor
TEST_CASE("CanvasList parameterized constructor with a default constructor") {
  CanvasList c1;
  CanvasList c2(c1);

  REQUIRE(c2.size() == 0);
  REQUIRE(c2.isempty());
}


TEST_CASE("CanvasList parameterized constructor with listSize > 0") {
  CanvasList l1;

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l1.push_back(&s);
  l1.push_back(&c);
  l1.push_back(&r);
  l1.push_back(&t);

  CanvasList l2(l1);

  REQUIRE(l2.size() == 4);
  REQUIRE(l2.shapeAt(0)->getX() == 1);
  REQUIRE(l2.shapeAt(0)->getY() == 2);
  REQUIRE(l2.shapeAt(1)->getX() == 3);
  REQUIRE(l2.shapeAt(1)->getY() == 4);
  REQUIRE(l2.shapeAt(2)->getX() == 6);
  REQUIRE(l2.shapeAt(2)->getY() == 7);
  REQUIRE(l2.shapeAt(3)->getX() == 10);
  REQUIRE(l2.shapeAt(3)->getY() == 11);
}


// Test = operator with a default constructor
TEST_CASE("CanvasList = operator with a default constructor") {
  CanvasList c1;
  CanvasList c2 = c1;

  REQUIRE(c2.size() == 0);
  REQUIRE(c2.isempty());
}


TEST_CASE("CanvasList = operator with listSize > 0") {
  CanvasList l1;

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l1.push_back(&s);
  l1.push_back(&c);
  l1.push_back(&r);
  l1.push_back(&t);

  CanvasList l2 = l1;
  REQUIRE(l2.size() == 4);
  REQUIRE(l2.shapeAt(0)->getX() == 1);
  REQUIRE(l2.shapeAt(0)->getY() == 2);
  REQUIRE(l2.shapeAt(1)->getX() == 3);
  REQUIRE(l2.shapeAt(1)->getY() == 4);
  REQUIRE(l2.shapeAt(2)->getX() == 6);
  REQUIRE(l2.shapeAt(2)->getY() == 7);
  REQUIRE(l2.shapeAt(3)->getX() == 10);
  REQUIRE(l2.shapeAt(3)->getY() == 11);
}


// Test CanvasLists's = operator overwrites a CanvasList
TEST_CASE("CanvasList = operator overwrites a CanvasList")
{
  CanvasList l1;
  CanvasList l2(l1);

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l1.push_back(&s);
  l1.push_back(&c);
  l1.push_back(&r);
  l1.push_back(&t);

  l2.push_back(&c);
  l2.push_back(&c);
  l2.push_back(&c);
  l2.push_back(&c);

  l2 = l1;
  REQUIRE(l2.shapeAt(0)->getX() == 1);
  REQUIRE(l2.shapeAt(0)->getY() == 2);
  REQUIRE(l2.shapeAt(1)->getX() == 3);
  REQUIRE(l2.shapeAt(1)->getY() == 4);
  REQUIRE(l2.shapeAt(2)->getX() == 6);
  REQUIRE(l2.shapeAt(2)->getY() == 7);
  REQUIRE(l2.shapeAt(3)->getX() == 10);
  REQUIRE(l2.shapeAt(3)->getY() == 11);
}


// Test CanvasLists's clear()
TEST_CASE("CanvasList clear() after push_back()")
{
  CanvasList l1;
  CanvasList l2(l1);

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l1.push_back(&s);
  l1.push_back(&c);
  l1.push_back(&r);
  l1.push_back(&t);
  l1.push_front(&s);
  l1.push_front(&c);
  l1.push_front(&r);
  l1.push_front(&t);

  l2.push_back(&s);
  l2.push_back(&c);
  l2.push_back(&r);
  l2.push_back(&t);
  l2.push_front(&s);
  l2.push_front(&c);
  l2.push_front(&r);
  l2.push_front(&t);

  l1.clear();
  l2.clear();

  REQUIRE(l1.size() == 0);
  REQUIRE(l1.isempty());
  REQUIRE(l2.size() == 0);
  REQUIRE(l2.isempty());
}


// Test CanvasList push_back() and shapeAt()
TEST_CASE("CanvasList push_back() and shapeAt() on default and parameterized constructor") {
  CanvasList l1;
  CanvasList l2(l1);

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l1.push_back(&s);
  l1.push_back(&c);
  l1.push_back(&r);
  l1.push_back(&t);

  l2.push_back(&s);
  l2.push_back(&c);
  l2.push_back(&r);
  l2.push_back(&t);

  REQUIRE(l1.size() == 4);
  REQUIRE(l1.shapeAt(0)->getX() == 1);
  REQUIRE(l1.shapeAt(0)->getY() == 2);
  REQUIRE(l1.shapeAt(1)->getX() == 3);
  REQUIRE(l1.shapeAt(1)->getY() == 4);
  REQUIRE(l1.shapeAt(2)->getX() == 6);
  REQUIRE(l1.shapeAt(2)->getY() == 7);
  REQUIRE(l1.shapeAt(3)->getX() == 10);
  REQUIRE(l1.shapeAt(3)->getY() == 11);

  REQUIRE(l2.size() == 4);
  REQUIRE(l2.shapeAt(0)->getX() == 1);
  REQUIRE(l2.shapeAt(0)->getY() == 2);
  REQUIRE(l2.shapeAt(1)->getX() == 3);
  REQUIRE(l2.shapeAt(1)->getY() == 4);
  REQUIRE(l2.shapeAt(2)->getX() == 6);
  REQUIRE(l2.shapeAt(2)->getY() == 7);
  REQUIRE(l2.shapeAt(3)->getX() == 10);
  REQUIRE(l2.shapeAt(3)->getY() == 11);
}


TEST_CASE("CanvasList push_front() and shapeAt() on default constructor") {
  CanvasList l;

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l.push_front(&s);
  l.push_front(&c);
  l.push_front(&r);
  l.push_front(&t);

  REQUIRE(l.size() == 4);
  REQUIRE(l.shapeAt(3)->getX() == 1);
  REQUIRE(l.shapeAt(3)->getY() == 2);
  REQUIRE(l.shapeAt(2)->getX() == 3);
  REQUIRE(l.shapeAt(2)->getY() == 4);
  REQUIRE(l.shapeAt(1)->getX() == 6);
  REQUIRE(l.shapeAt(1)->getY() == 7);
  REQUIRE(l.shapeAt(0)->getX() == 10);
  REQUIRE(l.shapeAt(0)->getY() == 11);
}


// Test insert_after() on default constructor
TEST_CASE("CanvasList insert_after() and shapeAt() on default constructor") {

  CanvasList l;

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);
  Shape s2(14, 15);
  Circle c2(16, 17, 18);

  l.push_back(&s);
  l.push_back(&c);
  l.push_back(&r);
  l.push_back(&t);

  l.insertAfter(0, &s2);      // Insert at index 1
  l.insertAfter(4, &c2);      // Insert at new index 5
  l.insertAfter(-2, &s2);     // Out of bounds. Do nothing
  l.insertAfter(10, &s2);     // Out of bounds. Do nothing

  REQUIRE(l.size() == 6);
  REQUIRE(l.shapeAt(0)->getX() == 1);
  REQUIRE(l.shapeAt(0)->getY() == 2);
  REQUIRE(l.shapeAt(1)->getX() == 14);
  REQUIRE(l.shapeAt(1)->getY() == 15);
  REQUIRE(l.shapeAt(2)->getX() == 3);
  REQUIRE(l.shapeAt(2)->getY() == 4);
  REQUIRE(l.shapeAt(3)->getX() == 6);
  REQUIRE(l.shapeAt(3)->getY() == 7);
  REQUIRE(l.shapeAt(4)->getX() == 10);
  REQUIRE(l.shapeAt(4)->getY() == 11);
  REQUIRE(l.shapeAt(5)->getX() == 16);
  REQUIRE(l.shapeAt(5)->getY() == 17);
}


// Test removeAt() on default constructor
TEST_CASE("CanvasList removeAt() on default constructor") {
  CanvasList l;

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);
  Shape s2(14, 15);
  Circle c2(16, 17, 18);

  l.push_back(&s);
  l.push_back(&c);   
  l.push_back(&r);
  l.push_back(&t);
  l.push_back(&s2);
  l.push_back(&c2);

  l.removeAt(5);      // Delete last node
  l.removeAt(2);      // Delete middle node
  l.removeAt(0);      // Delete first node
  l.removeAt(-2);     // Out of bounds. Do nothing
  l.removeAt(10);     // Out of bounds. Do nothing

  REQUIRE(l.size() == 3);
  REQUIRE(l.shapeAt(0)->getX() == 3);
  REQUIRE(l.shapeAt(0)->getY() == 4);
  REQUIRE(l.shapeAt(1)->getX() == 10);
  REQUIRE(l.shapeAt(1)->getY() == 11);
  REQUIRE(l.shapeAt(2)->getX() == 14);
  REQUIRE(l.shapeAt(2)->getY() == 15);
}


// Test CanvasLists's pop_front()
TEST_CASE("CanvasList pop_front() on default constructor")
{
  CanvasList l;
  Shape *result = l.pop_front();
  REQUIRE(result == NULL);

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l.push_back(&s);
  l.push_back(&c);   
  l.push_back(&r);
  l.push_back(&t);
  Shape *result1 = l.pop_front();
  Shape *result2 = l.pop_front();

  REQUIRE(result1->getX() == 1);
  REQUIRE(result1->getY() == 2);
  REQUIRE(result2->getX() == 3);
  REQUIRE(result2->getY() == 4);

  REQUIRE(l.size() == 2);
  REQUIRE(l.shapeAt(0)->getX() == 6);
  REQUIRE(l.shapeAt(0)->getY() == 7);
  REQUIRE(l.shapeAt(1)->getX() == 10);
  REQUIRE(l.shapeAt(1)->getY() == 11);

  delete result1;
  delete result2;
}


// Test CanvasLists's pop_back()
TEST_CASE("CanvasList pop_back() on default constructor")
{
  CanvasList l;
  Shape *result = l.pop_back();
  REQUIRE(result == NULL);

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);
  Rectangle r(6, 7, 8, 9);
  RightTriangle t(10, 11, 12, 13);

  l.push_back(&s);
  l.push_back(&c);   
  l.push_back(&r);
  l.push_back(&t);
  Shape *result1 = l.pop_back();
  Shape *result2 = l.pop_back();

  REQUIRE(result1->getX() == 10);
  REQUIRE(result1->getY() == 11);
  REQUIRE(result2->getX() == 6);
  REQUIRE(result2->getY() == 7);

  REQUIRE(l.size() == 2);
  REQUIRE(l.shapeAt(0)->getX() == 1);
  REQUIRE(l.shapeAt(0)->getY() == 2);
  REQUIRE(l.shapeAt(1)->getX() == 3);
  REQUIRE(l.shapeAt(1)->getY() == 4);

  delete result1;
  delete result2;
}


// Test CanvasLists front()
TEST_CASE("CanvaList front()") {
  CanvasList l;
  REQUIRE(l.front() == NULL);

  // Declare various Shapes
  Shape s(1, 2);
  Circle c(3, 4, 5);

  l.push_front(&s);
  REQUIRE(l.front()->value->getX() == 1);
  REQUIRE(l.front()->value->getY() == 2);

  l.push_front(&c);
  REQUIRE(l.front()->value->getX() == 3);
  REQUIRE(l.front()->value->getY() == 4);  
}


// Test CanvasList isempty()
TEST_CASE("CanvasList isempty()") {
  CanvasList l;
  REQUIRE(l.isempty());
  REQUIRE(l.shapeAt(-1) == NULL);
  REQUIRE(l.shapeAt(3) == NULL);

  Shape s(1, 2);
  Circle c(3, 4, 5);

  l.push_back(&s);
  l.push_back(&c);
  REQUIRE(l.isempty() == false);
}


TEST_CASE("CanvasList find()") {
  CanvasList l;
  REQUIRE(l.find(1, 2) == -1);

  Shape s(1, 2);

  l.push_back(&s);
  l.push_back(&s);

  REQUIRE(l.find(1, 2) == 0);
}