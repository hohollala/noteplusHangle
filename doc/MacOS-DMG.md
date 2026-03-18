# Building A macOS DMG

This repository includes a custom `dmg_custom` target for generating a macOS installer disk image.

## Requirements

- macOS
- Qt installed with `macdeployqt` available in `PATH`
- CMake
- A configured build directory

## Build The App

Configure the project if you have not already:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

Build the app bundle:

```bash
cmake --build build --target NotepadNext -j4
```

## Create The DMG

Run:

```bash
cmake --build build --target dmg_custom -j4
```

This target will:

- install the app bundle into `build/install/NotepadNext.app`
- run `macdeployqt`
- generate a custom DMG using `scripts/create-mac-installer.sh`

The final installer will be written to:

```text
build/NotepadNext-v<version>.dmg
```

For the current project version, that is typically:

```text
build/NotepadNext-v0.13.dmg
```

## Install Locally

To install the generated DMG manually:

1. Open the generated `.dmg`.
2. Drag `NotepadNext.app` into `/Applications`.

If macOS blocks the first launch for an ad-hoc signed local build, remove quarantine:

```bash
xattr -dr com.apple.quarantine /Applications/NotepadNext.app
```

## Related Files

- `cmake/PackagingMac.cmake`
- `scripts/create-mac-installer.sh`
