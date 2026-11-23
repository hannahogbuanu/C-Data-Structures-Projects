#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include "csvstream.hpp"
using namespace std;

set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

class Classifier {
    public:
        Classifier() :
            num_posts(0) {}
        
        void train(const string &label, const string &content) {
            num_posts++;
            label_counts[label]++;

            map<string, int> &words_for_label = label_word_counts[label];
            set<string> words = unique_words(content);
            for (const string &word : words) {
                word_counts[word]++;        
                words_for_label[word]++;   
            }
        }
        int get_num_posts() const {
            return num_posts;
        }
        
        int getVocabSize() const {
            return word_counts.size();
        }

        string predict(const string &content, double &bestscore) const {
            string bestlabel;
            bool first = true;
            for (const auto &pair : label_counts) {
                double s = score(pair.first, content);
                if (first || s > bestscore){
                    bestlabel = pair.first;
                    bestscore = s;
                    first = false;
                }
            }
            return bestlabel;
        }

        void print_classes() const {
            cout << "classes:" << endl;
            for (const auto &pair : label_counts) {
                cout << "  " << pair.first << ", " << pair.second
                << " examples, log-prior = " << logprior(pair.first) << endl;
            }
        }

        void print_parameters() const {
            cout << "classifier parameters:" << endl;
            for (const auto &label_pair : label_word_counts) {
                for (const auto &wordpair : label_pair.second) {
                    cout << "  " << label_pair.first << ":" << wordpair.first
                    << ", count = " << wordpair.second << ", log-likelihood = "
                    << log_likelihood(label_pair.first, wordpair.first) << endl;
                }
            }
        }
    
    private:
        int num_posts;
        map<string, int> label_counts;
        map<string, int> word_counts;
        map<string, map<string, int>> label_word_counts;

        double logprior(const string &label) const {
            return log(double(label_counts.at(label))/ num_posts);

        }

        double log_likelihood(const string &label, const string &word) const {
            const map<string, int> &words4label = label_word_counts.at(label);
            auto inlabel = words4label.find(word);
            auto inall = word_counts.find(word);

            if (inlabel != words4label.end()) {
                return log(double(inlabel->second)/label_counts.at(label));

            }
            else if (inall != word_counts.end()) {
                return log(double(inall->second)/num_posts);
            }
            else{
                return log(1.0/num_posts);
            }
        }

        double score(const string &label, const string &content) const {
            double total = logprior(label);
            set<string> words = unique_words(content);
            for (const string &word : words) {
                total += log_likelihood(label, word);
            }
            return total;
        }
};


int main(int argc, char *argv[]) {
    cout.precision(3);
    if(argc != 2 && argc != 3) {
        cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
        return 1;
    }

    string train_filename = argv[1];
    try {
        csvstream train_in(train_filename);
    } 
    catch (const csvstream_exception &e) {
        cout << "Error opening file: " << train_filename << endl;
        return 1;
    }

    if (argc == 3) {
        string test_filename = argv[2];
        try {
            csvstream test_in(test_filename);
        } 
        catch (const csvstream_exception &e) {
            cout << "Error opening file: " << test_filename << endl;
            return 1;
        }
    }

    bool trainOnly = (argc == 2);

    Classifier classifier;
    csvstream train_in(train_filename);
    map<string, string> row;

    if (trainOnly) {
        cout << "training data:" << endl;
    }

    while (train_in >> row) {
        string label = row["tag"];
        string content = row["content"];
        if (trainOnly) {
            cout << "  label = " << label << ", content = " << content << endl;

        }
        classifier.train(label, content);
    }
    cout << "trained on " << classifier.get_num_posts() << " examples" << endl;
    if (trainOnly) {
        cout << "vocabulary size = " << classifier.getVocabSize() << endl;

    }
    cout << endl;

    if(trainOnly) {
        classifier.print_classes();
        classifier.print_parameters();
        cout << endl;
    }

    if (argc == 3) {
        csvstream test_in(argv[2]);
        map<string, string> test_row;
        int correct = 0;
        int total = 0;

        cout << "test data:" << endl;
        while (test_in >> test_row) {
            string label = test_row["tag"];
            string content = test_row["content"];

            double score = 0;
            string predicted = classifier.predict(content, score);

            cout << "  correct = " << label << ", predicted = " << predicted
            << ", log-probability score = " << score << endl;
            cout << "  content = " << content << endl << endl;

            total++;
            if (predicted == label) {
            correct++;
            }
        }
        cout << "performance: " << correct << " / " << total
        << " posts predicted correctly" << endl;
    }
    return 0;

}
