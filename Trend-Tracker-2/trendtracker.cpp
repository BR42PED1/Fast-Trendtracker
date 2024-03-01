#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "trendtracker.h"
//Aaron Ratliff

		// Creates a Trendtracker containing hashtags 
		// found in the provided file.
		// The file is promised to have the following format: 
		// 
		// string1 
		// string2 
		// ...
		// stringN 
		//
		// where string1 < string2 < ... < stringN 
		// 
		// Must run in O(n) time.
Trendtracker :: Trendtracker(string filename) {
  string hashtag;
  ifstream inFile;
  inFile.open(filename);
  while(getline(inFile, hashtag)) {
    Entry e;
    e.hashtag = hashtag;
    e.pop = 0;
    E.push_back(e);
  }
  inFile.close();     
}

//////////////////////////////////////////////////////////////////////
		// Return the number of hashtags in the Trendtracker.
		//
		// Must run in O(1) time.

int Trendtracker :: size() {
  return E.size();
}

//////////////////////////////////////////////////////////////////////
		// Adds 1 to the total number times a hashtag has been tweeted.
		// If the hashtag does not exist in TrendTracker, does nothing.
		//
		// Must run in O(log(n)) time.

void Trendtracker :: tweeted(string ht) {
  E[search(ht)].pop++;

  bool dup = false;

  for ( int i = 0; i < S.size(); i++ ) {
    
    if (S[i] == search(ht)) {
      dup = true;
    }
    
  }

  if ( dup == false ) {
    S.push_back(search(ht));
  }

  for ( int t = 0; t < S.size(); t++ ) {
    int j = t;
    while ( j > 0 && E[S[j]].pop > E[S[j-1]].pop ) {
      int temp = S[j-1];
      S[j-1] = S[j];
      S[j] = temp;
      j--;
    }
  }

  if ( S.size() > 3 ) {
    S.pop_back();
  }
}

//////////////////////////////////////////////////////////////////////
		// Returns the number of times a hashtag has been tweeted.
		// If the hashtag does not exist in Trendtracker, returns -1.
		// 
		// Must run in O(log(n)) time.

int Trendtracker :: popularity(string name) {

  int index = search(name);

  if ( index != -1 ) {
    return E[index].pop;
  }

  return -1;
}

//////////////////////////////////////////////////////////////////////
		// Returns a most-tweeted hashtag.
		// If the Trendtracker has no hashtags, returns "".
		// 
		// Must run in O(1) time.

string Trendtracker :: top_trend() {
  if ( E.size() == 0 ) {
    return "";
  }

  else {
     return E[S[0]].hashtag; 
  }
}

//////////////////////////////////////////////////////////////////////
		// Fills the provided vector with the 3 most-tweeted hashtags, 
		// in order from most-tweeted to least-tweeted.
		// 
		// If there are fewer than 3 hashtags, then the vector is filled
		// with all hashtags (in most-tweeted to least-tweeted order).
		//
		// Must run in O(1) time.

void Trendtracker :: top_three_trends(vector<string> &T ) {

  T.clear();
  
  if ( E.size() == 1 ) {
    T.push_back(E[0].hashtag);
    return;
  }

  if ( S.size() == 0 ) {
    T.push_back(E[0].hashtag);
    T.push_back(E[1].hashtag);
    T.push_back(E[2].hashtag);
  }

  else if ( S.size() == 1 ) {
    T.push_back(E[S[0]].hashtag);
    T.push_back(E[1].hashtag);
    T.push_back(E[2].hashtag);
  }

  else if ( S.size() == 2 ) {
    T.push_back(E[S[0]].hashtag);
    T.push_back(E[S[1]].hashtag);
    T.push_back(E[2].hashtag);
  }

  else {
    T.push_back(E[S[0]].hashtag);
    T.push_back(E[S[1]].hashtag);
    T.push_back(E[S[2]].hashtag);
  }
}


		// Optional helper method.
		// Returns the index of E containing an Entry with hashtag ht.
		// If no such hashtag is found, returns -1. 
		// 
		// Should run in O(log(n)).

int Trendtracker :: search(string ht) {
  int l = 0;
  int r = E.size()-1;
  
  while ( l <= r ) {
    int mid = (l + r) / 2;
    if (E[mid].hashtag == ht) {
      return mid;
    }

    else if (E[mid].hashtag < ht) {
      l = mid + 1;
    }

    else {
      r = mid - 1;
    }
  }

  return -1;
  
}

