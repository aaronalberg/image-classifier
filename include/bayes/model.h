// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include <bayes/image.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::stoi;
using std::ofstream;


namespace bayes {

// 0-9 inclusive.
constexpr size_t kNumClasses = 10;
constexpr double kLaplace = .1;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
class Model {

 private:
  vector<bayes::Image> parseTrainingFiles();
  int image_count_;
  vector<double> class_proportion_;
  vector<vector<vector<double>>> pixel_proportions;
  void writeModelFile();

 public:
  void trainModel();
  static vector<int> prepareRow(string&);
};

}  // namespace bayes

#endif  // BAYES_MODEL_H_
