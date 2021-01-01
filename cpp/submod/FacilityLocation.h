

/*
Implementation decisions.
1) Considering the possibility of very large datasets, its safer to use long long int (alias ll) in place of int (for storing size/index of data)

2) Containers like X, groundset, effectiveGroundSet etc (which contain index of datapoints) have been implemented as set (instead of vector).
This is because in C++, set container is implemented as red-black tree and thus search operations happen in log(n) time which is beneficial
for functions like marginalGain(), sequentialUpdate() etc that require such search operations frequently.
If we use vectors then for efficiency we would have an additional responsibility of ensuring that they are sorted. Thus,
set is a more natural choice here

3) For sparse mode, constructor will accept sparse matrix as a collection of 3 component vectors (for csr) and use them to instantiate
a sparse matrix object either using a custom utility class or using some high performance library like boost.

*/
#ifndef NAIVEGREEDYOPTIMIZER_H
#define NAIVEGREEDYOPTIMIZER_H
#include"../optimizers/NaiveGreedyOptimizer.h"
#endif

#ifndef SETFUNCTION_H
#define SETFUNCTION_H
#include"SetFunction.h"
#endif
#include"sparse_utils.h"
typedef long long int ll;

class FacilityLocation :public SetFunction
{

	ll n; 
	ll n_master;
	std::string mode;
	std::vector<std::vector<float>>k_dense;
	SparseSim k_sparse = SparseSim(); 
	std::vector<std::set<ll>>clusters; //vector of clusters (where each cluster is taken as a set of datapoint index)
	ll num_neighbors;
	bool partial;
	bool seperateMaster;
	std::set<ll> effectiveGroundSet;
	std::set<ll> masterSet;
	ll numEffectiveGroundset;
	std::vector<float> similarityWithNearestInEffectiveX;
	//std::map<std::vector<float>, ll>map_data_to_ind;

public:
	//constructor(no_of_elem_in_ground, mode, sim_matrix or cluster, num_neigh, partial, ground_subset )

	//For dense similarity matrix
	FacilityLocation(ll n_, std::string mode_, std::vector<std::vector<float>>k_dense_, ll num_neighbors_, bool partial_, std::set<ll> ground_, bool seperateMaster_);
	
	//For sparse similarity matrix
	FacilityLocation(ll n_, std::string mode_, std::vector<float>arr_val, std::vector<ll>arr_count, std::vector<ll>arr_col, ll num_neighbors_, bool partial_, std::set<ll> ground_);

	//For cluster mode
	FacilityLocation(ll n_, std::string mode_, std::vector<std::set<ll>>clusters_, ll num_neighbors_, bool partial_, std::set<ll> ground_);


	float evaluate(std::set<ll> X);
	float evaluateSequential(std::set<ll> X);
	float marginalGain(std::set<ll> X, ll item);
	float marginalGainSequential(std::set<ll> X, ll item);
	void sequentialUpdate(std::set<ll> X, ll item);
	std::set<ll> getEffectiveGroundSet();
	std::vector<std::pair<ll, float>> maximize(std::string, float budget, bool stopIfZeroGain, bool stopIfNegativeGain, bool verbosity);

	friend float get_max_sim_dense(ll datapoint_ind, std::set<ll> dataset_ind, FacilityLocation obj);
	friend float get_max_sim_sparse(ll datapoint_ind, std::set<ll> dataset_ind, FacilityLocation obj);
};


float get_max_sim_dense(ll datapoint_ind, std::set<ll> dataset_ind, FacilityLocation obj);
float get_max_sim_sparse(ll datapoint_ind, std::set<ll> dataset_ind, FacilityLocation obj);

