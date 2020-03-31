// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/image.h>
#include <bayes/model.h>
#include <gflags/gflags.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;
using namespace bayes;



// TODO(you): Change the code below for your project use case.

DEFINE_string(name, "Aaron", "Your first name");
DEFINE_bool(happy, false, "Whether the greeting is a happy greeting");





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

vector<int> splitPixelProportions(string &line) {
  vector<int> row;
  istringstream sstream(line);
  int count_iteration = 0;
  while (sstream && count_iteration < kImageSize) {
    count_iteration++;
    string word;
    sstream >> word;
    row.push_back(stoi(word));
  }

  return row;
}

vector<vector<vector<int>>>
    generateProportionGrids(ifstream &model_stream, string &line) {
  vector<vector<vector<int>>> proportions;
  for (int i = 0; i < kNumClasses; i++) {
    vector<vector<int>> grid;
    for (int j = 0; j < kImageSize; j++) {
      getline(model_stream, line);
      vector<int> row = splitPixelProportions(line);
      grid.push_back(row);
    }

    proportions.push_back(grid);
  }
  while (getline(model_stream, line)) {
    istringstream stream(line);
    vector<int> row;


  }

  return proportions;
}


int main(int argc, char** argv) {
  gflags::SetUsageMessage(
      "Greets you with your name. Pass --helpshort for options.");

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_name.empty()) {
    std::cerr << "Please provide a name via the --name flag." << std::endl;
    return EXIT_FAILURE;
  }

  const std::string puncutation = FLAGS_happy ? "!" : ".";
  cout << "Hello, " << FLAGS_name << puncutation << endl;

  ifstream model_stream("model.txt");
  if (!model_stream.good()) {
    bayes::Model model;
    model.trainModel();
  }

  ifstream model("model.txt");
  string next_line;
  getline(model, next_line);
  vector<double> class_proportions = splitClassProportions(next_line);
  vector<vector<vector<int>>> proportions =
      generateProportionGrids(model, next_line);
  vector<bayes::Image> imagesToTest =
      readTestFiles(argv[1], argv[2]);
  int image_count = 0;
  int correct_count = 0;
  for (bayes::Image &image : imagesToTest) {
    image_count++;
    int return_class =
        bayes::classifyImage(image, class_proportions, proportions);
    if (return_class == image.number_class) {
      correct_count++;
    }
  }
  model.close();

  cout << "RESULTS" << endl;
  cout << "Image count: " << image_count << endl;
  cout << (correct_count / image_count) << "% correct" << endl;

  return EXIT_SUCCESS;
}
