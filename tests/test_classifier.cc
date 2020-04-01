// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>
#include <bayes/image.h>
using namespace bayes;

string images = "/Users/aaronalberg/CLionProjects/naive-bayes-aaronalberg/data/digitdata/testimages";
string labels = "/Users/aaronalberg/CLionProjects/naive-bayes-aaronalberg/data/digitdata/testlabels";
bayes::Model model;

TEST_CASE("Prepare Regular Row", "[model][prepare-row]") {
  vector<int> test_row = {0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1};
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
  REQUIRE(ClassifyAllImages(images, labels) > 15);
}

TEST_CASE("Model is very effective", "[model]") {
  model.trainModel();
  REQUIRE(ClassifyAllImages(images, labels) > 70);
}

TEST_CASE("Find highest index", "[classifier]") {
  vector<double> unsorted = {-1.0, -4.5, -3.7, -0.05, -45, -5.2, -1.0, -4.5, -3.7, -0.05, -45, -5.2};
  REQUIRE(FindHighestIndex(unsorted) == 3);
}

TEST_CASE("Find highest index equal", "[classifier]") {
  vector<double> equal = {-5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2, -5.2};
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

TEST_CASE("Correct number of images parsed", "[classifier]") {
  REQUIRE(ParseFiles(images, labels).size() == 1000);
}

TEST_CASE("Correct number of images trained", "[model]") {

  //to make sure count from previous tests doesn't carry over
  Model new_model;
  new_model.trainModel();
  REQUIRE(model.image_count_ == 5000);
}

TEST_CASE("Correct classification", "[classifier]") {
  Image to_test = ParseFiles(images, labels)[0];
  model.trainModel();
  ifstream model_stream("model.txt");
  string next_line;
  getline(model_stream, next_line);
  vector<double> class_proportions = SplitProportions(next_line, kNumClasses);
  vector<vector<vector<double>>> pixel_proportions =
      MakeProportionGrids(model_stream, next_line);
  REQUIRE(ClassifyImage(to_test, class_proportions, pixel_proportions) == 9);
}

