// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
/*store timestamp location long lat and individual*/

main () {
  //declaring variables
  cout<<"hi";
  string line;
  ifstream myfile ("Baboon_data.csv");
  vector<string> baboon_names;
  map<string, vector<vector<string>>> baboon_personal_data;

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
        baboon_personal_data[result[8]] = {};

      }

      vector<string> relevant_data;
      relevant_data= {"timestamp: "+ result[2],"longitude: "+result[3],"latitude:"+result[4]};
      string baboon_name = result[8];
      baboon_personal_data[baboon_name].push_back(relevant_data);// having trouble printing the baboon_personal_data to the console, perhaps it's another quirk of c++?





    }
    myfile.close();

    /*
    If you are wanting to print it out.
    for (pair<string, vector<string>> element : baboon_personal_data) {
    string key = element.first;
    vector<string> value = element.second;
    cout << key <<"::"<< endl;
    for (int i=0;i<value.size();i++){
      cout<<value[i]<<endl;
    }

}*/

  }


  else cout << "Unable to open file";

  return 0;
}
