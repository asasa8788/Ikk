#pragma once

#include "ikk/core/options.h"

namespace Ikk {

inline constexpr auto kShowRpcErrors = Option<bool>{
	"ikk.showRpcErrors", Scope::Device, false,
	Category::Services, "lng_ikk_show_rpc_errors",
	static_cast<unsigned>(Flag::LocalOnly) };

inline void RegisterDiagnosticsOptions(Registry &registry) {
	Expects(registry.Add(kShowRpcErrors));
}

void InstallRpcErrorObserver();

} // namespace Ikk
