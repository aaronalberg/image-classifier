// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>
#include <bayes/image.h>
using namespace bayes;



string images_path =
    "/Users/aaronalberg/CLionProjects/naive-bayes-aaronalberg/"
    "data/digitdata/testimages";
string labels_path =
    "/Users/aaronalberg/CLionProjects/naive-bayes-aaronalberg/"
    "data/digitdata/testlabels";
Model model;
Image image_to_test;
ifstream model_stream;
string next_line;
vector<double> class_proportions;
vector<vector<vector<double>>> pixel_proportions;

void Prepare(int index) {
  model.trainModel();
  image_to_test = ParseFiles(images_path, labels_path)[index];
  model_stream.open("model.txt");
  getline(model_stream, next_line);
  class_proportions = SplitProportions(next_line, kNumClasses);
  pixel_proportions = MakeProportionGrids(model_stream, next_line);
}

TEST_CASE("Prepare Regular Row", "[model][prepare-row]") {
  vector<int> test_row =
      {0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1};
  string test_string = " #+#   ++ #+#   ++ #+#   ++#";
  REQUIRE(Model::prepareRow(test_string) == test_row);
}

TEST_CASE("Prepare empty row", "[model][prepare-row]") {
  vector<int> test_row(bayes::kImageSize, 0);
  string test_string = "                            ";
  REQUIRE(Model::prepareRow(test_string) == test_row);
}

TEST_CASE("Prepare complete row", "[model][prepare-row]") {
  vector<int> test_row(bayes::kImageSize, 1);
  string test_string = "#+##++#+##++#+##++#+##++++##";
  REQUIRE(Model::prepareRow(test_string) == test_row);
}

TEST_CASE("Model is written", "[model][write-model-file") {
  model.trainModel();
  ifstream stream("model.txt");
  REQUIRE(stream.good());
}

TEST_CASE("Model is not random", "[model]") {
  model.trainModel();

  //threshold to be above lucky random choosing
  REQUIRE(ClassifyAllImages(images_path, labels_path) > 15);
}

TEST_CASE("Model is very effective", "[model]") {
  model.trainModel();
  REQUIRE(ClassifyAllImages(images_path, labels_path) > 70);
}

TEST_CASE("Find highest index", "[classifier]") {
  vector<double> unsorted =
      {-1.0, -4.5, -3.7, -0.05, -45, -5.2, -1.0, -4.5, -3.7, -0.05, -45, -5.2};
  REQUIRE(FindHighestIndex(unsorted) == 3);
}

TEST_CASE("Find highest index equal", "[classifier]") {
  vector<double> equal =
      {-5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2};
  REQUIRE(FindHighestIndex(equal) == 0);
}

TEST_CASE("Split class proportions", "[classifier]") {
  string to_test = ".119 .099 .103 .098 .132 .089 .88 .90 .121 .90";
  vector<double> result =
      {.119, .099, .103, .098, .132, .089, .88, .90, .121, .90};
  REQUIRE(SplitProportions(to_test, kNumClasses) == result);
}

TEST_CASE("Split pixel proportions", "[classifier]") {
  string to_test = ".119 .099 .103 .098 .132 .089 .88 .90 .121 .90 .119 .099 "
                  ".103 .098 .132 .089 .88 .90 .121 .90 "
                  ".119 .099 .103 .098 .132 .089 .88 .90 ";
  vector<double> result = {.119, .099, .103, .098, .132, .089, .88,
                           .90, .121, .90, .119, .099, .103, .098, .132,
                           .089, .88, .90, .121, .90, .119, .099, .103,
                           .098,.132, .089, .88, .90};
  REQUIRE(SplitProportions(to_test, kImageSize) == result);
}

TEST_CASE("Correct number of images tested", "[classifier]") {
  REQUIRE(ParseFiles(images_path, labels_path).size() == 1000);
}

TEST_CASE("Proportions grid correct size", "[classifier]") {
  Prepare(0);
  REQUIRE(pixel_proportions.size() == kNumClasses);
  for (int i = 0; i < kNumClasses; i++) {
    REQUIRE(pixel_proportions[i].size() == kImageSize);
  }
  model_stream.close();
}

TEST_CASE("Correct number of images trained", "[model]") {
  Model different_model;
  different_model.trainModel();
  REQUIRE(different_model.image_count_ == 5000);
}

TEST_CASE("Correct classification 2", "[classifier]") {
  Prepare(50);
  REQUIRE(ClassifyImage(image_to_test, class_proportions, pixel_proportions) == 2);
  model_stream.close();
}

TEST_CASE("Correct classification 0", "[classifier]") {
  Prepare(1);
  REQUIRE(ClassifyImage(image_to_test, class_proportions, pixel_proportions) == 0);
  model_stream.close();
}

TEST_CASE("Not cheating","[classifier]") {
  Prepare(0);
  REQUIRE(ClassifyImage(image_to_test, class_proportions, pixel_proportions) != 9);
  model_stream.close();
}


