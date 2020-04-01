// Copyright 2020 Aaron Alberg. All rights reserved.

#include <bayes/classifier.h>

namespace bayes {

double ClassifyAllImages(string arg1, string arg2) {
  ifstream model("model.txt");
  string next_line;
  getline(model, next_line);
  vector<double> class_proportions = SplitProportions(next_line, kNumClasses);
  vector<vector<vector<double>>> pixel_proportions =
      MakeProportionGrids(model, next_line);
  vector<Image> test_images = ParseFiles(arg1, arg2);

  int image_count = 0, correct_count = 0;
  for (Image &image : test_images) {
    image_count++;
    int return_class =
        ClassifyImage(image, class_proportions, pixel_proportions);
    if (return_class == image.getNumberClass()) {
      correct_count++;
    }
  }

  model.close();
  double percent_correct = ((double) correct_count / (double) image_count) * 100;
  cout << "RESULTS" << endl;
  cout << "Image count: " << image_count << endl;
  cout << percent_correct << "% correct" << endl;
  return percent_correct;
}

int ClassifyImage(Image &image, vector<double> &class_proportions,
    vector<vector<vector<double>>> &pixel_proportions) {

  vector<double> comparable_probs(kNumClasses, 1);
  for (int num = 0; num < kNumClasses; num++) {
    comparable_probs[num] += class_proportions[num];
    for (int i = 0; i < kImageSize; i++) {
      for (int j = 0; j < kImageSize; j++) {
        if (image.getPixels()[i][j] == 1) {
          comparable_probs[num] += log(pixel_proportions[num][i][j]);
        } else {
          comparable_probs[num] += log(1 - pixel_proportions[num][i][j]);
        }
      }
    }
  }

  return FindHighestIndex(comparable_probs);
}

int FindHighestIndex(vector<double> &comparable_list) {
  int highest_index = 0;
  double highest_value = std::numeric_limits<double>::lowest();
  for (int i = 0; i < comparable_list.size(); i++) {
    if (comparable_list[i] > highest_value) {
      highest_index = i;
      highest_value = comparable_list[i];
    }
  }

  return highest_index;
}

vector<Image> ParseFiles(const string& images_path, const string& labels_path) {
  ifstream testing_images_(images_path);
  ifstream testing_labels_(labels_path);

  string next_line_images, next_line_labels;
  int label_value, line_count = 1;
  vector<Image> images;
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

vector<double> SplitProportions(string& line, int size) {

  //https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
  istringstream stream(line);
  vector<double> proportions_row;
  int count = 0;
  while (stream && count < size) {
    count++;
    string word;
    stream >> word;
    proportions_row.push_back(stod(word));
  }

  return proportions_row;
}

vector<vector<vector<double>>> MakeProportionGrids(ifstream& stream, string&line) {
  vector<vector<vector<double>>> pixel_proportions;
  for (int i = 0; i < kNumClasses; i++) {
    vector<vector<double>> grid;
    for (int j = 0; j < kImageSize; j++) {
      getline(stream, line);
      vector<double> row = SplitProportions(line, kImageSize);
      grid.push_back(row);
    }

    pixel_proportions.push_back(grid);
  }

  return pixel_proportions;
}

}  // namespace bayes

