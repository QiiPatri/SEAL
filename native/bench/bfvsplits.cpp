// BFV per-category registration functions
#include "bench.h"
#include <iomanip>

using namespace benchmark;
using namespace seal;
using namespace sealbench;
using namespace std;

namespace sealbench
{
    void register_bm_family_bfv_enc(const pair<size_t, vector<seal::Modulus>> &parms, unordered_map<seal::EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        seal::EncryptionParameters parms_bfv(seal::scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(seal::PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bfv->context().key_context_data()->total_coeff_modulus_bit_count());
        RegisterBenchmark((string("BFV / 加密")).c_str(), [=](State &st) { bm_bfv_encrypt_combined(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 解密")).c_str(), [=](State &st) { bm_bfv_decrypt_combined(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    // 编码/解码已并入加密/解密基准，不再单独注册。
    }

    void register_bm_family_bfv_add(const pair<size_t, vector<seal::Modulus>> &parms, unordered_map<seal::EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        seal::EncryptionParameters parms_bfv(seal::scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(seal::PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bfv->context().key_context_data()->total_coeff_modulus_bit_count());
        RegisterBenchmark((string("BFV / 密文-密文加法")).c_str(), [=](State &st) { bm_bfv_add_ct(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 密文-明文加法")).c_str(), [=](State &st) { bm_bfv_add_pt(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_bfv_mul(const pair<size_t, vector<seal::Modulus>> &parms, unordered_map<seal::EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        seal::EncryptionParameters parms_bfv(seal::scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(seal::PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bfv->context().key_context_data()->total_coeff_modulus_bit_count());
        RegisterBenchmark((string("BFV / 密文-密文乘法")).c_str(), [=](State &st) { bm_bfv_mul_combined_ct(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 密文-明文乘法")).c_str(), [=](State &st) { bm_bfv_mul_combined_pt(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        // RegisterBenchmark((string("BFV / 平方")).c_str(), [=](State &st) { bm_bfv_square(st, bm_env_bfv); })
        //     ->Unit(benchmark::kMicrosecond)
        //     ->Iterations(10);
    }
}
