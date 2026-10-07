#pragma once

class HistoryItem;
namespace Ui {
class PopupMenu;
} // namespace Ui
namespace Window {
class SessionController;
} // namespace Window

namespace Ikk::Menu {

void InsertQuickRatingActions(
	Ui::PopupMenu *menu,
	HistoryItem *item,
	Window::SessionController *controller);

} // namespace Ikk::Menu
