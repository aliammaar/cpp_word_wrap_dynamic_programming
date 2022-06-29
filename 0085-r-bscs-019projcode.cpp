
//0085-r-bscs-019
//sec A
//submitted to :***********Sir Saeed Ul Rehman Turk**********


// *******************A Dynamic programming solution for Word Wrap Problem*******************************

#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;

#define INF INT_MAX

int printSolution (int p[], int n);

// l[] represents lengths of different words in input sequence. For example,
// l[] = {3, 2, 2, 5} is for a sentence like "aaa bb cc ddddd".  n is size of
// l[] and M is line width (maximum no. of characters that can fit in a line)

void solveWordWrap (int l[], int n, int M)

{
  // For simplicity, 1 extra space is used in all below arrays
  // extras[i][j] will have number of extra spaces if words from i
  // to j are put in a single line

  int extras[n+1][n+1];
  // extras[i][j] will have cost of a line that is lc  which has words from i to j

  int lc[n+1][n+1];

  // c[i] will have total cost of optimal arrangement of words from 1 to i

  int c[n+1];
  // p[] is used to print the solution.
  int p[n+1];
  int i, j;

  // calculate extra spaces in a single line.
  for (i = 1; i <= n; i++)
    {
      extras[i][i] = M - l[i-1];    // The value extra[i][j]
     // indicates extra spaces if words from word number i to j are
     // placed in a single line
      for (j = i+1; j <= n; j++)
        extras[i][j] = extras[i][j-1] - l[j-1] - 1;
    }

  // Calculate line cost corresponding to the above calculated extra spaces.
  for (i = 1; i <= n; i++)
  {
    for (j = i; j <= n; j++)
    {
      if (extras[i][j] < 0)
        lc[i][j] = INF; // The value lc[i][j] indicates cost of putting words from
        // word number i to j in a single line
      else if (j == n && extras[i][j] >= 0)
          lc[i][j] = 0;
      else
        lc[i][j] = extras[i][j]*extras[i][j];
    }
  }

  //  this for loop will Calculate minimum cost and find minimum cost arrangement.
  c[0] = 0;

  for (j = 1; j <= n; j++)
  {
    c[j] = INF;      //  The value c[j] indicates optimized cost to arrange words
    for (i = 1; i <= j; i++)  // from word number 1 to j
    {
    // this if condition is saying if optimized cost of ith index -1 means one index back of ith index
    // is not equal to infinity and line cost is not equal to infinity and cost of i-1 +line cost of i and j
    // is less than optimezed cost then optimezed cost will be equal to their sum
    if (c[i-1] != INF && lc[i][j] != INF && (c[i-1] + lc[i][j] < c[j]))
      {
        c[j] = c[i-1] + lc[i][j];
        p[j] = i;  //for printig of jth index equal to i
      }
    }
  }
  printSolution(p, n);

}

// for printing the answer where p[] is printing array

int printSolution (int p[], int n)
{
  int k;
  fstream file;
  string word;
  int word_count = 1;
  string line;
  std::ofstream outfile;
  time_t t = std::time(0);

  cout << "timetime" << endl;
  cout << t << endl;
  cout << "timetime" << endl;

  if (p[n] == 1) {
    // printf ("From word no. %d to %d \n", p[n], n);
    file.open("word-wrap-input.txt");
    while(file >> word) {
      if(word_count >= p[n] && word_count <= n){
        line.append(" ");
        line.append(word);
      }
      if (word_count >= n){
        break;
      }
      word_count++;
    }

    outfile.open("word-wrap-output.txt", std::ios_base::app);
    // ofstream WriteToFile("word-wrap-output.txt");
    outfile << line;
    cout << line << endl;
    k = 1;
  }
  else {
    k = printSolution (p, p[n]-1) + 1;
    // printf ("Line number %d: From word no. %d to %d \n", k, p[n], n);
    file.open("word-wrap-input.txt");
    while(file >> word) {
      if(word_count >= p[n] && word_count <= n){
        line.append(" ");
        line.append(word);
      }
      if (word_count >= n){
        break;
      }
      word_count++;
    }
    if (line.length() > 0) {
    outfile.open("word-wrap-output.txt", std::ios_base::app);
      outfile << line;
      cout << line << endl;
    }
  }

  return k;
}


int main() {
  int* arr = NULL;
  arr = new int[1000];
  int arr_index = 0;
  fstream file;
  string word;

  std::cout << "**************************************************************" << std::endl;
  std::cout << "     Word Wrap Problem Solution with Dynamic Programming      " << std::endl;
  std::cout << "**************************************************************" << std::endl;

  ifstream myFile("word-wrap-input.txt");
  if(myFile.fail()) {
    std::cout<<"Please ensure input file exists with name word-wrap-input.txt"<<std::endl;
  }
  else {
    std::cout<<"Proccessing word-wrap-input.txt"<<std::endl;
  }

  file.open("word-wrap-input.txt");
  while(file >> word) {
    arr[arr_index] = word.length();
    arr_index++;
  }

  int n = (arr_index)*4;
  int M = 80;
  solveWordWrap(arr, n, M);
  return 0;
}
