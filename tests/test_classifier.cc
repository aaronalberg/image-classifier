// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <bayes/classifier.h>
#include <bayes/model.h>





TEST_CASE("Prepare Regular Row", "[model][prepare-row]") {
  vector<int> test_row = {0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1};
  string test_string = " #+#   ++ #+#   ++ #+#   ++#";
  REQUIRE(bayes::Model::prepareRow(test_string) == test_row);
}

TEST_CASE("Prepare empty row", "[model][prepare-row]") {
  vector<int> test_row(bayes::kImageSize, 0);
  string test_string = "                            ";
  REQUIRE(bayes::Model::prepareRow(test_string) == test_row);
}

TEST_CASE("Prepare complete row", "[model][prepare-row]") {
  vector<int> test_row(bayes::kImageSize, 1);
  string test_string = "#+##++#+##++#+##++#+##++++##";
  REQUIRE(bayes::Model::prepareRow(test_string) == test_row);
}

TEST_CASE("Model is written", "[model][write-model-file") {
  bayes::Model model;
  model.trainModel();
  ifstream stream("model.txt");
  REQUIRE(stream.good());
}

TEST_CASE("Split class proportions", "[classify][split]") {
  vector<double> test_vector = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  string test_string = "0.0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0";
  REQUIRE(classify::)
}
