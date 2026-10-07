# Ikk Desktop branding

Ikk Desktop is an independent Telegram client maintained by the Ikk
developers. It is based on Telegram Desktop; upstream source, history,
license and copyright notices remain with their respective authors.

The Ikk name and project identity are controlled by the Ikk developers.
The Ikk icon artwork is Copyright © the Ikk icon authors. All rights
reserved. The artwork is a separate brand asset; the source-code license
does not license its use as the branding of third-party distributions.
Preserve this notice with copied or derived icon assets.

The canonical icon is the Ikk layered artwork, retained in
`Telegram/Resources/branding/Ikk.icon`. Its desktop rendition is exported
with Xcode Icon Composer into `ikk.png`; application PNGs, the Windows ICO,
macOS icon sets and non-macOS tray glyphs are derived from this artwork.
Desktop PNG renditions use 8-bit sRGB with alpha for platform compatibility.

On macOS the bundle icon is compiled from `Ikk.icon` when Xcode 26 or later
is available, so the system renders it. The alternate icons offered in the
settings are the Ikk alternates, retained as `Ikk*.icon` next to it;
`export_icons.py` renders their light and dark renditions into
`Telegram/Resources/ikk/icons`. The same copyright applies to them.
Required upstream and third-party notices remain unchanged.

The macOS menu bar retains the upstream Telegram paper-plane glyph and unread
badge rendering, including its sizing and appearance handling.

Application identity:

- Display name: Ikk Desktop; executable and macOS bundle: Ikk.
- macOS and Linux application ID: `dev.ikk.desktop`.
- Windows application ID: `dev.ikk.desktop` with a distinct installer
  ID and notification activator.
- macOS data directory: `Application Support/Ikk Desktop`; Linux uses
  `IkkDesktop` under the system application data directory. Existing
  Telegram profiles are not imported automatically.
- Portable directory: `IkkForcePortable`.
- Telegram `tg:` and `tonsite:` protocol compatibility is retained.

Upstream crash submission is disabled at build time. Release builds update
themselves from this repository's releases and accept only packages signed
with Ikk keys; the Telegram update feeds are not queried. Other builds
have automatic updates disabled. Manual release links point to this
repository. Store distribution is not configured; desktop builds are
supported. Internal build targets, resource bundle names and Telegram
service/protocol names remain compatible with the upstream build system.
Signing and distribution credentials are kept outside the repository.
