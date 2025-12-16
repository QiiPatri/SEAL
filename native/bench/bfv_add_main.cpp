// BFV add runner
#include "bench.h"
#include <iostream>
#include "benchmark/benchmark.h"

using namespace sealbench;
using namespace std;
using namespace benchmark;

int main(int argc, char **argv)
{
    Initialize(&argc, argv);
    cout << "BFV add bench runner" << endl;

    vector<pair<size_t, vector<seal::Modulus>>> bm_parms_vec;
    unordered_map<seal::EncryptionParameters, shared_ptr<BMEnv>> bm_env_map;
    auto default_parms = seal::util::global_variables::GetDefaultCoeffModulus128();
    for (auto &i : default_parms)
    {
        if (i.first == 32768) bm_parms_vec.emplace_back(i);
    }
    for (auto &i : bm_parms_vec)
    {
        seal::EncryptionParameters parms_bfv(seal::scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(i.first);
        parms_bfv.set_coeff_modulus(i.second);
        parms_bfv.set_plain_modulus(seal::PlainModulus::Batching(i.first, 20));
        if (bm_env_map.emplace(make_pair(parms_bfv, make_shared<BMEnv>(parms_bfv))).second == false)
            throw invalid_argument("duplicate parameter sets");
    }
    for (auto &i : bm_parms_vec) register_bm_family_bfv_add(i, bm_env_map);
    RunBenchmarksWithTotalTime();
}
