#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>      // std::pair, std::make_pair
#include <bits/stdc++.h>
using namespace std;


class Baboon_Reader {
public:
  map<string, vector<tuple<double,double,double>>> readFile(){
    /*
    generates a map consisting of baboon names as keys.
    Each key has a vector listing tuples containing longitude
    and latitude for each timestamp
    */
      cout<<"Creating Map";
      string line;
      ifstream myfile ("Baboon_data.csv");
      vector<string> baboon_names;
      map<string, vector<tuple<double,double,double>>> baboon_personal_data;

      if (myfile.is_open()) //opens file
      {
        while ( getline (myfile,line) ) //assigns each line of the file to the string line.
        {

          stringstream s_stream(line);// don't quite understand this yet. The documentation was a little confusing, will read further.

          vector<string> result;

          while(s_stream.good())
          {
            /*
            goes through each line (while there are lines to go through) and seperates based on the delimeter (the comma).
            Adding them to the result vector.
            */
            string substr;
            getline(s_stream, substr, ',');
            result.push_back(substr);
          }
          if (find(baboon_names.begin(), baboon_names.end(),result[8]) != baboon_names.end()){
            ;
          }else{
            /*checks to see if baboon name is already present in the baboon list.
              If not it creates an empty vector that will be added to and adds to the baboon list.
              */
            baboon_names.push_back(result[8]);
            baboon_personal_data[result[8]] = {};
          }
          tuple<double,double,double> relevant_data;

          double timestamp = atof(result[2].c_str()); //loses some data ask dr.chester for suggestion here
          double longitude = atof(result[3].c_str());
          double latitude = atof(result[4].c_str());
          relevant_data= make_tuple(timestamp,longitude,latitude);// timestamp long lat
          string baboon_name = result[8];
          baboon_personal_data[baboon_name].push_back(relevant_data);
        }
        myfile.close();
        return baboon_personal_data;
      }
      else cout << "Unable to open file";
      }


  vector<string> baboonNamesList(){
    /*
    was having trouble returning two values from the readFile function (new to c++).
    I copy pasted a chunk of the  readFile function so that I could easily access the list of names
    in the jaccard_index_for_each function.
    */
    string line;
    ifstream myfile ("Baboon_data.csv");
    vector<string> baboon_names;

    if (myfile.is_open()) //opens file
    {
      while ( getline (myfile,line) ) //assigns each line of the file to the string line.
      {
        stringstream s_stream(line);// don't quite understand this yet. The documentation was a little confusing, will read further.
        vector<string> result;
        while(s_stream.good()) //goes through each line (while there are lines to go through) and seperates based on the delimeter (the comma)
        {
          string substr;
          getline(s_stream, substr, ',');
          result.push_back(substr);
        }
        if (find(baboon_names.begin(), baboon_names.end(),result[8]) != baboon_names.end()){
          ;
        }else{
          baboon_names.push_back(result[8]); //checks to see if baboon name is already present in the baboon list. If not it creates an empty vector that will be added to and adds to the baboon list.
        }
      return baboon_names;
    }
    }
  }

  map<string, double> jaccard_index_for_each(map<string, vector<tuple<double,double,double>>> dicty, string baboon_name ){
    /*
    0.0001° = 11.1 m
    0.00001° = 1.11 m
    This function aims to generate the jaccard index between the baboon of interest and every other baboon listed.
    This is most likely not the most efficient way to measure fly by but it's good practice nonetheless.

    The timestamps are out of sync but I should see whether the number of timestamps are consistant.
    In this instantiation I pretend that the timestamps are in sync and that the number of timestamps are consistant.

    I think I may have to search for a new data set as the timestamps are not very consistant in their sampling.
    I think the ideal data set would have at least one of the two characteristics:
    1. large sampling frequency (second or minute based rather then by hour)
    2. consistant sampling (sampling at the same times for each baboon)
    */

    vector<string> baboon_names=baboonNamesList();
    map<string, double> dictToReturn;
    double longitude_tolerance =0.00001;
    double latitude_tolerance =0.00001;
    for (int i = 0; i < dicty[baboon_name].size(); i++) {
      for(int j = 0; j< baboon_names.size();j++){
        double totalIntersections = 0;
        for(int k =0; k< dicty[baboon_names[j]].size();k++){
          if (get<1>(dicty[baboon_name][i])-longitude_tolerance <= get<1>(dicty[baboon_names[j]][k]) &&get<1>(dicty[baboon_names[j]][k])<=get<1>(dicty[baboon_name][i])+longitude_tolerance){
            if (get<2>(dicty[baboon_name][i])-latitude_tolerance <= get<2>(dicty[baboon_names[j]][k]) &&get<2>(dicty[baboon_names[j]][k])<=get<2>(dicty[baboon_name][i])+latitude_tolerance){
              totalIntersections+=1;
            }
          }
        }
        dictToReturn[baboon_names[j]] = totalIntersections/dicty[baboon_names[j]].size(); // here I assume (probably incorrectly) that the size of each set of timestamps are the same.
      }

    }
  return dictToReturn;
  }

  };

  main () {
    //declaring variables
    Baboon_Reader baboon;
    map<string, vector<tuple<double,double,double>>> dicty = baboon.readFile();
    map<string, double> jaccard_index = baboon.jaccard_index_for_each(dicty, "F9"); //The goal here is to compare the from F9 to each other point.




    return 0;
  }
