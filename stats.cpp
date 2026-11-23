#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf

using namespace std;

int count(vector<double> v) {
  return v.size();
}

double sum(vector<double> v) {
  double sums = 0;
  for(int index = 0; index < v.size(); ++index) {
    sums = sums + v[index];
  }
  return sums;
}

double mean(vector<double> v) {
  return sum(v)/count(v);
}

double median(vector<double> v) {
  sort(v.begin(), v.end());
  if (v.size() % 2 == 0) {
    int divide = v.size()/2.0;
    return (v[divide] + v[divide-1])/2.0;
  }
  else {
    double divided = v.size()/2.0;
    return (v[divided-0.5]); 
  }
}

double min(vector<double> v) {
  double minimum = v[0];
  for (int index = 0; index < v.size(); ++index) {
    if (v[index] < minimum){
      minimum = v[index];
    }
    else{
      minimum = minimum;
    }
  }
  return minimum; 

}

double max(vector<double> v) {
  double maximum = v[0];
  for (int index = 0; index < v.size(); ++index) {
    if (v[index] > maximum){
      maximum = v[index];
    }
    else{
      maximum = maximum;
    }
  }
  return maximum; 
}

double stdev(vector<double> v) {
  
  double addition = 0;
  for (int index = 0; index < v.size(); ++index) {
    sqrt(1.0/(v.size() - 1));
    addition = addition + pow((v[index] - mean(v)), 2);
  }

  double stndev = sqrt((1.0/(v.size()-1))*(addition));
  return stndev;
}

double percentile(vector<double> v, double p) {
  if (p == 1) {
    return max(v);
  }
  else {
    sort(v.begin(), v.end());
    double rank = p*(v.size()-1) + 1;
    double intpart = 0;
    double fractpart = 0;
    fractpart = modf(rank, &intpart);
    double perc = v[intpart - 1] + (fractpart * (v[intpart] - v[intpart - 1]));
    return perc;
  }  
  

  
}

vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {
  vector<double> newv = {};
  for (int index = 0; index < v.size(); ++index){
    if (criteria[index] == target) {
      newv.push_back(v[index]);
    }
    
  }
  return newv;
}
