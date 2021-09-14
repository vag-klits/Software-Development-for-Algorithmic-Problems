#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "classes.h"

using namespace std;

vector_info::vector_info ()
{
	id=-1;
	dim=-1;
	return;
}

vector_info::~vector_info ()
{
	coord.clear ();
	return;
}

void vector_info::set_id (int x)
{
	id=x;
	return;
}

void vector_info::set_dim (int x)
{
	dim=x;
	return;
}

void vector_info::set_str_id (string x)
{
	str_id=x;
	return;
}

void vector_info::set_coord (int x)
{
	coord.push_back (x);
	return;
}

vector<int> vector_info::get_coord()
{
	return this->coord;
}

int vector_info::get_id ()
{
	return id;
}

int vector_info::get_dim ()
{
	return dim;
}

string vector_info::get_str_id ()
{
	return str_id;
}

int vector_info::get_specific_coord (int i)
{
	if (i>coord.size ()-1)
		return -1;

	return coord[i];
}


void vector_info::print_info ()
{
	cout << "id=" << id << endl;
	cout << "dim=" << dim << endl;
	for (int i=0; i<coord.size (); i++)
		cout << coord[i] << " " << endl;

	return;
}

hash_node::hash_node ()
{
	id=-1;
	return;
}

hash_node::~hash_node ()
{
	return;
}

void hash_node::set_id (int x)
{
	id=x;
	return;
}

void hash_node::set_g (long long int x)
{
	g=x;
	return;
}

int hash_node::get_id ()
{
	return id;
}

long long int hash_node::get_g ()
{
	return g;
}

void hash_node::print_info ()
{
	cout << id << " -- " << g << endl;
	return;
}


bucket::bucket ()
{
	return;
}

bucket::~bucket ()
{
	v.clear ();
}

void bucket::add_node (hash_node *x)
{
	v.push_back (x);
	return;
}

vector <hash_node *> bucket::get_all_nodes ()
{
	return v;
}

hash_node *bucket::get_specific_hash_node (int i)
{
	if (i<v.size ())
		return v[i];
	else
		return NULL;
}


neighboor_frequency::neighboor_frequency ()
{
	id=-1;
	value=-1;
	return;
}

neighboor_frequency::~neighboor_frequency ()
{
	return;
}

void neighboor_frequency::set_id (int x)
{
	id=x;
	return;
}

void neighboor_frequency::set_value (int x)
{
	value=x;
	return;
}

int neighboor_frequency::get_id ()
{
	return id;
}

int neighboor_frequency::get_value ()
{
	return value;
}

void neighboor_frequency::increase_value ()
{
	value++;
	return;
}

trueNN_node::trueNN_node ()
{
	id=-1;
	return;
}

trueNN_node::~trueNN_node ()
{
	return;
}

void trueNN_node::set_id (int x)
{
	id=x;
	return;
}

void trueNN_node::set_min_dist (int x)
{
	min_dist=x;
	return;
}

void trueNN_node::set_time(float t)
{
	this->time = t;
}

int trueNN_node::get_id ()
{
	return id;
}

float trueNN_node::get_time()
{
	return this->time;
}

int trueNN_node::get_min_dist ()
{
	return min_dist;
}

void trueNN_node::print_info ()
{
	cout << "id= " << id << " -- " << "min_dist=  " << min_dist << endl;
	return;
}


LSH_neig::LSH_neig()
{
	this->id = -1;
	this->dist = -1;
}

int LSH_neig::get_id()
{
	return this->id;
}

int LSH_neig::get_dist()
{
	return this->dist;
}

float LSH_neig::get_time()
{
	return this->time;
}

void LSH_neig::set_time(float tt)
{
	this->time = tt;
}

void LSH_neig::set_id(int id)
{
	this->id = id;
}

void LSH_neig::set_dist(int dd)
{
	this->dist = dd;
}
