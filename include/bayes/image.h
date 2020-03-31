// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <vector>

using std::vector;


namespace bayes {

constexpr size_t kImageSize = 28;

struct Image {
  int number_class;
  vector<vector<int>> pixels;
  Image(vector<vector<int>>&, int);

};

}  // namespace bayes

#endif  // BAYES_IMAGE_H_
