// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/model.h>

namespace bayes {

void Model::trainModel() {
  vector<bayes::Image> images = readTrainingFiles();
  std::cout << image_count_ << endl;
  std::cout << class_count_[0] << endl;



}



vector<bayes::Image> Model::readTrainingFiles() {
  ifstream training_images_;
  ifstream training_labels_;
  training_images_.open("data/digitdata/trainingimages");
  training_labels_.open("data/digitdata/traininglabels");

  string next_line_images;
  string next_line_labels;
  int label_value;
  int line_count = 0;
  vector<bayes::Image> images;
  grid.assign(kImageSize, vector<int>(kImageSize, 1));
  class_count_.assign(kNumClasses,0);

  while (getline (training_images_, next_line_images)) {

    vector<int> row;
    for (int i = 0; i < bayes::kImageSize; i++) {
      if (next_line_images.at(i) == ' ') {
        row.push_back(0);
      }

      if (next_line_images.at(i) == '+'
          || (next_line_images.at(i) == '#')) {
        row.push_back(1);
      }
    }
    grid[line_count % kImageSize] = row;


    if (line_count % kImageSize == 0 && line_count != 0) {
      image_count_++;
      getline(training_labels_, next_line_labels);
      label_value = stoi(next_line_labels);
      std::cout << "label " << label_value << endl;
      class_count_[label_value] ++;
      std::cout << "yuh " << class_count_[label_value] << endl;
      bayes::Image current_image(grid, label_value);
      images.push_back(current_image);
    }

    line_count++;
    if (line_count > 1000) {
      break;
    }

  }

  training_images_.close();
  training_labels_.close();
  return images;
}

}  // namespace bayes

