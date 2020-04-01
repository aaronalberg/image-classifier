// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/image.h>

namespace bayes {

Image::Image(vector<vector<int>> &grid, int value) {
  pixels = grid;
  number_class = value;
}

int& Image::getNumberClass() {
  return number_class;
}

vector<vector<int>>& Image::getPixels() {
  return pixels;
}

}  // namespace bayes

