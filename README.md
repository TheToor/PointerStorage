<p align="center">
  <h3 align="center">PointerStorage</h3>
  <p align="center">
    PointerStorage is a SAMP Plugin for in memory storage of PAWN data
    <br />
	<b>This project is no longer maintained</b>
  </p>



## Table of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [License](#license)
* [Acknowledgements](#acknowledgements)



## About The Project

### Prerequisites

N/A

### Installation

1. Add plugin to "plugins" folder
2. Add plugin to server.cfg
3. Add "PointerStorage.inc" to "include" folder

### Build

#### Windows

1. Open "lscrp.sln" with Visual Studio
2. Build project with Visual Studio

#### Linux



## Usage

### Create class and add attributes
```
new classPtr = createClass("Player");
addAttribute(classPtr, INTEGER, "PlayerId");
addAttribute(classPtr, INTEGER, "CharacterId");
addAttribute(classPtr, INTEGER, "Money");
addAttribute(classPtr, INTEGER, "SkinId");
addAttribute(classPtr, STRING, "PlayerName");
addAttribute(classPtr, ARRAY_FLOAT, "FloatArray");
```
### Create entity and set values
```
new tmp = createEntity(classPtr);
setEntityValue(tmp, "PlayerId", 1);
setEntityValue(tmp, "CharacterId", 1);
setEntityValue(tmp, "Money", 1);
setEntityValue(tmp, "SkinId", 1);
setEntityValue(tmp, "PlayerName", "playername");
setEntityValue(tmp, "FloatArray", {0.0, 1.0, 2.0}, 3);
```
### Get values
```
new pID;
getEntityValue(tmp, "PlayerId", pID);
```


## License

Distributed under the GNU General Public License v3.0 License. See `LICENSE` for more information.


## Acknowledgements
* KOBRA: Original source code