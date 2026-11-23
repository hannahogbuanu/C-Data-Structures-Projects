/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Statistics Project
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;


void testsum2();
void testmedian();
void testmean();
void testmax();
void testmin();
void testmedian2();
void teststdev();
void testperc();
void testfilter();
void testperc2();



void testsum2() {
  cout << "testsum2" << endl;
  
  vector<double> a = {10,4,-3,2,6};
  assert(sum(a) == 19);
  cout << "PASS!" << endl;
}

void testmean() {
  cout << "testmean" << endl;
  
  vector<double> a = {10,4,3.5,2,6};
  
  assert(mean(a) == 5.1);

  cout << "PASS!" << endl;
}

void testmedian() {
  cout << "testmedian" << endl;
  
  vector<double> a = {10,4,3.5,2,6};
  
  assert(median(a) == 4);

  cout << "PASS!" << endl;
}

void testmedian2() {
  cout << "testmedian2" << endl;
  
  vector<double> a = {10,4,3.5,2,6,3};
 
  assert(median(a) == 3.75);

  cout << "PASS!" << endl;
}

void testmin() {
  cout << "testmin" << endl;
  
  vector<double> a = {10,4,3.5,2,6,3};
 
  assert(min(a) == 2);

  cout << "PASS!" << endl;
}

void testmax() {
  cout << "testmax" << endl;
  
  vector<double> a = {4,10,3.5,2,6,3};
 
  assert(max(a) == 10);

  cout << "PASS!" << endl;
}

void teststdev() {
  cout << "teststdev" << endl;
  
  vector<double> a = {1.5,2.5,3.5};
  
  assert(stdev(a) == 1);
  cout << "PASS!" << endl;
}

void testperc() {
  cout << "testperc" << endl;
  
  vector<double> a = {35,20,15,50,40};
  double p = 0.4;
  
  assert(percentile(a, p) == 29);
  cout << "PASS!" << endl;
}

void testperc2() {
  cout << "testperc2" << endl;
  vector<double> a = {11.5,9.6,9.9,10.1,11.2,9.2,7.8,12.3,10.1,10.9};
  double p = 1;
  
  assert(percentile(a, p) == 12.3);
  cout << "PASS!" << endl;
}

void testfilter() {
  cout << "testfilter" << endl;
  
  vector<double> a = {35,20,15,50,40,4.5,67,8};
  vector<double> criterium = {0,0,2,1,1,2,1,0};
  double targeti = 1;
  vector<double> medium = filter(a, criterium, targeti);
  assert(medium.size() == 3);
  assert(sum(medium) == 50 + 40 + 67);
  cout << "PASS!" << endl;
}

// Add prototypes for you test functions here.

int main() {

  testsum2();
  testmedian();
  testmean();
  testmax();
  testmin();
  testmedian2();
  teststdev();
  testperc();
  testfilter();
  testperc2();

  // Call your test functions here

  return 0;
}



// Add the test function implementations here.
