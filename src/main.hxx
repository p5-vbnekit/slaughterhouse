#pragma once

#include <p5/lambda/game+fwd.hxx>
#include <p5/lambda/engine+fwd.hxx>
#include <p5/lambda/common+fwd.hxx>
#include <p5/lambda/metamod+fwd.hxx>


namespace this_::main {

namespace parent_ = this_;
namespace this_ = parent_::main;

namespace engine {

namespace parent_ = this_;
namespace this_ = parent_::engine;

using Functions = ::p5::lambda::engine::Functions;
using Globals = ::p5::lambda::engine::Globals;

} // namespace engine

namespace game {

namespace parent_ = this_;
namespace this_ = parent_::game;

void inject(engine::Functions const *, engine::Globals *) noexcept(true);

namespace functions {

namespace parent_ = this_;
namespace this_ = parent_::functions;

using Pointers = ::p5::lambda::game::functions::Pointers;

} // namespace functions
} // namespace game

using Boolean = ::p5::lambda::common::IntegerBoolean;

namespace metamod {

namespace parent_ = this_;
namespace this_ = parent_::metamod;

using Globals = ::p5::lambda::metamod::Globals;
using Functions = ::p5::lambda::metamod::Functions;

namespace plugin {

namespace parent_ = this_;
namespace this_ = parent_::plugin;

using Info = ::p5::lambda::metamod::plugin::Info;
using Phase = ::p5::lambda::metamod::plugin::LoadTime;
using Functions = ::p5::lambda::metamod::plugin::Functions;
using UnloadReason = ::p5::lambda::metamod::plugin::UnloadReason;

Boolean query(char const *, Info **, parent_::Functions const *) noexcept(true);
Boolean attach(Phase, Functions *, Globals *, game::functions::Pointers const *) noexcept(true);
Boolean detach(plugin::Phase, plugin::UnloadReason) noexcept(true);

} // namespace plugin
} // namespace metamod
} // namespace this_::main
