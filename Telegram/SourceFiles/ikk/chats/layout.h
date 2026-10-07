#pragma once

namespace style {
struct DialogRow;
} // namespace style

namespace Ikk::Chats {

[[nodiscard]] const style::DialogRow &RowStyle(bool hasTags, bool wideRow);
[[nodiscard]] int PreviewLines();
[[nodiscard]] bool HideSavedAndArchivedPreviews();
[[nodiscard]] bool HidePreview(bool folder, bool savedMessages);
[[nodiscard]] QString HiddenPreviewText(bool folder);
[[nodiscard]] bool HideStories();
[[nodiscard]] bool ShowArchiveInFolders();
[[nodiscard]] bool HideFolderUnreadCounters();

} // namespace Ikk::Chats
