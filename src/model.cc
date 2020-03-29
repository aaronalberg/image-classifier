// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/model.h>

namespace bayes {

void Model::trainModel() {
  vector<bayes::Image> images = readTrainingFiles();
  std::cout << images[0].trainingClass << endl;
  for (int i = 0; i < 28; i++) {
    std::cout << images[0].pixels[6][i] << endl;
  }
  for (int i = 0; i < 28; i++) {
    std::cout << images[0].pixels[5][i] << endl;
  }
  for (int i = 0; i < 28; i++) {
    std::cout << images[0].pixels[7][i] << endl;
  }

}



vector<bayes::Image> Model::readTrainingFiles() {
  ifstream training_images_;
  ifstream training_labels_;
  training_images_.open("data/digitdata/trainingimages");
  training_labels_.open("data/digitdata/traininglabels");

  string next_line_images;
  string next_line_labels;
  int label_value;
  int line_count = 0;
  vector<bayes::Image> images;
  grid.assign(kImageSize, vector<int>(kImageSize, 1));

  while (getline (training_images_, next_line_images)) {

    vector<int> row;
    for (int i = 0; i < bayes::kImageSize; i++) {
      if (next_line_images.at(i) == ' ') {
        //grid[line_count].push_back(0);
        //std::cout << "here   bbb" << endl;
        row.push_back(0);
      }

      if (next_line_images.at(i) == '+'
          || (next_line_images.at(i) == '#')) {
        //grid[line_count].push_back(1);
        //std::cout << "here   aaa" << endl;
        row.push_back(1);
        //std::cout << row[i] << endl;
      }
    }
    std::cout << row[0] << endl;
    grid.push_back(row);
    std::cout << grid[0][0] << endl;


    if (line_count % kImageSize == 0 && line_count != 0) {
      std::cout << grid[0][9] << endl;
      getline(training_labels_, next_line_labels);
      label_value = stoi(next_line_labels);
      bayes::Image current_image(grid, label_value);
      images.push_back(current_image);
    }

    line_count++;
    if (line_count > 1000) {
      break;
    }

  }

  training_images_.close();
  training_labels_.close();
  std::cout << "hey0" << endl;
  return images;
}

}  // namespace bayes

