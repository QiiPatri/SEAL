#include "bench.h"
#include <vector>
#include <string>

namespace benchmark
{
    namespace internal
    {
        benchmark::ConsoleReporter::OutputOptions GetOutputOptions(bool force_no_color = false);
    }
}

namespace
{
    // Custom reporter that injects total run time (seconds) into the console output.
    class TotalTimeConsoleReporter : public benchmark::ConsoleReporter
    {
    public:
        TotalTimeConsoleReporter()
            : benchmark::ConsoleReporter(static_cast<benchmark::ConsoleReporter::OutputOptions>(
                  benchmark::internal::GetOutputOptions() | benchmark::ConsoleReporter::OO_Tabular))
        {
        }

    protected:
        void ReportRuns(const std::vector<benchmark::BenchmarkReporter::Run> &reports) override
        {
            std::vector<benchmark::BenchmarkReporter::Run> augmented;
            augmented.reserve(reports.size());
            for (const auto &run : reports)
            {
                augmented.push_back(run);
                auto &mut = augmented.back();
                if (!should_augment(mut))
                {
                    continue;
                }
                const double total_seconds = mut.real_accumulated_time;
                mut.counters["total_time(s)"] = benchmark::Counter(total_seconds);
            }
            benchmark::ConsoleReporter::ReportRuns(augmented);
        }

    private:
        static bool should_augment(const benchmark::BenchmarkReporter::Run &run)
        {
            if (run.report_big_o || run.report_rms)
            {
                return false;
            }
            if (run.run_type != benchmark::BenchmarkReporter::Run::RT_Iteration)
            {
                return false;
            }
            if (run.iterations <= 0)
            {
                return false;
            }
            return true;
        }
    };

    TotalTimeConsoleReporter &get_reporter()
    {
        static TotalTimeConsoleReporter reporter_instance;
        return reporter_instance;
    }
}

namespace sealbench
{
    std::size_t RunBenchmarksWithTotalTime()
    {
        return RunSpecifiedBenchmarks(&get_reporter());
    }
}
