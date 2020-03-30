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



// TODO(you): Change the code below for your project use case.

DEFINE_string(name, "Aaron", "Your first name");
DEFINE_bool(happy, false, "Whether the greeting is a happy greeting");


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

    ifstream test_stream(argv[1]);
    if (test_stream.fail()) {
        cout << "No files to test" << endl;
    }

    ifstream model_stream("model.txt");
    if (!model_stream.good()) {
      bayes::Model model;
      model.trainModel();

    }



  return EXIT_SUCCESS;
}
