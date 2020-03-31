// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include <bayes/image.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using std::cout;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::stoi;
using std::ofstream;


namespace bayes {




/*
 * We've given you a starter struct to represent the model.
 * You are totally allowed to delete, change, move, rename, etc. this struct
 * however you like! In fact, we encourage it! It only exists as a starting
 * point of reference.
 *
 * In our probabilities array we have a final dimension [2], which represents
 * the individual probabilities that a pixel for a class is either shaded or
 * not shaded. Since the probability that a pixel is shaded is just
 * (1 - probability not shaded), we COULD have deleted that final dimension
 * (and you can do so if you want to), but we left it in so that you could
 * see how the model would need to change if we were to keep track of the
 * probability that a pixel is white vs. gray vs. dark gray vs. black.
 *
 * You can delete this comment once you're done with it.
 */

// 0-9 inclusive.
constexpr size_t kNumClasses = 10;
// Shaded or not shaded.
constexpr size_t kNumShades = 2;
constexpr size_t kLaplace = 1;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
class Model {

 private:
  vector<vector<int>> grid;
  vector<bayes::Image> readTrainingFiles();
  int image_count_;
  vector<double> class_proportion_;
  vector<vector<vector<double>>> pixel_proportions;

 public:
  void trainModel();
  static vector<int> prepareRow(string&);
};

}  // namespace bayes

#endif  // BAYES_MODEL_H_
