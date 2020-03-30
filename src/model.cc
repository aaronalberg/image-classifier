// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/model.h>

namespace bayes {

void Model::trainModel() {
  vector<bayes::Image> images = readTrainingFiles();
  std::cout << image_count_ << endl;
  std::cout << class_proportion_[5] << endl;

  //each element of the vector is a grid for each class
  //https://stackoverflow.com/questions/19484103/
  // how-to-initialize-3-dimension-vector-with-the-size-in-c
  vector<vector<vector<double>>> proportions(kNumClasses,
      vector<vector<double>>(kImageSize, vector<double>(kImageSize)));


  for (bayes::Image &image : images) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
       if (image.pixels[i][j] == 1) {
         proportions[image.trainingClass][i][j]++;
       }
      }
    }
  }
  ofstream model("model.txt");
  for (vector<vector<double>> &vec : proportions) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        model << vec[i][j] << " ";
      }

      model << "\n";
    }

    model << "\n";
  }
  model.close();

  /*

  for (vector<vector<double>> &field : proportions) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        field[i][j] = (field[i][j] + kLaplace) / (kLaplace + image_count_);
        field[i][j] = log(field[i][j]);
      }
    }
  }
   */

}

vector<bayes::Image> Model::readTrainingFiles() {
  ifstream training_images_;
  ifstream training_labels_;
  training_images_.open("data/digitdata/trainingimages");
  training_labels_.open("data/digitdata/traininglabels");

  string next_line_images;
  string next_line_labels;
  int label_value;
  int line_count = 1;
  vector<bayes::Image> images;
  grid.assign(kImageSize, vector<int>(kImageSize, 1));
  class_proportion_.assign(kNumClasses,0);

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
      class_proportion_[label_value] ++;
      bayes::Image current_image(grid, label_value);
      images.push_back(current_image);



    }

    line_count++;
  }

  training_images_.close();
  training_labels_.close();
  for (double &class_entry : class_proportion_) {
    class_entry = class_entry / image_count_;
  }

  return images;
}

}  // namespace bayes

