#pragma once

#include "ikk/core/options.h"
#include "ikk/network/model.h"
#include "base/basic_types.h"

namespace Ikk::Network {

inline constexpr auto kIpStrategy = Option<int>{
	"ikk.ipStrategy", Scope::Device, 0,
	Category::Network, "lng_ikk_ip_strategy",
	static_cast<unsigned>(Flag::LocalOnly), ValidIpStrategy };
inline constexpr auto kDisableBackupAddresses = Option<bool>{
	"ikk.disableBackupAddresses", Scope::Device, false,
	Category::Network, "lng_ikk_disable_backup_addresses",
	static_cast<unsigned>(Flag::LocalOnly) };
inline constexpr auto kUseSystemDns = Option<bool>{
	"ikk.useSystemDns", Scope::Device, false,
	Category::Network, "lng_ikk_use_system_dns",
	static_cast<unsigned>(Flag::LocalOnly) };
inline const auto kCustomDoh = Option<QString>{
	"ikk.customDoh", Scope::Device, QString(),
	Category::Network, "lng_ikk_custom_doh",
	static_cast<unsigned>(Flag::LocalOnly), ValidCustomDoh };
inline constexpr auto kTransferFlags = static_cast<unsigned>(Flag::LocalOnly)
	| static_cast<unsigned>(Flag::RequiresRestart);
inline const auto kDownloadSpeedBoost = Option<QString>{
	"ikk.downloadSpeedBoost", Scope::Device, u"none"_q,
	Category::Network, "lng_ikk_download_speed_boost",
	kTransferFlags, ValidDownloadBoost };
inline constexpr auto kUploadSpeedBoost = Option<bool>{
	"ikk.uploadSpeedBoost", Scope::Device, false,
	Category::Network, "lng_ikk_upload_speed_boost",
	kTransferFlags };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kIpStrategy));
	Expects(registry.Add(kDisableBackupAddresses));
	Expects(registry.Add(kUseSystemDns));
	Expects(registry.Add(kCustomDoh));
	Expects(registry.Add(kDownloadSpeedBoost));
	Expects(registry.Add(kUploadSpeedBoost));
}

} // namespace Ikk::Network
