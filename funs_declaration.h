#include <vector>
#include <string>

#define def_K 5
#define def_L 4

using namespace std;

vector <vector_info *> store_set (string);

vector <double> random_s (int);

vector <vector <vector <double>>> every_s (int, int, int);

vector <int> compute_a (vector_info *, vector <double>);

vector <vector <vector <int>>> a_for_each_x (vector_info *, vector <vector <vector <double>>>, int, int, int);

int compute_m (vector <vector <vector <vector <int>>>>);

int mymod (int, int);

int modpow (int, int, int);

int compute_h (vector <int>, int, int, int);

vector < vector <vector <int>>> h_for_each_x (vector <vector <vector <vector <int>>>>, int, int, int, int);

long long int compute_g (vector <int>);

vector < vector <long long int>> every_g (vector <vector <vector <int>>>);

int hashing (long long int, long long int);

vector < vector <hash_node *>> match_g_and_x (vector <vector <long long int>> g);

vector <bucket **> make_L_hashtables (vector <vector <hash_node *>>, int, int);

bool check_args(int argc, const char * argv[], string * input_file, string * query_file, int * k, int * m, string * output_file);

vector <vector_info *> store_queries(string query_file, double * R);

vector <vector <hash_node *>> find_possible_nns (vector <bucket **>, int, vector <vector <long long int>>);

vector <LSH_neig *> find_nn (vector <vector <hash_node *>> posibol, vector <vector <long long int>> q_g, vector<vector_info *> dataset, vector<vector_info *> queries, clock_t time);

vector <map<int, LSH_neig *>> find_R_NNs(vector <vector <hash_node *>> posibol, vector <vector <long long int>> q_g, vector<vector_info *> dataset, vector<vector_info *> queries, double R);

int compute_dist (vector_info *, vector_info *);

vector <trueNN_node *> find_trueNN (vector <vector_info *>, vector <vector_info *>);

bool write_output(string output_file, vector<LSH_neig *> NN, vector<trueNN_node *> tr, vector <map <int, LSH_neig *>> R_NNs, vector<vector_info *> queries, vector<vector_info *> dataset);
