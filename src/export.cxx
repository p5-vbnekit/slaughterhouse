#include "main.hxx"

#include "global.h"


P5_SLAUGHTERHOUSE_GLOBAL_EXTERN_C ::this_::main::Boolean
P5_SLAUGHTERHOUSE_GLOBAL_EXPORT Meta_Query(
    char const *version,
    ::this_::main::metamod::plugin::Info **info,
    ::this_::main::metamod::Functions const *functions
) {
    return ::this_::main::metamod::plugin::query(version, info, functions);
}

P5_SLAUGHTERHOUSE_GLOBAL_EXTERN_C ::this_::main::Boolean
P5_SLAUGHTERHOUSE_GLOBAL_EXPORT Meta_Attach(
    ::this_::main::metamod::plugin::Phase phase,
    ::this_::main::metamod::plugin::Functions *functions,
    ::this_::main::metamod::Globals *globals,
    ::this_::main::game::functions::Pointers const *game
) {
    return ::this_::main::metamod::plugin::attach(phase, functions, globals, game);
}

P5_SLAUGHTERHOUSE_GLOBAL_EXTERN_C ::this_::main::Boolean
P5_SLAUGHTERHOUSE_GLOBAL_EXPORT Meta_Detach(
    ::this_::main::metamod::plugin::Phase phase,
    ::this_::main::metamod::plugin::UnloadReason reason
) {
    return ::this_::main::metamod::plugin::detach(phase, reason);
}

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

P5_SLAUGHTERHOUSE_GLOBAL_EXTERN_C void
P5_SLAUGHTERHOUSE_GLOBAL_EXPORT
P5_SLAUGHTERHOUSE_GLOBAL_WINAPI
GiveFnptrsToDll(
    ::this_::main::engine::Functions const *functions,
    ::this_::main::engine::Globals *globals
) {
    return ::this_::main::game::inject(functions, globals);
}
