#pragma once

#include "ikk/core/options.h"

#include <optional>

namespace Ikk::Snapshot {

inline constexpr auto kCloudThemeTitleLimit = 128;

struct CloudThemeRef {
	quint64 user = 0;
	quint64 themeId = 0;
	quint64 accessHash = 0;
	quint64 documentId = 0;
	QString title;
	QString slug;

	friend inline bool operator==(
		const CloudThemeRef &,
		const CloudThemeRef &) = default;
};

[[nodiscard]] std::optional<CloudThemeRef> ParseCloudThemeRef(
	const QByteArray &raw);
[[nodiscard]] QByteArray SerializeCloudThemeRef(const CloudThemeRef &ref);
[[nodiscard]] bool ValidCloudThemeRef(const QByteArray &raw);
[[nodiscard]] bool ValidCloudAccount(const QString &value);

inline const auto kCloudTheme = Option<QByteArray>{
	"ikk.snapshotCloudTheme", Scope::Account, QByteArray(),
	Category::Menu, "lng_ikk_snapshot_cloud_theme",
	static_cast<unsigned>(Flag::Hidden), ValidCloudThemeRef };
inline const auto kCloudAccount = Option<QString>{
	"ikk.snapshotCloudAccount", Scope::Device, QString(),
	Category::Menu, "lng_ikk_snapshot_cloud_theme",
	static_cast<unsigned>(Flag::Hidden), ValidCloudAccount };

inline void RegisterCloudThemeOptions(Registry &registry) {
	Expects(registry.Add(kCloudTheme));
	Expects(registry.Add(kCloudAccount));
}

} // namespace Ikk::Snapshot
