#include <vector>
#include <ctime>

using namespace std;

class vector_info
{
	private:
		int id, dim;
		string str_id;
		std::vector<int> coord;

	public:
		void print_info ();

		void set_id (int);
		void set_dim (int);
		void set_str_id (string);
		void set_coord (int);

		int get_id ();
		int get_dim ();
		string get_str_id ();
		int get_specific_coord (int);
		vector<int> get_coord();

		vector_info ();
		~vector_info ();
};

class hash_node
{
	private:
		int id;
		long long int g;

	public:
		void set_id (int);
		void set_g (long long int);

		int get_id ();
		long long int get_g ();

		void print_info ();

		hash_node ();
		~hash_node ();

};


class bucket
{
	private:
		std::vector <hash_node *> v;

	public:
		void add_node (hash_node *);

		std::vector <hash_node *> get_all_nodes ();
		hash_node *get_specific_hash_node (int);

		bucket ();
		~bucket ();
};


class neighboor_frequency
{
	private:
		int id, value;

	public:
		void set_id (int);
		void set_value (int);

		int get_id ();
		int get_value ();

		void increase_value ();

		neighboor_frequency ();
		~neighboor_frequency ();
};


class trueNN_node
{
	private:
		int id, min_dist;
		float time;

	public:
		void set_time(float t);
		void set_id (int);
		void set_min_dist (int);

		int get_id ();
		int get_min_dist ();
		float get_time();

		void print_info ();

		trueNN_node ();
		~trueNN_node ();
};


class LSH_neig
{
	private:
		int id;
		int dist;
		float time;

	public:
		int get_id();
		int get_dist();
		float get_time();

		void set_time(float tt);
		void set_dist(int dd);
		void set_id(int id);

		LSH_neig();

};
