# Julius ![](res/julius_48.png)

Chat: [![Gitter](https://badges.gitter.im/julius-game/community.svg)](https://gitter.im/julius-game/community)

|             | Status | Latest release | Latest unstable |
|-------------|--------|----------------|-----------------|
| Windows  | [![AppVeyor](https://ci.appveyor.com/api/projects/status/github/bvschaik/julius?branch=master&svg=true)](https://ci.appveyor.com/project/bvschaik/julius) | [![Download](https://api.bintray.com/packages/bvschaik/julius/windows-release/images/download.svg)](https://bintray.com/bvschaik/julius/windows-release/_latestVersion) | [![Download](https://api.bintray.com/packages/bvschaik/julius/windows-unstable/images/download.svg)](https://bintray.com/bvschaik/julius/windows-unstable/_latestVersion#files) |
| Linux | [![Travis](https://travis-matrix-badges.herokuapp.com/repos/bvschaik/julius/branches/master/1)](https://travis-ci.org/bvschaik/julius) | Next release! | [![Download](https://api.bintray.com/packages/bvschaik/julius/linux-unstable/images/download.svg)](https://bintray.com/bvschaik/julius/linux-unstable/_latestVersion#files) |
| Mac | [![Travis](https://travis-matrix-badges.herokuapp.com/repos/bvschaik/julius/branches/master/5)](https://travis-ci.org/bvschaik/julius) | [![Download](https://api.bintray.com/packages/bvschaik/julius/mac-release/images/download.svg)](https://bintray.com/bvschaik/julius/mac-release/_latestVersion) | [![Download](https://api.bintray.com/packages/bvschaik/julius/mac-unstable/images/download.svg)](https://bintray.com/bvschaik/julius/mac-unstable/_latestVersion#files) |
| PS Vita | [![Travis](https://travis-matrix-badges.herokuapp.com/repos/bvschaik/julius/branches/master/6)](https://travis-ci.org/bvschaik/julius) | [![Download](https://api.bintray.com/packages/bvschaik/julius/vita-release/images/download.svg)](https://bintray.com/bvschaik/julius/vita-release/_latestVersion) | [![Download](https://api.bintray.com/packages/bvschaik/julius/vita-unstable/images/download.svg)](https://bintray.com/bvschaik/julius/vita-unstable/_latestVersion#files) |
| Nintendo Switch | [![Travis](https://travis-matrix-badges.herokuapp.com/repos/bvschaik/julius/branches/master/7)](https://travis-ci.org/bvschaik/julius) | [![Download](https://api.bintray.com/packages/bvschaik/julius/switch-release/images/download.svg)](https://bintray.com/bvschaik/julius/switch-release/_latestVersion) | [![Download](https://api.bintray.com/packages/bvschaik/julius/switch-unstable/images/download.svg)](https://bintray.com/bvschaik/julius/switch-unstable/_latestVersion#files) |

![](https://github.com/bvschaik/julius/blob/master/res/sce_sys/livearea/contents/bg.png?raw=true)

Julius is an open source re-implementation of Caesar III.

The aim of this project is to create an open-source version of Caesar 3, with the same logic
as the original, but with some UI enhancements, that is able to be played on multiple platforms.
The same logic means that the saved games are 100% compatible, and any gameplay bugs
present in the original Caesar 3 game will also be present in Julius.

UI enhancements include:
- Support for widescreen resolutions
- Windowed mode support for 32-bit desktops
- Several small in-game quality of life improvements

Julius requires the original assets (graphics, sounds, etc) from Caesar 3 to run.
It optionally [supports the high-quality MP3 files](doc/mp3_support.md) once provided on the
Sierra website.

## Running the game

First, download the game for your platform from the list above.

Alternatively, you can build Julius yourself. Check [Building Julius](doc/BUILDING.md)
for details.

Then you can either copy the game to the Caesar 3 folder, or run the game from an independent
folder, in which case the game will ask you to point to the Caesar 3 folder.

Note that you must have permission to write in the game data directory as the saves will be
stored there.

See [Running](doc/RUNNING.md) for further instructions and startup options.
