#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <ctime>
#include "classes.h"
#include "funs_declaration.h"

using namespace std;

#define W 4656.0

bool check_args(int argc, const char * argv[], string * input_file, string * query_file, int * k, int * L, string * output_file)
{

  if(argc == 11)
  {
    for(int i = 0; i < 10; i++)
    {
      if(strcmp(argv[i], "-d") == 0 )
      {
        if(input_file->length() == 0)
          input_file->append(argv[i+1]);
        else
          return false;
      }
      if(strcmp(argv[i], "-q") == 0)
      {
        if(query_file->length() == 0)
        {
          query_file->append(argv[i+1]);
        }
        else
          return false;
      }
      if(strcmp(argv[i], "-k") == 0 )
      {
        if(*k == -1)
          *k = atoi(argv[i+1]);
        else
          return false;
      }
      if(strcmp(argv[i], "-L") == 0 )
      {
        if(*L == -1)
          *L = atoi(argv[i+1]);
        else
          return false;
      }
      if(strcmp(argv[i], "-o") == 0)
      {
        if(output_file->length() == 0)
        {
          output_file->append(argv[i+1]);
        }
        else
          return false;
      }
    }
  }
  else if(argc == 7)
  {
    for(int i = 1; i < 7; i++)
    {
      if(strcmp(argv[i], "-d") == 0 )
      {
        if(input_file->length() == 0)
          *input_file = argv[i+1];
        else
          return false;
      }
      if(strcmp(argv[i], "-q") == 0)
      {
        if(query_file->length() == 0)
        {
          query_file->append(argv[i+1]);
        }
        else
          return false;
      }
      if(strcmp(argv[i], "-o") == 0)
      {
        if(output_file->length() == 0)
        {
          output_file->append(argv[i+1]);
        }
        else
          return false;
      }
    }

    *k = def_K;
    *L = def_L;
  }
  else if(argc == 1)
  {
    *k = def_K;
    *L = def_L;

    cout << "Please give the input_file" << endl;
    cin >> *input_file;
    cout << "Please give the query_file" << endl;
    cin >> *query_file;
    cout << "Please give the output_file" << endl;
    cin >> *output_file;
  }
  else
  {

    cout<< "ERROR" << endl;
    return false;
  }
  return true;
}

vector<vector_info *> store_set (string fname)
{
	string line, vec_line, id_str, coord_str;
	vector <vector_info *> dataset;
	int id=0, dim, pos_space1, pos_space2;
	vector_info *vec_ptr;

	fstream myfile (fname);
	if (myfile.is_open ())
	{
		while (getline (myfile, vec_line))
		{
      // cout << "AA" << endl;

			dim=0;
			vec_ptr=new vector_info ();

			pos_space1=0;
			pos_space2=vec_line.find (" ", pos_space1+1);

			if (pos_space2==std::string::npos)
				continue;

			id_str=vec_line.substr (pos_space1, pos_space2-pos_space1);
      // cout << "AA" << endl;

     		vec_ptr->set_id (id);
			vec_ptr->set_str_id (id_str);
      // cout << "AA" << endl;

			pos_space1=pos_space2+1;
			pos_space2=vec_line.find (" ", pos_space1);

			while (pos_space2!=std::string::npos)
			{
				if (pos_space2==std::string::npos)
					continue;

				coord_str=vec_line.substr (pos_space1, pos_space2-pos_space1);

				vec_ptr->set_coord (stoi (coord_str));

				dim++;

				pos_space1=pos_space2+1;
				pos_space2=vec_line.find (" ", pos_space1);
			}

			// coord_str=vec_line.substr (pos_space1);				// an den exei keno sto telos xreiazetai
			//
			// vec_ptr->set_coord (stoi (coord_str));
			//
			// dim++;

			vec_ptr->set_dim (dim);
			dataset.push_back (vec_ptr);

			id++;
		}

		myfile.close();
	}

	return dataset;
}

vector <vector_info *> store_queries(string query_file, double * R)
{
	string::size_type sz;
	string line, vec_line, id_str, coord_str;
	bool first_line = true;

	vector<vector_info *> dataset;

	int id=0, dim, pos_space1, pos_space2;

	vector_info *vec_ptr;

	fstream myfile(query_file);

	if(myfile.is_open())
	{

		while (getline(myfile, vec_line))
		{
			dim = 0;
			vec_ptr = new vector_info ();

			pos_space1 = 0;
			pos_space2 = vec_line.find (" ", pos_space1 + 1);

			if (pos_space2 == string::npos)
			{
				*R = stod(vec_line, &sz);
				continue;
			}

			id_str = vec_line.substr(pos_space1, pos_space2-pos_space1);

     		vec_ptr->set_id (id);
			vec_ptr->set_str_id (id_str);

			pos_space1 = pos_space2+1;
			pos_space2 = vec_line.find (" ", pos_space1);


			while (pos_space2 != string::npos)
			{
				if (pos_space2==string::npos)
					continue;

				coord_str=vec_line.substr (pos_space1, pos_space2-pos_space1);

				vec_ptr->set_coord (stoi (coord_str));

				dim++;

				pos_space1=pos_space2+1;
				pos_space2=vec_line.find (" ", pos_space1);
			}

			if(dim == 0 && first_line == true)
			{
				*R = stod(id_str, &sz);
			}
			else
			{
				vec_ptr->set_dim (dim);
				dataset.push_back (vec_ptr);

				id++;

			}
			first_line = false;

		}

		myfile.close();
	}

	return dataset;

}



vector <double> random_s (int dim)
{
	int i;
	vector <double> v;
	random_device rd;
	mt19937 gen (rd ());
	uniform_real_distribution <double> dis (0.0, W);

	for (i=0; i<dim; i++)
		v.push_back (dis (gen));

	return v;
}


vector <vector <vector <double>>> every_s (int L, int K, int dim)
{
	int i, j;
	vector <vector <double>> ks;
	vector <vector <vector <double>>> lks;

	for (i=0; i<L; i++)
	{
		for (j=0; j<K; j++)
			ks.push_back (random_s(dim));
		lks.push_back(ks);
		ks.clear();
	}

	return lks;
}

// double find_good_w (vector <vector_info *> v)
// {
// 	int i, j;
// 	for (i=0; )
// }


vector <int> compute_a (vector_info *x, vector <double> s)
{
	int i, val;
	double dif;

	vector <int> a;

	for (i=0; i<x->get_dim (); i++)
	{
		dif=x->get_specific_coord(i) - s[i];
		val = floor(dif/W);

		a.push_back (val);
	}
	return a;
}


vector <vector <vector <int>>> a_for_each_x (vector_info* x, vector <vector <vector <double>>> s, int L, int K, int dim)
{
	int i, j, z;
	vector <vector <int>> ka;
	vector <vector <vector <int>>> lka;

	for (i=0; i<L; i++)
	{
		for (j=0; j<K; j++)
			ka.push_back(compute_a(x, s[i].at(j)));

		lka.push_back(ka);
		ka.clear ();
	}

	return lka;
}


int compute_m (vector <vector <vector <vector <int>>>> a)
{
	int i, j, k, l, max=-1;

	for (i=0; i<a.size (); i++)
	{
		for (j=0; j<a[0].size (); j++)
		{
			for (k=0; k<a[0].at(0).size (); k++)
			{
				for (l=0; l<a[0].at(0).at (0).size (); l++)
				{
					if (a[i].at (j).at (k).at (l)>max)
						max=a[i].at (j).at (k).at (l);
				}
			}
		}
	}

	return max + 1;
}


int mymod (int a, int b)
{
  int m=a%b;

  if (m<0)
	{
		if (b<0)
			m=m-b;
		else
		m=m+b;
  }

  return m;
}


int modpow (int x, int y, int p)
{
    int res=1;      // Initialize result

    x=x%p;  // Update x if it is more than or
                // equal to p

    while (y>0)
    {
        // If y is odd, multiply x with result
        if (y&1)
            res=(res*x)%p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x)%p;
    }
    return res;
}


int compute_h (vector <int> a, int d, int m, int M)
{
	int i, h=0, modmult, power;
	long long int mult;

	// A^B mod C = ( (A mod C)^B ) mod C
	// (A * B ) mod C = (A mod C * B mod C) mod C

	for (i=0; i<a.size (); i++)
	{
		power=modpow (m, i, M);
		mult=power*(mymod (a[d-i-1], M));
		h+=mymod (mult, M);
	}

	h=mymod (h, M);

	return h;
}

vector <vector <vector <int>>> h_for_each_x (vector <vector <vector <vector <int>>>> a, int L, int K, int m, int M)
{
	int i, j, t, z;
	vector <int> kh;
	vector <vector <int>> lkh;
	vector <vector <vector <int>>> xlkh;

	for (i=0; i<a.size (); i++)
	{
		for (j=0; j<L; j++)
		{
			for (t=0; t<K; t++)
				kh.push_back (compute_h (a[i].at(j).at(t), a[0].at(0).at(0).size(), m, M));

			lkh.push_back (kh);
			kh.clear ();
		}

		xlkh.push_back(lkh);
		lkh.clear ();
	}

	return xlkh;
}


long long int compute_g (vector <int> h)
{
  long long int g;
  int i;
  string hi_str="";

  for (i=0; i<h.size (); i++)
    hi_str+=to_string (h[i]);

  g=stoll (hi_str);

  return g;
}


vector <vector <long long int>> every_g (vector <vector <vector <int>>> h)
{
	int i, j;
	vector <long long int> g;
	vector <vector <long long int>> xg;

	for (i=0; i<h.size (); i++)
	{
		for (j=0; j<h[0].size (); j++)
			g.push_back (compute_g (h[i].at(j)));

		xg.push_back (g);
		g.clear ();
	}

	return xg;
}


int hashing (long long int x, long long int size)
{
	int pos;
	long long int y, mult;

	y=x/size;
	mult=y*size;

	pos=x-mult;

	return pos;
}

vector <vector <hash_node *>> match_g_and_x (vector <vector <long long int>> g)
{
	int i, j;
	hash_node *hn;
	vector <hash_node *> gval;
	vector <vector <hash_node *>> l_gval;

	for (j = 0; j < g[0].size (); j++)
	{
		for (i = 0; i < g.size (); i++)
		{
			hn = new hash_node ();
			hn->set_id (i);
			hn->set_g (g[i].at(j));
			gval.push_back (hn);
		}

		l_gval.push_back (gval);
		gval.clear ();
	}


	return l_gval;
}

vector <bucket **> make_L_hashtables (vector <vector <hash_node *>> hn, int L, int size)
{
	int i, j, pos;
	long long int g;
	vector <bucket **> l_hashtables;
	bucket ** hashtable = new bucket *[size];

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < size; j++)
			hashtable[j] = NULL;

		for (j = 0; j < hn[0].size(); j++)
		{
			g = hn[i].at(j)->get_g();
			pos = hashing(g, size);

			if (hashtable[pos] == NULL)
				hashtable[pos] = new bucket;

			hashtable[pos]->add_node(hn[i].at(j));
		}

		l_hashtables.push_back(hashtable);
	}

	return l_hashtables;
}


vector <vector <hash_node *>> find_possible_nns (vector <bucket **> hashtables, int size, vector <vector <long long int>> q_g)
{
  int i, j, k, pos, found;
  bucket **buckets;
  vector <hash_node *> same_bucket;
  vector <vector <hash_node *>> nns;
  hash_node * empty = NULL;

  for (i=0; i < q_g.size (); i++)
  {
    found=0;
    for (j=0; j<hashtables.size (); j++)
    {
      buckets=hashtables[j];
      pos = hashing (q_g[i].at(j), size);
      if(buckets[pos] != NULL)
      {
        for (k=0; k < buckets[pos]->get_all_nodes().size (); k++)
        {
          if (q_g[i].at(j) == buckets[pos]->get_specific_hash_node(k)->get_g())
          {
              found=1;
              same_bucket.push_back(buckets[pos]->get_specific_hash_node(k));
          }

        }
      }
    }
    if (found == 0)
      	same_bucket.push_back(empty);

    nns.push_back (same_bucket);
    same_bucket.clear ();
  }

  // cout << "q_g=" << q_g.size () << endl;
  // for (i=0; i<q_g.size (); i++)
  // {
  //   // cout << i << endl;
  //   for (j=0; j<hashtables.size (); j++)
  //   {
  //     buckets=hashtables[j];
  //     pos=hashing (q_g[i].at (j), size);
  //     if (buckets[pos]!=NULL)
  //     {
  //       for (k=0; k<buckets[pos]->get_all_nodes ().size (); k++)
  //         same_bucket.push_back (buckets[pos]->get_specific_hash_node (k));
  //     }
  //   }
  //
  //   // for (j=0; j<same_bucket.size (); j++)
  //   //   nns.push_back (same_bucket[j]);
  //   nns.push_back (same_bucket);
  //   same_bucket.clear ();
  // }

  return nns;
}


vector <LSH_neig *> find_nn (vector <vector <hash_node *>> posibol, vector <vector <long long int>> q_g, vector<vector_info *> dataset, vector<vector_info *> queries, clock_t t)
{
  int i, j, k, nearest, dist = 0, near_pos;
  neighboor_frequency *nfr;
  vector <LSH_neig * > nns;
  clock_t time = 0.0;

  // vector <vector <hash_node *>> posibol = find_possible_nns (hashtables, size, q_g);

  for (i=0; i<posibol.size (); i++)
  {
    nearest = -1;
    time = clock();
    for (j=0; j<posibol[i].size (); j++)
    {

    	if(posibol[i].at(j) == NULL) // no neighbors
    	{
    		near_pos = -1;
    		nearest = -1;
    	}
    	else
    	{
    		int id = posibol[i].at(j)->get_id();
    		dist = compute_dist(dataset.at(id), queries.at(i));       //allaksa to -1

    		if(nearest == -1)
    		{
    			nearest = dist;
    			near_pos = id;
    		}
    		else
    		{
    			if(nearest > dist)
    			{
    				nearest = dist;
    				near_pos = id;
    			}
    		}
    	}
    }
    time = clock() - time + t;

    LSH_neig * neig = new LSH_neig;
    neig->set_id(near_pos);
    neig->set_dist(nearest);
    neig->set_time((float)time/CLOCKS_PER_SEC);
    nns.push_back(neig);

  }
  return nns;
}

vector <map<int, LSH_neig *>> find_R_NNs(vector <vector <hash_node *>> posibol, vector <vector <long long int>> q_g, vector<vector_info *> dataset, vector<vector_info *> queries, double R)
{
  int nearest, dist = 0, near_pos;
  float time = 0.0;
  map <int, LSH_neig * > nns;
  vector <map <int, LSH_neig * >> R_NNs;
  // clock_t tt;

  for (int i = 0; i < posibol.size(); i++)
  {
    nearest = -1;
    // tt = clock();
    for(int j = 0; j < posibol[i].size(); j++)
    {

    	if(posibol[i].at(j) == NULL) // no neighbors
    	{
    		near_pos = -1;
    		nearest = -1;
    		LSH_neig * neig = new LSH_neig;
    		neig->set_id(near_pos);
   			neig->set_dist(nearest);
    		neig->set_time(time);
    	}
    	else
    	{
    		int id = posibol[i].at(j)->get_id();
      		dist = compute_dist(dataset.at(id), queries.at(i));       // allaksa to id-1
      		nearest = dist;
      		near_pos = id;

      		if(dist < R)
      		{
      			LSH_neig * neig = new LSH_neig;
    			neig->set_id(near_pos);
   				neig->set_dist(nearest);
    			neig->set_time(time);
    			nns[near_pos] = neig;
      		}
      	}
    }

    if(nns.size() == 0)
    {
    	near_pos = -1;
    	nearest = -1;
    	LSH_neig * neig = new LSH_neig;
    	neig->set_id(near_pos);
   		neig->set_dist(nearest);
    	neig->set_time(time);
    	nns[near_pos] = neig;
    }

    R_NNs.push_back(nns);
    nns.clear();
  }

  return R_NNs;
}


int compute_dist (vector_info *x, vector_info *y)
{
  int i, sum=0;

  for (i=0; i< x->get_dim (); i++)
    sum+=abs (x->get_specific_coord(i) - y->get_specific_coord(i));

  return sum;
}


vector <trueNN_node *> find_trueNN (vector <vector_info *> dataset, vector <vector_info *> queries)
{
	int i, j, m, sum, min_sum, posmin;
	trueNN_node *node;
	vector <trueNN_node *> trueNN;
	clock_t time;

	for (i = 0; i<queries.size (); i++)
	{
		time = clock();
		node=new trueNN_node ();

		for (j = 0; j<dataset.size (); j++)
		{
			sum=compute_dist (dataset[j], queries[i]);

			// for (m=0; m<dataset[0]->get_dim (); m++)
			// 	sum+=abs (dataset[j]->get_specific_coord (m)-queries[i]->get_specific_coord (m));

			if (j == 0)
			{
        		posmin = j;
        		min_sum = sum;
				// node->set_id (j);
				// node->set_min_dist (sum);
			}
			else
			{
				if (sum < min_sum)
				{
					min_sum = sum;
          			posmin = j;
          // cout << "j=" << j << endl;
					// node->set_id (j);
					// node->set_min_dist (min_sum);
				}
			}
		}
		// cout << i << "--";
		time = clock() - time;
    	node->set_id (posmin);
    	node->set_min_dist (min_sum);
    	node->set_time((float)time/CLOCKS_PER_SEC);
    	// node->print_info ();
		trueNN.push_back (node);
	}
	// cout << endl;
	return trueNN;
}


bool write_output(string output_file, vector<LSH_neig *> NN, vector<trueNN_node *> tr, vector <map <int, LSH_neig *>> R_NNs, vector<vector_info *> queries, vector<vector_info *> dataset)
{
	ofstream file (output_file);

	double max = -1.0;
	double count = 0.0;
	double av_time = 0.0;

	for(int i = 0; i < NN.size(); i ++) // for every meighbor
	{
		file << "Query: ";
		file << queries[i]->get_str_id()<<endl;                 // str_id

		if(NN[i]->get_id() != -1)
		{

			file << "Nearest neighbor: ";
			file << dataset[NN[i]->get_id()]->get_str_id() << endl; // ALLAKSA TO -1 GIATI EFTIAKSA TA ID -- str_id

			file << "DistanceLSH: ";
			file << NN[i]->get_dist() << endl;

			file << "DistanceTrue: ";
			file << tr[i]->get_min_dist()<<endl;

			count += (double)NN[i]->get_dist()/tr[i]->get_min_dist();

			if((double)NN[i]->get_dist()/tr[i]->get_min_dist() > max)
				max = (double)NN[i]->get_dist()/tr[i]->get_min_dist();


			file << "tLSH: ";
			file << NN[i]->get_time() << endl;

			av_time += NN[i]->get_time();

			file << "tTrue: ";
			file << tr[i]->get_time()<<endl;

			file << "R-near neighbors: "<<endl;
			for(std::map<int, LSH_neig *>::iterator j = R_NNs[i].begin(); j != R_NNs[i].end(); j++)
			{
				if(j->first != -1)
					file << dataset[j->second->get_id()]->get_str_id() <<endl;
				else
					file << "No neighbors in Range R"<<endl;
			}
		}
		else
		{
			file << "Nearest neighbor: No neighbor with LSH"<<endl;

			file << "DistanceLSH: inf"<<endl;

			file << "DistanceTrue: ";
			file << tr[i]->get_min_dist()<<endl;
		}
		file << endl;

	}

	file.close();

	cout << "Average AF = "<< (float)count/queries.size() <<endl;
	cout << "Max AF = " << max << endl;

	cout << "Average time = " << av_time << endl;

	return true;
}
