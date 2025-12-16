// BGV enc runner
#include "bench.h"
#include <iostream>
#include "benchmark/benchmark.h"

using namespace sealbench;
using namespace std;
using namespace benchmark;

int main(int argc, char **argv)
{
    Initialize(&argc, argv);
    cout << "BGV enc bench runner" << endl;

    vector<pair<size_t, vector<seal::Modulus>>> bm_parms_vec;
    unordered_map<seal::EncryptionParameters, shared_ptr<BMEnv>> bm_env_map;
    auto default_parms = seal::util::global_variables::GetDefaultCoeffModulus128();
    for (auto &i : default_parms)
    {
        if (i.first == 32768) bm_parms_vec.emplace_back(i);
    }
    for (auto &i : bm_parms_vec)
    {
        seal::EncryptionParameters parms_bgv(seal::scheme_type::bgv);
        parms_bgv.set_poly_modulus_degree(i.first);
        parms_bgv.set_coeff_modulus(i.second);
        parms_bgv.set_plain_modulus(seal::PlainModulus::Batching(i.first, 20));
        if (bm_env_map.emplace(make_pair(parms_bgv, make_shared<BMEnv>(parms_bgv))).second == false)
            throw invalid_argument("duplicate parameter sets");
    }
    for (auto &i : bm_parms_vec) register_bm_family_bgv_enc(i, bm_env_map);
    RunBenchmarksWithTotalTime();
}
