#pragma once

#include "ikk/core/options.h"
#include "ikk/snapshot/cloud_theme_model.h"

#include <QtCore/QJsonObject>
#include <QtGui/QImage>

class HistoryItem;
namespace Ui { class PopupMenu; }
namespace Window {
class SessionController;
namespace Theme {
struct Instance;
} // namespace Theme
} // namespace Window

namespace Ikk::Snapshot {

[[nodiscard]] QJsonObject Defaults();
[[nodiscard]] bool Valid(const QJsonObject &value);
[[nodiscard]] bool Validate(const QByteArray &raw);
[[nodiscard]] std::variant<QImage, QString> Render(
	not_null<Window::SessionController*> controller,
	const MessageIdsList &ids,
	const QJsonObject &options,
	bool revealSpoilers,
	const Window::Theme::Instance *cloud = nullptr);
void InsertAction(
	Ui::PopupMenu *menu,
	Window::SessionController *controller,
	HistoryItem *item,
	MessageIdsList selected);

inline const auto kSettings = Option<QByteArray>{
	"ikk.snapshot", Scope::Device, QByteArray(),
	Category::Menu, "lng_ikk_snapshot", 0, Validate };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kSettings));
	RegisterCloudThemeOptions(registry);
}

} // namespace Ikk::Snapshot
