// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/model.h>

namespace bayes {

void Model::trainModel() {
  vector<bayes::Image> images = readTrainingFiles();
  pixel_proportions.assign(kNumClasses,
      vector<vector<double>>(kImageSize, vector<double>(kImageSize)));
  vector<vector<vector<int>>> class_count(kNumClasses, vector<vector<int>>(kImageSize, vector<int>(kImageSize)));
  for (bayes::Image &image : images) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
       if (image.pixels[i][j] == 1) {
         pixel_proportions[image.number_class][i][j]++;
       }
        class_count[image.number_class][i][j]++;
      }
    }
  }

  for (int num = 0; num < kNumClasses; num++) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        double laplace_one = (kLaplace + pixel_proportions[num][i][j]);
        double laplace_two = (2 * kLaplace) + class_count[num][i][j];
        pixel_proportions[num][i][j] = laplace_one / laplace_two;
      }
    }
  }

  ofstream model("model.txt");
  for (int i = 0; i < kNumClasses; i++) {
    model << class_proportion_[i] << " ";
  }

  model << endl;
  for (vector<vector<double>> &vec : pixel_proportions) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        model << vec[i][j] << " ";
      }

      model << endl;
    }
  }

  model.close();
}

vector<bayes::Image> Model::readTrainingFiles() {
  ifstream training_images_("data/digitdata/trainingimages");
  ifstream training_labels_("data/digitdata/traininglabels");

  string next_line_images;
  string next_line_labels;
  int label_value;
  int line_count = 1;
  vector<bayes::Image> images;
  grid.assign(kImageSize, vector<int>(kImageSize, 1));
  class_proportion_.assign(kNumClasses,0);

  while (getline (training_images_, next_line_images)) {

    vector<int> row = prepareRow(next_line_images);
    grid[line_count % kImageSize] = row;

    if (line_count % kImageSize == 0) {
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

vector<int> Model::prepareRow(string& next_line) {
  vector<int> row;
  for (int i = 0; i < bayes::kImageSize; i++) {
    if (next_line.at(i) == ' ') {
      row.push_back(0);
    }

    if (next_line.at(i) == '+'
        || (next_line.at(i) == '#')) {
      row.push_back(1);
    }
  }

  return row;
}

}  // namespace bayes

