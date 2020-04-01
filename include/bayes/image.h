// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <vector>

using std::vector;

namespace bayes {

constexpr size_t kImageSize = 28;

struct Image {
  Image(vector<vector<int>>&, int);
  int& getNumberClass();
  vector<vector<int>>& getPixels();

 private:
  int number_class;
  vector<vector<int>> pixels;

};

}  // namespace bayes

#endif  // BAYES_IMAGE_H_
