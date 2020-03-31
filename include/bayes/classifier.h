// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef BAYES_CLASSIFIER_H_
#define BAYES_CLASSIFIER_H_

#include <bayes/image.h>
#include <bayes/model.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::stod;

namespace bayes {

int classifyImage(Image&, vector<double>&, vector<vector<vector<double>>>&);

}  // namespace bayes

#endif  // BAYES_CLASSIFIER_H_

