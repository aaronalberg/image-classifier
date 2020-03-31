// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;
using namespace bayes;


vector<bayes::Image> readTestFiles(string images_path, string labels_path) {
  ifstream testing_images_(images_path);
  ifstream testing_labels_(labels_path);

  string next_line_images;
  string next_line_labels;
  int label_value;
  int line_count = 1;
  vector<bayes::Image> images;
  vector<vector<int>> grid;
  grid.assign(kImageSize, vector<int>(kImageSize, 1));

  while (getline (testing_images_, next_line_images)) {

    vector<int> row = Model::prepareRow(next_line_images);
    grid[line_count % kImageSize] = row;

    if (line_count % kImageSize == 0) {
      getline(testing_labels_, next_line_labels);
      label_value = stoi(next_line_labels);
      bayes::Image current_image(grid, label_value);
      images.push_back(current_image);
    }

    line_count++;
  }

  testing_images_.close();
  testing_labels_.close();
  return images;
}

vector<double> splitClassProportions(string &line) {

  //https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
  istringstream stream(line);
  vector<double> proportions;
  int count_iteration = 0;
  while (stream && count_iteration < kNumClasses) {
    count_iteration++;
    string word;
    stream >> word;
    proportions.push_back(stod(word));
  }

  return proportions;
}

vector<double> splitPixelProportions(string &line) {

  //https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
  vector<double> row;
  istringstream sstream(line);
  int count_iteration = 0;
  while (sstream && count_iteration < kImageSize) {
    count_iteration++;
    string word;
    sstream >> word;
    row.push_back(stod(word));
  }

  return row;
}

vector<vector<vector<double>>>
    generateProportionGrids(ifstream &model_stream, string &line) {
  vector<vector<vector<double>>> pixel_proportions;
  for (int i = 0; i < kNumClasses; i++) {
    vector<vector<double>> grid;
    for (int j = 0; j < kImageSize; j++) {
      getline(model_stream, line);
      vector<double> row = splitPixelProportions(line);
      grid.push_back(row);
    }

    pixel_proportions.push_back(grid);
  }

  return pixel_proportions;
}


int main(int argc, char** argv) {

  ifstream model_stream("model.txt");
  if (!model_stream.good()) {
    bayes::Model model;
    model.trainModel();
  }

  ifstream model("model.txt");
  string next_line;
  getline(model, next_line);
  vector<double> class_proportions = splitClassProportions(next_line);
  vector<vector<vector<double>>> pixel_proportions =
      generateProportionGrids(model, next_line);
  vector<bayes::Image> imagesToTest =
      readTestFiles(argv[1], argv[2]);
  int image_count = 0;
  int correct_count = 0;
  for (bayes::Image &image : imagesToTest) {
    image_count++;
    int return_class =
        bayes::classifyImage(image, class_proportions, pixel_proportions);
    if (return_class == image.number_class) {
      correct_count++;
    }
  }

  model.close();
  cout << "RESULTS" << endl;
  cout << "Image count: " << image_count << endl;
  cout << ((double) correct_count / (double) image_count) * 100 << "% correct" << endl;
  return EXIT_SUCCESS;
}
