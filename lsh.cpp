#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <ctime>
#include "classes.h"
#include "funs_declaration.h"

using namespace std;

int main(int argc, char const *argv[])
{
  string input_file, query_file, output_file;
  int K = -1, L = -1;
  double R = -1.0;

  clock_t time;

  if(check_args(argc, argv, &input_file, &query_file, &K, &L, &output_file) == false)
    return -1;


  int i,j,k, m, M, TABLESIZE=1024;
  vector <vector_info *> dataset, queries;

  vector <vector <vector <double>>> s;
  vector <vector <vector <vector <int>>>> a, q_a;
  vector <vector <vector <int>>> h, q_h;
  vector <vector <long long int>> g, q_g;
  vector <vector <hash_node *>> g_x;                                   
  vector <bucket **> hashtables;

  dataset = store_set (input_file);
  s = every_s (L, K, dataset[0]->get_dim()); // calculate the L * K random s vectors

  // for (i=0; i<3; i++)
  // {
  //   for (j=0; j<2; j++)
  //   {
  //     for (k=0; k<4; k++)
  //       cout << s[i].at (j).at (k) << " ";
  //     cout << endl;
  //   }
  //   cout << endl;
  // }

  for (i = 0; i < dataset.size(); i++)
    a.push_back(a_for_each_x (dataset[i], s, L ,K, dataset[0]->get_dim()));
  //
  // for (int y=0; y<dataset.size (); y++)
  // {
  //   for (i=0; i<L; i++)
  //   {
  //     for (j=0; j<K; j++)
  //     {
  //       cout << "--- K = " << j << " ---" << endl;
  //       for (k=0; k<dataset[0]->get_dim (); k++)
  //         cout << a[y].at (i).at (j).at (k) << " ";
  //       cout << endl;
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  // }
  //
  // for (i=0; i<L; i++)
  // {
  //   for (j=0; j<K; j++)
  //   {
  //     for (k=0; k<s[i].at (j).size (); k++)
  //       cout << s[i].at (j).at (k) << " ";
  //     cout << endl;
  //   }
  //   cout << endl;
  // }

  m = compute_m(a);

  m+=2;

  // w=find_good_w (dataset);
  // cout << "w=" << w << endl;

  // a=compute_a (dataset[0], s);

  // for (int i=0; i<a.size (); i++)
  //   cout << a[i] << endl;
  // for (int i=0; i<dataset.size ()-3; i++)
  // {
  //   cout << dataset[i]->get_id () << endl;
  // }

  // for (i=0; i<dataset.size (); i++)
  // {
  //   for (j=0; j<dataset[i]->get_dim (); j++)
  //     cout << dataset[i]->get_specific_coord (j) << " ";
  //   cout << endl;
  // }

  M=pow (2, 32/K);
  h=h_for_each_x (a, L, K, m, M);
  g=every_g (h);

  // cout << a.size () << endl;

  // for (i=0; i<h.size (); i++)
  // {
  //   for (j=0; j<h[0].size (); j++)
  //   {
  //     for (k=0; k<h[0].at (0).size (); k++)
  //       cout << h[i].at (j).at (k) << " ";
  //     cout << endl;
  //   }
  // }

  // for (i=0; i<g.size (); i++)
  // {
  //   for (j=0; j<g[0].size (); j++)
  //     cout << g[i].at (j) << " ";
  //   cout << endl;
  // }

  g_x = match_g_and_x (g);
  // cout << g_x.size () << " ++ " << g_x[0].size () << endl;
  hashtables = make_L_hashtables (g_x, L, TABLESIZE);

  // bucket** test=hashtables[0];
  // for (i=0; i<hashtables.size (); i++)
  // {
  //   cout << test[i]->get_all_nodes ().size () << endl;
  // }

  // cout << hashtables.size () << " -- " << TABLESIZE << " -- " << test[1]->get_all_nodes ().size () << endl;
  a.clear ();
  h.clear ();
  g.clear ();
  g_x.clear ();


  // bucket ** help;
  // for (i=0; i<hashtables.size (); i++)
  // {
  //   help=hashtables[i];
  //   for (j=0; j<TABLESIZE; j++)
  //   {
  //     if (help!=NULL)
  //     {
  //       for (k=0; k<help[j]->get_all_nodes ().size (); k++)
  //         cout << help[j]->get_all_nodes ().at (k)->get_id () << " -- " << help[j]->get_specific_hash_node (k)->get_g () << "  ";
  //       cout << endl;
  //     }
  //     cout << endl;
  //   }
  // }


  queries = store_queries(query_file, &R);

  for (i = 0; i < queries.size(); i++)
    q_a.push_back (a_for_each_x(queries[i], s, L ,K, queries[0]->get_dim ()));

  q_h=h_for_each_x(q_a, L, K, m, M);
  q_g=every_g(q_h);

  // time = clock();

  vector <vector <hash_node *>> posibol = find_possible_nns(hashtables, TABLESIZE, q_g);

  // time = clock() - time;
  // cout<<time<<endl;

  vector <LSH_neig *> NN = find_nn (posibol, q_g, dataset, queries, 0);

  vector <trueNN_node *> tr = find_trueNN (dataset, queries);

  vector <map<int, LSH_neig *>> R_NN = find_R_NNs(posibol, q_g, dataset, queries, R);

  // cout<<tr.size()<< " "<< NN.size()<<endl;

  if(write_output(output_file, NN, tr, R_NN, queries, dataset) != true)
    return -1;

  dataset.clear ();

  queries.clear();

  s.clear ();

  hashtables.clear ();

  return 0;
}
