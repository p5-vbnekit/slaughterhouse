#pragma once

#include <type_traits>

#include <p5/lambda.hxx>


namespace this_::plugin {

namespace parent_ = this_;
namespace this_ = parent_::plugin;
namespace lambda_ = ::p5::lambda;

struct GameFunctionsPointers final {
    using Standard = lambda_::game::functions::Standard;
    using Extension = lambda_::game::functions::Extension;

    Standard const *standard = nullptr;
    Extension const *extension = nullptr;
};

struct Singleton final : private lambda_::utils::sugar::Uncopyable {
    struct Engine final {
        using Globals = lambda_::engine::Globals;
        using Functions = lambda_::engine::Functions;

        Functions functions = {};
        Globals *globals = nullptr;
    };

    struct Game final {
        using Functions = lambda_::game::Functions;

        Functions functions = {};
    };

    struct Meta final {
        using Globals = lambda_::metamod::Globals;
        using Functions = lambda_::metamod::Functions;

        struct Plugin {
            using Info = lambda_::metamod::plugin::Info;
            using Functions = lambda_::metamod::plugin::Functions;

            Info info {
                .name = P5_SLAUGHTERHOUSE_PLUGIN_NAME,
                .version = P5_SLAUGHTERHOUSE_PLUGIN_VERSION,
                .date = P5_SLAUGHTERHOUSE_PLUGIN_TIMESTAMP,
                .author = "p5-vbnekit <vbnekit@gmail.com>",
                .url = "https://github.com/p5-vbnekit/slaughterhouse",
                .log_tag = "P5SH"
            };

            // Functions functions = hooks::make();
            Functions functions = {};
        };

        Plugin plugin = {};
        Functions functions = {};
        Globals *globals = nullptr;
    };

    Engine engine = {};
    Game game = {};
    Meta meta = {};
//    Test test;

//    template <Logs::Level V = Logs::Level::Info, class ... T> inline auto log(T && ... options) const noexcept(true) {
//        return mLogs.make<V>(::std::forward<T>(options) ...);
//    }

    inline static auto & instance() noexcept(true) { static Singleton instance; return instance; }

private:
//    Logs mLogs {makeLogsOptions()};

//    inline Logs::Options makeLogsOptions() const noexcept(true) {
//        return {
//            meta.plugin.info.logtag,
//            [] () { return Logs::Level::Error; },
//            {},
//            {}
//        };
//    }

    Singleton() = default;
};

} // namespace this_::plugin
