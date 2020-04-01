// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include <bayes/image.h>
#include <bayes/model.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::stod;
using std::vector;


namespace bayes {

int ClassifyImage(Image&, vector<double>&, vector<vector<vector<double>>>&);
int FindHighestIndex(vector<double>&);
vector<vector<vector<double>>> MakeProportionGrids(ifstream&, string&);
vector<double> SplitProportions(string&, int);
vector<Image> ParseFiles(const string&, const string&);
double ClassifyAllImages(string, string);

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

