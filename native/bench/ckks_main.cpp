// CKKS specific benchmark runner
#include "bench.h"
#include <iostream>
#include "benchmark/benchmark.h"

using namespace sealbench;
using namespace std;
using namespace benchmark;

int main(int argc, char **argv)
{
    Initialize(&argc, argv);

    cout << "CKKS bench runner" << endl;

    vector<pair<size_t, vector<seal::Modulus>>> bm_parms_vec;
    unordered_map<seal::EncryptionParameters, shared_ptr<BMEnv>> bm_env_map;

    auto default_parms = seal::util::global_variables::GetDefaultCoeffModulus128();
    for (auto &i : default_parms)
    {
        bm_parms_vec.emplace_back(i);
    }

    for (auto &i : default_parms)
    {
        seal::EncryptionParameters parms_ckks(seal::scheme_type::ckks);
        parms_ckks.set_poly_modulus_degree(i.first);
        parms_ckks.set_coeff_modulus(i.second);
        if (bm_env_map.emplace(make_pair(parms_ckks, make_shared<BMEnv>(parms_ckks))).second == false)
        {
            throw invalid_argument("duplicate parameter sets");
        }
    }

    for (auto &i : bm_parms_vec)
    {
        register_bm_family_ckks(i, bm_env_map);
    }

    RunSpecifiedBenchmarks();
}
