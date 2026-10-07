#pragma once

#include "ikk/media/options.h"
#include "lang/lang_keys.h"
#include "styles/style_menu_icons.h"

class DocumentData;
namespace Window {
class SessionController;
} // namespace Window

namespace Ikk::Media {

[[nodiscard]] int GifMaxSize(int fallback);
[[nodiscard]] int StickerPanelCell(int fallback);
[[nodiscard]] bool AutoDownloadBlocked(not_null<DocumentData*> document);
void ShowDownloads(not_null<Window::SessionController*> controller);

template <typename AddAction>
void AddDownloadsMenuItem(
		AddAction &&addAction,
		not_null<Window::SessionController*> controller) {
	if (!ForDevice().Get(kDownloadsInMainMenu)) {
		return;
	}
	addAction(
		tr::lng_ikk_downloads(),
		{ &st::menuIconDownload },
		u"downloads"_q
	)->setClickedCallback([=] {
		ShowDownloads(controller);
	});
}

} // namespace Ikk::Media
