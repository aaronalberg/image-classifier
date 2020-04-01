// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/model.h>

namespace bayes {

void Model::trainModel() {
  vector<Image> images = parseTrainingFiles();
  pixel_proportions_.assign(kNumClasses,
      vector<vector<double>>(kImageSize, vector<double>(kImageSize)));
  vector<vector<vector<int>>> class_count(kNumClasses, vector<vector<int>>(kImageSize, vector<int>(kImageSize)));
  for (Image &image : images) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
       if (image.getPixels()[i][j] == 1) {
         pixel_proportions_[image.getNumberClass()][i][j]++;
       }

        class_count[image.getNumberClass()][i][j]++;
      }
    }
  }

  for (int num = 0; num < kNumClasses; num++) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        double laplace_one = (kLaplace + pixel_proportions_[num][i][j]);
        double laplace_two = (2 * kLaplace) + class_count[num][i][j];
        pixel_proportions_[num][i][j] = laplace_one / laplace_two;
      }
    }
  }

  writeModelFile();
}

void Model::writeModelFile() {
  ofstream model("model.txt");
  for (int i = 0; i < kNumClasses; i++) {
    model << class_proportions_[i] << " ";
  }

  model << endl;
  for (vector<vector<double>> &vec : pixel_proportions_) {
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        model << vec[i][j] << " ";
      }

      model << endl;
    }
  }

  model.close();
}

vector<Image> Model::parseTrainingFiles() {
  ifstream training_images_("/Users/aaronalberg/CLionProjects/naive-bayes-aaronalberg/data/digitdata/trainingimages");
  ifstream training_labels_("/Users/aaronalberg/CLionProjects/naive-bayes-aaronalberg/data/digitdata/traininglabels");

  string next_line_images, next_line_labels;
  int label_value, line_count = 1;
  vector<Image> images;
  vector<vector<int>> grid(kImageSize, vector<int>(kImageSize, 1));
  class_proportions_.assign(kNumClasses,0);
  while (getline (training_images_, next_line_images)) {
    vector<int> row = prepareRow(next_line_images);
    grid[line_count % kImageSize] = row;

    if (line_count % kImageSize == 0) {
      image_count_++;
      getline(training_labels_, next_line_labels);
      label_value = stoi(next_line_labels);
      class_proportions_[label_value] ++;
      Image current_image(grid, label_value);
      images.push_back(current_image);
    }

    line_count++;
  }

  training_images_.close();
  training_labels_.close();
  for (double &class_entry : class_proportions_) {
    class_entry /= image_count_;
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

