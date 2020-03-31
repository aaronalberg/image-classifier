// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/image.h>

namespace bayes {

Image::Image(vector<vector<int>> &grid) {
  pixels = grid;
}

Image::Image(vector<vector<int>> &grid, int value) {
  pixels = grid;
  number_class = value;
}

}  // namespace bayes

