#!/usr/bin/env python3
"""One-shot rebrand: Nagram -> Ikk across tracked text files.

Order matters: specific patterns first (URLs, ids, composite tokens),
then the generic case-preserving token replacement. Skips submodules,
the license texts and the changelog (attribution obligations stay).
"""

import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

SKIP_EXACT = {
    "LICENSE",
    "LEGAL",
    "changelog.txt",
    "BRANDING.md",
    "README.md",
}
SKIP_DIRS = ("thirdparty", "lib_webview", "tgcalls")

SPECIFIC = [
    # URLs and identifiers before the generic pass gets a chance.
    ("https://github.com/NextAlone/Nagram-qt/blob/main/LICENSE", "https://github.com/ikk-dev/Ikk/blob/main/LICENSE"),
    ("https://github.com/NextAlone/Nagram-qt/releases/download", "https://github.com/ikk-dev/Ikk/releases/download"),
    ("https://github.com/NextAlone/Nagram-qt/releases", "https://github.com/ikk-dev/Ikk/releases"),
    ("https://github.com/NextAlone/Nagram-qt/issues", "https://github.com/ikk-dev/Ikk/issues"),
    ("https://github.com/NextAlone/Nagram-qt", "https://github.com/ikk-dev/Ikk"),
    ("github.com/NextAlone/Nagram-qt", "github.com/ikk-dev/Ikk"),
    ("NextAlone.NagramDesktop.Store", "dev.ikk.desktop.Store"),
    ("NextAlone.NagramDesktop", "dev.ikk.desktop"),
    ("NextAlone and Nagram contributors", "Ikk developers"),
    ("xyz.nextalone.nagram.desktop", "dev.ikk.desktop"),
    ("NextAlone", "ikk-dev"),
    ("Next Alone", "ikk developers"),
    ("12210746+NextAlone@users.noreply.github.com", "ikk-dev@users.noreply.github.com"),
    # Composite words the generic pass would split wrongly.
    ("NagramDesktop", "IkkDesktop"),
    ("NagramRevision", "IkkRevision"),
    ("NagramChannel", "IkkChannel"),
    ("NAGRAM_UPDATE_KEY", "IKK_UPDATE_KEY"),
    ("NAGRAM_API_ID", "IKK_API_ID"),
    ("NAGRAM_API_HASH", "IKK_API_HASH"),
    ("NAGRAM_NOTARY_APPLE_ID", "IKK_NOTARY_APPLE_ID"),
    ("NAGRAM_NOTARY_KEY_ID", "IKK_NOTARY_KEY_ID"),
    ("NAGRAM_NOTARY_ISSUER_ID", "IKK_NOTARY_ISSUER_ID"),
    ("NAGRAM_NOTARY_KEY", "IKK_NOTARY_KEY"),
    ("NAGRAM_UPDATE_KEY", "IKK_UPDATE_KEY"),
    ("nagram_version_data", "ikk_version_data"),
    ("NagramForcePortable", "IkkForcePortable"),
    ("NagramAlpha_data", "IkkAlpha_data"),
    ("NagramBeta_data", "IkkBeta_data"),
    ("MaitungTM", "the Ikk icon authors"),
]

GENERIC = [
    ("NAGRAM", "IKK"),
    ("Nagram", "Ikk"),
    ("nagram", "ikk"),
]

TEXT_SUFFIXES = {
    ".cpp", ".h", ".hpp", ".mm", ".m", ".c", ".style", ".cmake", ".txt", ".md",
    ".yml", ".yaml", ".json", ".py", ".sh", ".bat", ".ps1", ".qrc", ".xml",
    ".svg", ".strings", ".in", ".iss", ".rc", ".desktop", ".service", ".nix",
    ".gitattributes", ".gitignore", ".plist", ".html", ".css", ".js", ".tla",
    ".metainfo", ".flake", ".toml", ".cfg", ".ini", ".pro", ".pri", ".patch",
    ".diff", ".map", ".tl", ".tlo", ".scheme", ".pem", ".sig", ".sum", ".lock",
}
TEXT_BASENAMES = {
    ".gitmodules", ".gitattributes", ".gitignore", ".clang-tidy", ".clang-format",
    "dockerfile", "makefile", "version",
}


def is_text(path: Path) -> bool:
    if path.name.lower() in TEXT_BASENAMES or path.suffix.lower() in TEXT_SUFFIXES:
        return True
    if path.name in {"version", "changelog.txt"}:
        return True
    return False


def main() -> int:
    files = subprocess.run(
        ["git", "ls-files"], cwd=ROOT, capture_output=True, text=True, check=True
    ).stdout.splitlines()
    changed = 0
    for rel in files:
        p = ROOT / rel
        if not p.is_file():
            continue  # submodule gitlink
        parts = {part.lower() for part in p.parts}
        if parts & set(SKIP_DIRS):
            continue
        if rel in SKIP_EXACT:
            continue
        if not is_text(p):
            continue
        try:
            data = p.read_bytes()
        except OSError:
            continue
        if b"\x00" in data[:8192]:
            continue  # binary
        try:
            text = data.decode("utf-8")
        except UnicodeDecodeError:
            continue
        out = text
        for old, new in SPECIFIC:
            out = out.replace(old, new)
        for old, new in GENERIC:
            out = out.replace(old, new)
        if out != text:
            p.write_bytes(out.encode("utf-8"))
            changed += 1
    print(f"rebranded {changed} files")
    return 0


if __name__ == "__main__":
    sys.exit(main())
