#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int countDigits(long long n) {
    int k = 0;
    while (n) {
        k++;
        n /= 10;
    }
    return k;
}
struct node {
    long long phNo;
    string objName;
    string objDescription;
    string location;
    string category;
    set<string> tokenDescription;
};

// Tokenization and stop word removal
set<string> extractKeywords(const string& text, const set<string>& stopWords) {
    string processed;
    // Convert to lowercase and remove punctuation
    for (char ch : text) {
        if (ispunct(static_cast<unsigned char>(ch)))
            continue;
        processed += tolower(static_cast<unsigned char>(ch));
    }

    stringstream ss(processed);
    string word;
    set<string> keywordSet;
    while (ss >> word) {
        if (stopWords.count(word) == 0) {
            keywordSet.insert(word);
        }
    }
    return keywordSet;
}

// Jaccard Similarity Calculation
double calculateJaccard(const set<string>& set1, const set<string>& set2) {
    if (set1.empty() && set2.empty()) {
        return 1.0;
    }
    if (set1.empty() || set2.empty()) {
        return 0.0;
    }
    int intersection_count = 0;
    const auto& smaller_set = (set1.size() < set2.size()) ? set1 : set2;
    const auto& larger_set = (set1.size() < set2.size()) ? set2 : set1;
    for (const auto& element : smaller_set) {
        if (larger_set.count(element)) {
            intersection_count++;
        }
    }

    int union_count = set1.size() + set2.size() - intersection_count;

    if (union_count == 0) {
        return 0.0;
    }
    return static_cast<double>(intersection_count) /
           static_cast<double>(union_count);
}
// Final Score Calculation
double calculateScore(node lost, node found) {
    double jaccardWeight = 0.6;
    double categoryWeight = 0.25;
    double locationWeight = 0.15;
    double jaccardScore =
        calculateJaccard(lost.tokenDescription, found.tokenDescription);
    double categoryScore = 0.0;
    if (lost.category == found.category) {
        categoryScore = 1.0;
    } else if (lost.category == "Other" || found.category == "Other") {
        categoryScore = 0.2;
    }
    double locationScore = 0.0;
    if (lost.location == found.location) {
        locationScore = 1.0;
    } else if (lost.location == "Other" || found.location == "Other") {
        locationScore = 0.2; // Partial credit
    }
    double finalScore = (jaccardScore * jaccardWeight) +
                        (categoryScore * categoryWeight) +
                        (locationScore * locationWeight);
    return finalScore;
}
// Merge Sort Implementation
void merge(vector<pair<double, int>>& arr, int left, int mid, int right) {
    vector<pair<double, int>> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i].first >= arr[j].first)
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    // Copy remaining elements
    while (i <= mid)
        temp.push_back(arr[i++]);
    while (j <= right)
        temp.push_back(arr[j++]);

    // Copy back to original array
    for (int k = 0; k < temp.size(); k++)
        arr[left + k] = temp[k];
}

void mergeSort(vector<pair<double, int>>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
// Finding Top K Matches for a Lost Item
void find(const vector<vector<double>>& score, int lost_idx, int k,
          const vector<node>& found) {
    if (found.empty())
        return;
    int m = found.size();
    vector<pair<double, int>> ran;
    for (int i = 0; i < m; i++) {
        ran.push_back({score[lost_idx][i], i});
    }
    mergeSort(ran, 0, m-1);
    int i = 0;
    while (k > 0 && i < m) {
        if (ran[i].first == 0)
            break;
        cout << "\n--- Top Match " << (i + 1) << " ---" << endl;
        cout << "Score: " << ran[i].first << endl;
        cout << "Object Name: " << found[ran[i].second].objName << endl;
        cout << "Description: " << found[ran[i].second].objDescription << endl;
        k--;
        i++;
    }
}

int main() {
    set<string> stopWords(
        {"a", "an", "the", "in", "on", "is", "of", "for", "with"});
    vector<node> lost;
    vector<string> locations = {"Library",      "CCD",       "Gym",
                                "Orion",        "MIG",       "LOGOS",
                                "COKE Station", "2K Market", "Other"};
    vector<string> category = {"Electronics",    "Keys/Wallet/ID",
                               "Bags/Backpacks", "Clothing/Accessories",
                               "Books/Notes",    "Other"};
    vector<node> found;
    int t = 1;
    cout << "\n--- Lost Items Complaint  ---" << endl;
    // Open CSV file for lost items (append mode)
    ofstream lostFile("lost_items.csv", ios::app);
    if (!lostFile) {
        cerr << "Failed to open lost_items.csv for writing." << endl;
    }

    while (t) {
        node lost1;
        cout << "Enter phone number: " << endl;
        long long p;
        cin >> p;
        while (countDigits(p) != 10) {
            cout << "Enter Valid Number" << endl;
            cin >> p;
        }
        lost1.phNo = p;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter object name: " << endl;
        getline(cin, lost1.objName);
        cout << "Enter object type from given Options and choose the number "
                "beside it"
             << endl;

        for (int i = 0; i < category.size(); i++) {
            cout << i + 1 << "  " << category[i] << endl;
        }
        int k;
        cin >> k;
        while (k < 1 || k > category.size()) {
            cout << "Enter Valid Number" << endl;
            cin >> k;
        }
        lost1.category = category[k - 1];

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter object description: " << endl;
        getline(cin, lost1.objDescription);
        lost1.tokenDescription =
            extractKeywords(lost1.objDescription, stopWords);
        cout << "Enter location from give options and choose the number beside "
                "it "
             << endl;
        for (int i = 0; i < locations.size(); i++) {
            cout << i + 1 << "  " << locations[i] << endl;
        }
        int l;
        cin >> l;
        while (l < 1 || l > locations.size()) {
            cout << "Enter Valid Number" << endl;
            cin >> l;
        }
        lost1.location = locations[l - 1];
        lost.push_back(lost1);

        if (lostFile) {
            lostFile << lost1.phNo << "," << '"' << lost1.objName << '"' << ","
                     << '"' << lost1.objDescription << '"' << "," << '"'
                     << lost1.location << '"' << endl;
        }

        cout << "Add another lost item? (1 for yes, 0 for no): " << endl;
        cin >> t;
    }
    if (lostFile)
        lostFile.close();

    cout << "\n--- Found Items Complaint  ---" << endl;
    // Open CSV file for found items (append mode)
    ofstream foundFile("found_items.csv", ios::app);
    if (!foundFile) {
        cerr << "Failed to open found_items.csv for writing." << endl;
    }
    int r = 1;
    while (r) {
        node found1;
        cout << "Enter phone number: " << endl;
        long long p;
        cin >> p;
        while (countDigits(p) != 10) {
            cout << "Enter Valid Number" << endl;
            cin >> p;
        }
        found1.phNo = p;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter object name: " << endl;
        getline(cin, found1.objName);
        cout << "Enter object type from given Options and choose the number "
                "beside it"
             << endl;

        for (int i = 0; i < category.size(); i++) {
            cout << i + 1 << "  " << category[i] << endl;
        }
        int k;
        cin >> k;
        while (k < 1 || k > category.size()) {
            cout << "Enter Valid Number" << endl;
            cin >> k;
        }
        found1.category = category[k - 1];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter object description: " << endl;
        getline(cin, found1.objDescription);
        found1.tokenDescription =
            extractKeywords(found1.objDescription, stopWords);
        cout << "Enter location from give options and choose the number beside "
                "it "
             << endl;
        for (int i = 0; i < locations.size(); i++) {
            cout << i + 1 << "  " << locations[i] << endl;
        }
        int l;
        cin >> l;
        while (l < 1 || l > locations.size()) {
            cout << "Enter Valid Number" << endl;
            cin >> l;
        }
        found1.location = locations[l - 1];
        found.push_back(found1);
        // Write to CSV
        if (foundFile) {
            foundFile << found1.phNo << "," << '"' << found1.objName << '"'
                      << "," << '"' << found1.objDescription << '"' << ","
                      << '"' << found1.location << '"' << endl;
        }
        cout << "Add another found item? (1 for yes, 0 for no): " << endl;
        cin >> r;
    }
    if (foundFile)
        foundFile.close();

    int n = lost.size();
    int m = found.size();

    if (n == 0 || m == 0) {
        cout << "Need at least one lost and one found item to compare." << endl;
        return 0;
    }

    vector<vector<double>> score(n, vector<double>(m));

    cout << "\n--- Calculated Scores ---" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            score[i][j] = calculateScore(lost[i], found[j]);
            cout << score[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n--- Enter Lost Item Index(0 based) and Number of Matches ---" << endl;
    int i, k;
    cin >> i >> k;
    while (i < 0 || i >= n || k < 1) {
        cout << "Enter Valid Numbers" << endl;
        cin >> i >> k;
    }
    find(score, i, k,found); // to find k certain max scores with found node for a particular
    return 0;
}
