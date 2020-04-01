// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/model.h>
#include <cstdlib>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;
using namespace bayes;


int main(int argc, char** argv) {
  ifstream model_stream("model.txt");
  if (!model_stream.good()) {
    Model model;
    model.trainModel();
    model_stream.close();
  }

  ClassifyAllImages(argv[1], argv[2]);
  return EXIT_SUCCESS;
}
