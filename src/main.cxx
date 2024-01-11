#include <cstdint>

#include <string>
#include <utility>
#include <sstream>
#include <stdexcept>

#include <p5/lambda.hxx>

#include "main.hxx"
#include "singleton.hxx"


namespace this_::main {

using Singleton_ = parent_::plugin::Singleton;

template <class ... T> inline static auto print_exception_(auto &stream, T && ...payload) noexcept(true) {
#if false
    try {
        // stream << ::p5::lambda::utils::sugar::format_exception(::std::forward<T>(payload) ...);
    }

    catch(...) {}
#else
    ::p5::lambda::utils::sugar::unused(stream, payload ...);
#endif
}

// `GiveFnptrsToDll` - receive engine function table from engine.
// This appears to be the _first_ DLL routine called by the engine, so we do some setup operations here.
void game::inject(engine::Functions const *functions, engine::Globals *globals) noexcept(true) {
    auto &singleton_ = Singleton_::instance();

    try {
        // singleton_.log << ::LogLevel::Developer
        // << "globals = " << static_cast<void const *>(globals) << ", functions = " << functions;

        if (! static_cast<bool>(globals)) throw ::std::invalid_argument{"globals pointer is null"};
        if (! static_cast<bool>(functions)) throw ::std::invalid_argument{"functions pointer is null"};

        singleton_.engine.globals = globals;
        singleton_.engine.functions = *functions;

        // singleton_.log << ::LogLevel::Developer << "success";
    }

    catch(...) { /* print_exception_(global.log << ::LogLevel::Error << "GiveFnptrsToDll failed: "); */ }
}

// `Meta_Query` - metamod requesting info about this plugin:
// - `version`      (given)     interface_version metamod is using
// - `info`         (requested) struct with info about plugin
// - `functions`    (given)     table of utility functions provided by metamod
Boolean metamod::plugin::query(char const *version, Info **info, parent_::Functions const *functions) noexcept(true) {
    auto &singleton_ = Singleton_::instance();

    try {
        auto &&version_ = ::std::string{singleton_.meta.plugin.info.interface_version};

        // global.log <<::LogLevel::Developer << "interface version = \"" << version_
        // << "\", plugin info = " << static_cast<void const *>(info)
        // << ", util functions = " << static_cast<void const *>(functions);

        if (! static_cast<bool>(info)) throw ::std::invalid_argument{"plugin info pointer is null"};
        *info = &singleton_.meta.plugin.info;

        if (! (static_cast<bool>(version) && singleton_.meta.plugin.info.interface_version == version_)) {
            ::std::ostringstream stream_;
            stream_ << "interface version mismatch: plugin["
                << singleton_.meta.plugin.info.interface_version
                << "] != metamod[" << ::std::move(version_)
            << "]";
            throw ::std::invalid_argument{stream_.str()};
        }

        if (! static_cast<bool>(functions)) throw ::std::invalid_argument{"util functions pointer is null"};
        singleton_.meta.functions = *functions;
        // singleton_.log << ::LogLevel::Developer << "success";

        return Boolean::True;
    }

    catch(...) { /* print_exception_(global.log << ::LogLevel::Error << "Meta_Query failed: "); */ }

    return Boolean::False;
}

// `Meta_Attach` - metamod attaching plugin to the server:
// - `phase`            (given)     current phase, ie during map, during changelevel, or at startup
// - `functions`        (requested) table of function tables this plugin catches
// - `globals`          (given)     global vars from metamod
// - `game_functions`   (given)     copy of function tables from game shared module
Boolean metamod::plugin::attach(
    Phase /*phase*/, Functions *functions, Globals *globals,
    game::functions::Pointers const *game_functions
) noexcept(true) {
    auto &singleton_ = Singleton_::instance();

    try {
        // singleton_.log << ::LogLevel::Developer
        // << "phase = " << static_cast<::std::size_t>(phase) << ", plugin functions = " << static_cast<void const *>(functions)
        // << ", globals = " << static_cast<void const *>(globals) << ", game functions = " << static_cast<void const *>(game);

        if (! static_cast<bool>(singleton_.engine.globals)) throw ::std::runtime_error{"GiveFnptrsToDll failed"};
        if (! static_cast<bool>(functions)) throw ::std::invalid_argument{"plugin functions pointer is null"};
        if (! static_cast<bool>(game_functions)) throw ::std::invalid_argument{"game functions pointer is null"};

        auto const * const standard = game_functions->standard;
        if (! static_cast<bool>(standard)) throw ::std::invalid_argument{"standard game functions pointer is null"};

        auto const * const extension = game_functions->extension;
        if (! static_cast<bool>(extension)) throw ::std::invalid_argument{"\new\" game functions pointer is null"};

        *functions = singleton_.meta.plugin.functions;

        singleton_.meta.globals = globals;
        singleton_.game.functions.standard = *standard;
        singleton_.game.functions.extension = *extension;

        // singleton_.test.attach();
        // singleton_.log << ::LogLevel::Developer << "success";

        return Boolean::True;
    }

    catch(...) { /* print_exception_(global.log << ::LogLevel::Error << "Meta_Attach failed: "); */ }

    return Boolean::False;
}

// `Meta_Detach` - metamod detaching plugin from the server:
// - `phase`    (given) current phase, ie during map, etc
// - `reason`   (given) why detaching (refresh, console unload, forced unload, etc)
Boolean metamod::plugin::detach(Phase /*phase*/, UnloadReason /*reason*/) noexcept(true) {
    auto &singleton_ = Singleton_::instance();

    try {
        // singleton_.log << ::LogLevel::Developer
        // << "phase = " << static_cast<::std::size_t>(phase) << ", reason = " << static_cast<::std::size_t>(reason);

        singleton_.meta.globals = nullptr;
        singleton_.game.functions = {};

        // singleton_.test.detach();
        // singleton_.log << ::LogLevel::Developer << "success";

        return Boolean::True;
    }

    catch(...) { /* print_exception_(singleton_.log << ::LogLevel::Error << "Meta_Detach failed: "); */ }

    return Boolean::False;
}

} // namespace this_::main
