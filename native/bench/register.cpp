// Auto-generated split of registry logic from bench.cpp
#include "bench.h"
#include <iomanip>

using namespace benchmark;
using namespace seal;
using namespace sealbench;
using namespace std;

namespace sealbench
{
    void register_bm_family_keygen(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bfv(scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_map.find(parms_bfv)->second->context().key_context_data()->total_coeff_modulus_bit_count());
        SEAL_BENCHMARK_REGISTER(KeyGen, n, log_q, Secret, bm_keygen_secret, bm_env_bfv);
        SEAL_BENCHMARK_REGISTER(KeyGen, n, log_q, Public, bm_keygen_public, bm_env_bfv);
        if (bm_env_bfv->context().using_keyswitching())
        {
            SEAL_BENCHMARK_REGISTER(KeyGen, n, log_q, Relin, bm_keygen_relin, bm_env_bfv);
            SEAL_BENCHMARK_REGISTER(KeyGen, n, log_q, Galois, bm_keygen_galois, bm_env_bfv);
        }
    }

    void register_bm_family_bfv(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bfv(scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bfv->context().key_context_data()->total_coeff_modulus_bit_count());
        // Concise localized BFV registrations (no n=/log(q)= prefix)
        RegisterBenchmark((string("BFV / 加密")).c_str(), [=](State &st) { bm_bfv_encrypt_combined(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 解密")).c_str(), [=](State &st) { bm_bfv_decrypt_combined(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 密文-密文加法")).c_str(), [=](State &st) { bm_bfv_add_ct(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 密文-明文加法")).c_str(), [=](State &st) { bm_bfv_add_pt(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 密文-密文乘法")).c_str(), [=](State &st) { bm_bfv_mul_combined_ct(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 密文-明文乘法")).c_str(), [=](State &st) { bm_bfv_mul_combined_pt(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 编码")).c_str(), [=](State &st) { bm_bfv_encode_batch(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 解码")).c_str(), [=](State &st) { bm_bfv_decode_batch(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BFV / 取负/减法/旋转/重线性化 等" )).c_str(), [=](State &st) { bm_bfv_negate(st, bm_env_bfv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        if (bm_env_bfv->context().first_context_data()->parms().coeff_modulus().size() > 1)
        {
            SEAL_BENCHMARK_REGISTER(BFV, n, log_q, EvaluateModSwitchInplace, bm_bfv_modswitch_inplace, bm_env_bfv);
        }
        if (bm_env_bfv->context().using_keyswitching())
        {
            SEAL_BENCHMARK_REGISTER(BFV, n, log_q, EvaluateRelinInplace, bm_bfv_relin_inplace, bm_env_bfv);
            SEAL_BENCHMARK_REGISTER(BFV, n, log_q, EvaluateRotateRows, bm_bfv_rotate_rows, bm_env_bfv);
            SEAL_BENCHMARK_REGISTER(BFV, n, log_q, EvaluateRotateCols, bm_bfv_rotate_cols, bm_env_bfv);
        }
    }

    void register_bm_family_bgv(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bfv(scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        EncryptionParameters parms_bgv(scheme_type::bgv);
        parms_bgv.set_poly_modulus_degree(parms.first);
        parms_bgv.set_coeff_modulus(parms.second);
        parms_bgv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bgv = bm_env_map.find(parms_bgv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bgv->context().key_context_data()->total_coeff_modulus_bit_count());

        // Concise localized BGV registrations (no n=/log(q)= prefix)
        RegisterBenchmark((string("BGV / 加密")).c_str(), [=](State &st) { bm_bgv_encrypt_combined(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 解密")).c_str(), [=](State &st) { bm_bgv_decrypt_combined(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 密文-密文加法")).c_str(), [=](State &st) { bm_bgv_add_ct(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 密文-明文加法")).c_str(), [=](State &st) { bm_bgv_add_pt(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 密文-密文乘法")).c_str(), [=](State &st) { bm_bgv_mul_combined_ct(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 密文-明文乘法")).c_str(), [=](State &st) { bm_bgv_mul_combined_pt(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 编码")).c_str(), [=](State &st) { bm_bgv_encode_batch(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 解码")).c_str(), [=](State &st) { bm_bgv_decode_batch(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        if (bm_env_bgv->context().first_context_data()->parms().coeff_modulus().size() > 1)
        {
            SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateModSwitchInplace, bm_bgv_modswitch_inplace, bm_env_bgv);
        }
        if (bm_env_bgv->context().using_keyswitching())
        {
            SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateRelinInplace, bm_bgv_relin_inplace, bm_env_bgv);
            SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateRotateRows, bm_bgv_rotate_rows, bm_env_bgv);
            SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateRotateRowsInplace, bm_bgv_rotate_rows_inplace, bm_env_bgv);
            SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateRotateCols, bm_bgv_rotate_cols, bm_env_bgv);
            SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateRotateColsInplace, bm_bgv_rotate_cols_inplace, bm_env_bgv);
        }
        SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateToNTTInplace, bm_bgv_to_ntt_inplace, bm_env_bgv);
        SEAL_BENCHMARK_REGISTER(BGV, n, log_q, EvaluateFromNTTInplace, bm_bgv_from_ntt_inplace, bm_env_bgv);
    }

    // BGV per-category registration
    void register_bm_family_bgv_enc(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bgv(scheme_type::bgv);
        parms_bgv.set_poly_modulus_degree(parms.first);
        parms_bgv.set_coeff_modulus(parms.second);
        parms_bgv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bgv = bm_env_map.find(parms_bgv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bgv->context().key_context_data()->total_coeff_modulus_bit_count());

        // Combined encrypt: merge secret/public encrypt and encode timings into one concise benchmark
        RegisterBenchmark((string("BGV / 加密")).c_str(), [=](State &st) { bm_bgv_encrypt_combined(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);

        // Combined decrypt + decode -> '解密'
        RegisterBenchmark((string("BGV / 解密")).c_str(), [=](State &st) { bm_bgv_decrypt_combined(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_bgv_add(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bgv(scheme_type::bgv);
        parms_bgv.set_poly_modulus_degree(parms.first);
        parms_bgv.set_coeff_modulus(parms.second);
        parms_bgv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bgv = bm_env_map.find(parms_bgv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bgv->context().key_context_data()->total_coeff_modulus_bit_count());

        // Only register concise localized add benchmarks: ciphertext-ciphertext and ciphertext-plaintext
        RegisterBenchmark((string("BGV / 密文-密文加法")).c_str(), [=](State &st) { bm_bgv_add_ct(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 密文-明文加法")).c_str(), [=](State &st) { bm_bgv_add_pt(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_bgv_mul(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bgv(scheme_type::bgv);
        parms_bgv.set_poly_modulus_degree(parms.first);
        parms_bgv.set_coeff_modulus(parms.second);
        parms_bgv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bgv = bm_env_map.find(parms_bgv)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_bgv->context().key_context_data()->total_coeff_modulus_bit_count());

        // Register concise localized multiplication benchmarks (BGV multiply has no rescale)
        RegisterBenchmark((string("BGV / 密文-密文乘法")).c_str(), [=](State &st) { bm_bgv_mul_combined_ct(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("BGV / 密文-明文乘法")).c_str(), [=](State &st) { bm_bgv_mul_combined_pt(st, bm_env_bgv); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_ckks(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_ckks(scheme_type::ckks);
        parms_ckks.set_poly_modulus_degree(parms.first);
        parms_ckks.set_coeff_modulus(parms.second);
        shared_ptr<BMEnv> bm_env_ckks = bm_env_map.find(parms_ckks)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_ckks->context().key_context_data()->total_coeff_modulus_bit_count());

    // CKKS registrations moved to per-category registration functions to allow concise naming.
        if (bm_env_ckks->context().first_context_data()->parms().coeff_modulus().size() > 1)
        {
            SEAL_BENCHMARK_REGISTER(CKKS, n, log_q, EvaluateRescaleInplace, bm_ckks_rescale_inplace, bm_env_ckks);
        }
        if (bm_env_ckks->context().using_keyswitching())
        {
            SEAL_BENCHMARK_REGISTER(CKKS, n, log_q, EvaluateRelinInplace, bm_ckks_relin_inplace, bm_env_ckks);
            SEAL_BENCHMARK_REGISTER(CKKS, n, log_q, EvaluateRotate, bm_ckks_rotate, bm_env_ckks);
        }
    }

    // CKKS per-category registration
    void register_bm_family_ckks_enc(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_ckks(scheme_type::ckks);
        parms_ckks.set_poly_modulus_degree(parms.first);
        parms_ckks.set_coeff_modulus(parms.second);
        shared_ptr<BMEnv> bm_env_ckks = bm_env_map.find(parms_ckks)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_ckks->context().key_context_data()->total_coeff_modulus_bit_count());
        // Register concise, localized names for combined benchmarks (no n= / log(q)= prefix)
        RegisterBenchmark((string("CKKS / 加密")).c_str(), [=](State &st) { bm_ckks_encrypt_combined(st, bm_env_ckks); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);

        // Combined decrypt + decode -> '解密'
        RegisterBenchmark((string("CKKS / 解密")).c_str(), [=](State &st) { bm_ckks_decrypt_combined(st, bm_env_ckks); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_ckks_add(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_ckks(scheme_type::ckks);
        parms_ckks.set_poly_modulus_degree(parms.first);
        parms_ckks.set_coeff_modulus(parms.second);
        shared_ptr<BMEnv> bm_env_ckks = bm_env_map.find(parms_ckks)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_ckks->context().key_context_data()->total_coeff_modulus_bit_count());
        // Only register concise localized add benchmarks (no n= / log(q)= prefix)
        RegisterBenchmark((string("CKKS / 密文-密文加法")).c_str(), [=](State &st) { bm_ckks_add_ct(st, bm_env_ckks); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("CKKS / 密文-明文加法")).c_str(), [=](State &st) { bm_ckks_add_pt(st, bm_env_ckks); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_ckks_mul(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_ckks(scheme_type::ckks);
        parms_ckks.set_poly_modulus_degree(parms.first);
        parms_ckks.set_coeff_modulus(parms.second);
        shared_ptr<BMEnv> bm_env_ckks = bm_env_map.find(parms_ckks)->second;

        int n = static_cast<int>(parms.first);
        int log_q = static_cast<int>(bm_env_ckks->context().key_context_data()->total_coeff_modulus_bit_count());

        // Register concise, localized CKKS multiplication benchmarks (combined operations)
        RegisterBenchmark((string("CKKS / 密文-密文乘法")).c_str(), [=](State &st) { bm_ckks_mul_combined_ct(st, bm_env_ckks); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
        RegisterBenchmark((string("CKKS / 密文-明文乘法")).c_str(), [=](State &st) { bm_ckks_mul_combined_pt(st, bm_env_ckks); })
            ->Unit(benchmark::kMicrosecond)
            ->Iterations(10);
    }

    void register_bm_family_util(const pair<size_t, vector<Modulus>> &parms, unordered_map<EncryptionParameters, shared_ptr<BMEnv>> &bm_env_map)
    {
        EncryptionParameters parms_bfv(scheme_type::bfv);
        parms_bfv.set_poly_modulus_degree(parms.first);
        parms_bfv.set_coeff_modulus(parms.second);
        parms_bfv.set_plain_modulus(PlainModulus::Batching(parms.first, 20));
        shared_ptr<BMEnv> bm_env_bfv = bm_env_map.find(parms_bfv)->second;

        int n = static_cast<int>(parms.first);
        SEAL_BENCHMARK_REGISTER(UTIL, n, 0, NTTForward, bm_util_ntt_forward, bm_env_bfv);
        SEAL_BENCHMARK_REGISTER(UTIL, n, 0, NTTInverse, bm_util_ntt_inverse, bm_env_bfv);
        SEAL_BENCHMARK_REGISTER(UTIL, n, 0, NTTForwardLowLevel, bm_util_ntt_forward_low_level, bm_env_bfv);
        SEAL_BENCHMARK_REGISTER(UTIL, n, 0, NTTInverseLowLevel, bm_util_ntt_inverse_low_level, bm_env_bfv);
        SEAL_BENCHMARK_REGISTER(UTIL, n, 0, NTTForwardLowLevelLazy, bm_util_ntt_forward_low_level_lazy, bm_env_bfv);
        SEAL_BENCHMARK_REGISTER(UTIL, n, 0, NTTInverseLowLevelLazy, bm_util_ntt_inverse_low_level_lazy, bm_env_bfv);
    }

} // namespace sealbench
