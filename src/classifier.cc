// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/classifier.h>

namespace bayes {

int classifyImage(Image &image, vector<double> &class_proportions,
    vector<vector<vector<double>>> &pixel_proportions) {

  vector<double> comparable_probs(kNumClasses, 1);
  for (int num = 0; num < kNumClasses; num++) {
    comparable_probs[num] += class_proportions[num];
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        if (image.pixels[i][j] == 1) {
          comparable_probs[num] += log(pixel_proportions[num][i][j]);
        } else {
          comparable_probs[num] += log(1 - pixel_proportions[num][i][j]);
        }
      }
    }
  }

  return findHighestIndex(comparable_probs);
}

int findHighestIndex(vector<double> &comparable_list) {
  int highest_index = 0;
  double highest_value = std::numeric_limits<double>::lowest();
  for (int i = 0; i < kNumClasses; i++) {
    if (comparable_list[i] > highest_value) {
      highest_index = i;
      highest_value = comparable_list[i];
    }
  }

  return highest_index;
}




}  // namespace bayes

