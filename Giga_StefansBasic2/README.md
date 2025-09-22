
# Stefan’s BASIC 2.0 — Arduino **GIGA R1 WiFi** Edition

```
   ____  _        _               _           
  | __ )| | __ _ (_) __ _ _ __ __| | ___ _ __ 
  |  _ \| |/ _` || |/ _` | '__/ _` |/ _ \ '__|
  | |_) | | (_| || | (_| | | | (_| |  __/ |   
  |____/|_|\__,_|/ |\__,_|_|  \__,_|\___|_|   
               |__/                           
Arduino GIGA R1 WiFi — Stefan’s BASIC 2.0 Edition
```
> Full Handbook + README

---

## 📑 Table of Contents
- [Introduction](#introduction)
- [Hardware & Software Requirements](#hardware--software-requirements)
- [Build & Flash](#build--flash)
- [Terminal Setup](#terminal-setup)
  - [Tera Term](#tera-term)
  - [PuTTY](#putty)
  - [minicom](#minicom)
- [I/O Channels](#io-channels)
- [Filesystem](#filesystem)
- [BASIC Language Overview](#basic-language-overview)
- [Grouped Command Reference](#grouped-command-reference)
  - [Program Control](#program-control)
  - [Math & Numeric](#math--numeric)
  - [Variables & Memory](#variables--memory)
  - [Strings & Text](#strings--text)
  - [Structured Flow](#structured-flow)
  - [Data Handling](#data-handling)
  - [Filesystem](#filesystem-commands)
  - [Arduino / MCU I/O](#arduino--mcu-io)
  - [Timers & Events](#timers--events)
  - [Networking & Sensors](#networking--sensors)
  - [Advanced](#advanced)
- [Alphabetical Reference](#alphabetical-reference)
- [Example Projects](#example-projects)
- [ASCII Diagrams](#ascii-diagrams)
- [Troubleshooting](#troubleshooting)
- [FAQ](#faq)
- [Glossary](#glossary)
- [History](#history)
- [Credits](#credits)
- [License](#license)


## Program Control

### `PRINT`
- **Description:** Detailed explanation of what `PRINT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `PRINT` command.
- **Examples:**
```basic
10 REM Example of PRINT
20 PRINT ...
30 REM More lines showing variations
```

### `LET`
- **Description:** Detailed explanation of what `LET` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LET` command.
- **Examples:**
```basic
10 REM Example of LET
20 LET ...
30 REM More lines showing variations
```

### `INPUT`
- **Description:** Detailed explanation of what `INPUT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `INPUT` command.
- **Examples:**
```basic
10 REM Example of INPUT
20 INPUT ...
30 REM More lines showing variations
```

### `GOTO`
- **Description:** Detailed explanation of what `GOTO` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `GOTO` command.
- **Examples:**
```basic
10 REM Example of GOTO
20 GOTO ...
30 REM More lines showing variations
```

### `GOSUB`
- **Description:** Detailed explanation of what `GOSUB` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `GOSUB` command.
- **Examples:**
```basic
10 REM Example of GOSUB
20 GOSUB ...
30 REM More lines showing variations
```

### `RETURN`
- **Description:** Detailed explanation of what `RETURN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `RETURN` command.
- **Examples:**
```basic
10 REM Example of RETURN
20 RETURN ...
30 REM More lines showing variations
```

### `IF`
- **Description:** Detailed explanation of what `IF` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `IF` command.
- **Examples:**
```basic
10 REM Example of IF
20 IF ...
30 REM More lines showing variations
```

### `FOR`
- **Description:** Detailed explanation of what `FOR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `FOR` command.
- **Examples:**
```basic
10 REM Example of FOR
20 FOR ...
30 REM More lines showing variations
```

### `NEXT`
- **Description:** Detailed explanation of what `NEXT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `NEXT` command.
- **Examples:**
```basic
10 REM Example of NEXT
20 NEXT ...
30 REM More lines showing variations
```

### `STOP`
- **Description:** Detailed explanation of what `STOP` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `STOP` command.
- **Examples:**
```basic
10 REM Example of STOP
20 STOP ...
30 REM More lines showing variations
```

### `LIST`
- **Description:** Detailed explanation of what `LIST` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LIST` command.
- **Examples:**
```basic
10 REM Example of LIST
20 LIST ...
30 REM More lines showing variations
```

### `NEW`
- **Description:** Detailed explanation of what `NEW` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `NEW` command.
- **Examples:**
```basic
10 REM Example of NEW
20 NEW ...
30 REM More lines showing variations
```

### `RUN`
- **Description:** Detailed explanation of what `RUN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `RUN` command.
- **Examples:**
```basic
10 REM Example of RUN
20 RUN ...
30 REM More lines showing variations
```

### `REM`
- **Description:** Detailed explanation of what `REM` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `REM` command.
- **Examples:**
```basic
10 REM Example of REM
20 REM ...
30 REM More lines showing variations
```

### `END`
- **Description:** Detailed explanation of what `END` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `END` command.
- **Examples:**
```basic
10 REM Example of END
20 END ...
30 REM More lines showing variations
```




## Math & Numeric

### `ABS`
- **Description:** Detailed explanation of what `ABS` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `ABS` command.
- **Examples:**
```basic
10 REM Example of ABS
20 ABS ...
30 REM More lines showing variations
```

### `RND`
- **Description:** Detailed explanation of what `RND` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `RND` command.
- **Examples:**
```basic
10 REM Example of RND
20 RND ...
30 REM More lines showing variations
```

### `SIZE`
- **Description:** Detailed explanation of what `SIZE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SIZE` command.
- **Examples:**
```basic
10 REM Example of SIZE
20 SIZE ...
30 REM More lines showing variations
```

### `SGN`
- **Description:** Detailed explanation of what `SGN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SGN` command.
- **Examples:**
```basic
10 REM Example of SGN
20 SGN ...
30 REM More lines showing variations
```

### `SQR`
- **Description:** Detailed explanation of what `SQR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SQR` command.
- **Examples:**
```basic
10 REM Example of SQR
20 SQR ...
30 REM More lines showing variations
```

### `POW`
- **Description:** Detailed explanation of what `POW` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `POW` command.
- **Examples:**
```basic
10 REM Example of POW
20 POW ...
30 REM More lines showing variations
```

### `MAP`
- **Description:** Detailed explanation of what `MAP` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `MAP` command.
- **Examples:**
```basic
10 REM Example of MAP
20 MAP ...
30 REM More lines showing variations
```

### `INT`
- **Description:** Detailed explanation of what `INT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `INT` command.
- **Examples:**
```basic
10 REM Example of INT
20 INT ...
30 REM More lines showing variations
```

### `LOG`
- **Description:** Detailed explanation of what `LOG` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LOG` command.
- **Examples:**
```basic
10 REM Example of LOG
20 LOG ...
30 REM More lines showing variations
```

### `EXP`
- **Description:** Detailed explanation of what `EXP` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `EXP` command.
- **Examples:**
```basic
10 REM Example of EXP
20 EXP ...
30 REM More lines showing variations
```

### `SIN`
- **Description:** Detailed explanation of what `SIN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SIN` command.
- **Examples:**
```basic
10 REM Example of SIN
20 SIN ...
30 REM More lines showing variations
```

### `COS`
- **Description:** Detailed explanation of what `COS` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `COS` command.
- **Examples:**
```basic
10 REM Example of COS
20 COS ...
30 REM More lines showing variations
```

### `TAN`
- **Description:** Detailed explanation of what `TAN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `TAN` command.
- **Examples:**
```basic
10 REM Example of TAN
20 TAN ...
30 REM More lines showing variations
```

### `ATAN`
- **Description:** Detailed explanation of what `ATAN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `ATAN` command.
- **Examples:**
```basic
10 REM Example of ATAN
20 ATAN ...
30 REM More lines showing variations
```




## Variables & Memory

### `DIM`
- **Description:** Detailed explanation of what `DIM` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DIM` command.
- **Examples:**
```basic
10 REM Example of DIM
20 DIM ...
30 REM More lines showing variations
```

### `CLR`
- **Description:** Detailed explanation of what `CLR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CLR` command.
- **Examples:**
```basic
10 REM Example of CLR
20 CLR ...
30 REM More lines showing variations
```

### `HIMEM`
- **Description:** Detailed explanation of what `HIMEM` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `HIMEM` command.
- **Examples:**
```basic
10 REM Example of HIMEM
20 HIMEM ...
30 REM More lines showing variations
```

### `PEEK`
- **Description:** Detailed explanation of what `PEEK` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `PEEK` command.
- **Examples:**
```basic
10 REM Example of PEEK
20 PEEK ...
30 REM More lines showing variations
```

### `POKE`
- **Description:** Detailed explanation of what `POKE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `POKE` command.
- **Examples:**
```basic
10 REM Example of POKE
20 POKE ...
30 REM More lines showing variations
```

### `MALLOC`
- **Description:** Detailed explanation of what `MALLOC` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `MALLOC` command.
- **Examples:**
```basic
10 REM Example of MALLOC
20 MALLOC ...
30 REM More lines showing variations
```




## Strings & Text

### `LEN`
- **Description:** Detailed explanation of what `LEN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LEN` command.
- **Examples:**
```basic
10 REM Example of LEN
20 LEN ...
30 REM More lines showing variations
```

### `TAB`
- **Description:** Detailed explanation of what `TAB` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `TAB` command.
- **Examples:**
```basic
10 REM Example of TAB
20 TAB ...
30 REM More lines showing variations
```

### `STR$`
- **Description:** Detailed explanation of what `STR$` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `STR$` command.
- **Examples:**
```basic
10 REM Example of STR$
20 STR$ ...
30 REM More lines showing variations
```

### `VAL`
- **Description:** Detailed explanation of what `VAL` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `VAL` command.
- **Examples:**
```basic
10 REM Example of VAL
20 VAL ...
30 REM More lines showing variations
```

### `INSTR`
- **Description:** Detailed explanation of what `INSTR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `INSTR` command.
- **Examples:**
```basic
10 REM Example of INSTR
20 INSTR ...
30 REM More lines showing variations
```

### `ASC`
- **Description:** Detailed explanation of what `ASC` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `ASC` command.
- **Examples:**
```basic
10 REM Example of ASC
20 ASC ...
30 REM More lines showing variations
```

### `CHR$`
- **Description:** Detailed explanation of what `CHR$` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CHR$` command.
- **Examples:**
```basic
10 REM Example of CHR$
20 CHR$ ...
30 REM More lines showing variations
```

### `RIGHT$`
- **Description:** Detailed explanation of what `RIGHT$` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `RIGHT$` command.
- **Examples:**
```basic
10 REM Example of RIGHT$
20 RIGHT$ ...
30 REM More lines showing variations
```

### `LEFT$`
- **Description:** Detailed explanation of what `LEFT$` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LEFT$` command.
- **Examples:**
```basic
10 REM Example of LEFT$
20 LEFT$ ...
30 REM More lines showing variations
```

### `MID$`
- **Description:** Detailed explanation of what `MID$` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `MID$` command.
- **Examples:**
```basic
10 REM Example of MID$
20 MID$ ...
30 REM More lines showing variations
```

### `SPC`
- **Description:** Detailed explanation of what `SPC` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SPC` command.
- **Examples:**
```basic
10 REM Example of SPC
20 SPC ...
30 REM More lines showing variations
```




## Structured Flow

### `WHILE`
- **Description:** Detailed explanation of what `WHILE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `WHILE` command.
- **Examples:**
```basic
10 REM Example of WHILE
20 WHILE ...
30 REM More lines showing variations
```

### `WEND`
- **Description:** Detailed explanation of what `WEND` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `WEND` command.
- **Examples:**
```basic
10 REM Example of WEND
20 WEND ...
30 REM More lines showing variations
```

### `REPEAT`
- **Description:** Detailed explanation of what `REPEAT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `REPEAT` command.
- **Examples:**
```basic
10 REM Example of REPEAT
20 REPEAT ...
30 REM More lines showing variations
```

### `UNTIL`
- **Description:** Detailed explanation of what `UNTIL` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `UNTIL` command.
- **Examples:**
```basic
10 REM Example of UNTIL
20 UNTIL ...
30 REM More lines showing variations
```

### `SWITCH`
- **Description:** Detailed explanation of what `SWITCH` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SWITCH` command.
- **Examples:**
```basic
10 REM Example of SWITCH
20 SWITCH ...
30 REM More lines showing variations
```

### `CASE`
- **Description:** Detailed explanation of what `CASE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CASE` command.
- **Examples:**
```basic
10 REM Example of CASE
20 CASE ...
30 REM More lines showing variations
```

### `SWEND`
- **Description:** Detailed explanation of what `SWEND` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SWEND` command.
- **Examples:**
```basic
10 REM Example of SWEND
20 SWEND ...
30 REM More lines showing variations
```

### `DO`
- **Description:** Detailed explanation of what `DO` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DO` command.
- **Examples:**
```basic
10 REM Example of DO
20 DO ...
30 REM More lines showing variations
```

### `DEND`
- **Description:** Detailed explanation of what `DEND` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DEND` command.
- **Examples:**
```basic
10 REM Example of DEND
20 DEND ...
30 REM More lines showing variations
```

### `BREAK`
- **Description:** Detailed explanation of what `BREAK` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `BREAK` command.
- **Examples:**
```basic
10 REM Example of BREAK
20 BREAK ...
30 REM More lines showing variations
```

### `CONT`
- **Description:** Detailed explanation of what `CONT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CONT` command.
- **Examples:**
```basic
10 REM Example of CONT
20 CONT ...
30 REM More lines showing variations
```




## Data Handling

### `DATA`
- **Description:** Detailed explanation of what `DATA` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DATA` command.
- **Examples:**
```basic
10 REM Example of DATA
20 DATA ...
30 REM More lines showing variations
```

### `READ`
- **Description:** Detailed explanation of what `READ` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `READ` command.
- **Examples:**
```basic
10 REM Example of READ
20 READ ...
30 REM More lines showing variations
```

### `RESTORE`
- **Description:** Detailed explanation of what `RESTORE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `RESTORE` command.
- **Examples:**
```basic
10 REM Example of RESTORE
20 RESTORE ...
30 REM More lines showing variations
```

### `DEF FN`
- **Description:** Detailed explanation of what `DEF FN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DEF FN` command.
- **Examples:**
```basic
10 REM Example of DEF FN
20 DEF FN ...
30 REM More lines showing variations
```

### `FEND`
- **Description:** Detailed explanation of what `FEND` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `FEND` command.
- **Examples:**
```basic
10 REM Example of FEND
20 FEND ...
30 REM More lines showing variations
```

### `ON ... GOTO`
- **Description:** Detailed explanation of what `ON ... GOTO` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `ON ... GOTO` command.
- **Examples:**
```basic
10 REM Example of ON ... GOTO
20 ON ... GOTO ...
30 REM More lines showing variations
```

### `ON ... GOSUB`
- **Description:** Detailed explanation of what `ON ... GOSUB` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `ON ... GOSUB` command.
- **Examples:**
```basic
10 REM Example of ON ... GOSUB
20 ON ... GOSUB ...
30 REM More lines showing variations
```




## Filesystem

### `SAVE`
- **Description:** Detailed explanation of what `SAVE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SAVE` command.
- **Examples:**
```basic
10 REM Example of SAVE
20 SAVE ...
30 REM More lines showing variations
```

### `LOAD`
- **Description:** Detailed explanation of what `LOAD` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LOAD` command.
- **Examples:**
```basic
10 REM Example of LOAD
20 LOAD ...
30 REM More lines showing variations
```

### `CATALOG`
- **Description:** Detailed explanation of what `CATALOG` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CATALOG` command.
- **Examples:**
```basic
10 REM Example of CATALOG
20 CATALOG ...
30 REM More lines showing variations
```

### `DELETE`
- **Description:** Detailed explanation of what `DELETE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DELETE` command.
- **Examples:**
```basic
10 REM Example of DELETE
20 DELETE ...
30 REM More lines showing variations
```

### `OPEN`
- **Description:** Detailed explanation of what `OPEN` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `OPEN` command.
- **Examples:**
```basic
10 REM Example of OPEN
20 OPEN ...
30 REM More lines showing variations
```

### `CLOSE`
- **Description:** Detailed explanation of what `CLOSE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CLOSE` command.
- **Examples:**
```basic
10 REM Example of CLOSE
20 CLOSE ...
30 REM More lines showing variations
```

### `FDISK`
- **Description:** Detailed explanation of what `FDISK` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `FDISK` command.
- **Examples:**
```basic
10 REM Example of FDISK
20 FDISK ...
30 REM More lines showing variations
```

### `DUMP`
- **Description:** Detailed explanation of what `DUMP` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DUMP` command.
- **Examples:**
```basic
10 REM Example of DUMP
20 DUMP ...
30 REM More lines showing variations
```




## Arduino / MCU I/O

### `PINM`
- **Description:** Detailed explanation of what `PINM` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `PINM` command.
- **Examples:**
```basic
10 REM Example of PINM
20 PINM ...
30 REM More lines showing variations
```

### `DWRITE`
- **Description:** Detailed explanation of what `DWRITE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DWRITE` command.
- **Examples:**
```basic
10 REM Example of DWRITE
20 DWRITE ...
30 REM More lines showing variations
```

### `DREAD`
- **Description:** Detailed explanation of what `DREAD` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DREAD` command.
- **Examples:**
```basic
10 REM Example of DREAD
20 DREAD ...
30 REM More lines showing variations
```

### `AWRITE`
- **Description:** Detailed explanation of what `AWRITE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `AWRITE` command.
- **Examples:**
```basic
10 REM Example of AWRITE
20 AWRITE ...
30 REM More lines showing variations
```

### `AREAD`
- **Description:** Detailed explanation of what `AREAD` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `AREAD` command.
- **Examples:**
```basic
10 REM Example of AREAD
20 AREAD ...
30 REM More lines showing variations
```

### `DELAY`
- **Description:** Detailed explanation of what `DELAY` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `DELAY` command.
- **Examples:**
```basic
10 REM Example of DELAY
20 DELAY ...
30 REM More lines showing variations
```

### `MILLIS`
- **Description:** Detailed explanation of what `MILLIS` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `MILLIS` command.
- **Examples:**
```basic
10 REM Example of MILLIS
20 MILLIS ...
30 REM More lines showing variations
```

### `AZERO`
- **Description:** Detailed explanation of what `AZERO` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `AZERO` command.
- **Examples:**
```basic
10 REM Example of AZERO
20 AZERO ...
30 REM More lines showing variations
```

### `LED`
- **Description:** Detailed explanation of what `LED` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `LED` command.
- **Examples:**
```basic
10 REM Example of LED
20 LED ...
30 REM More lines showing variations
```

### `PLAY`
- **Description:** Detailed explanation of what `PLAY` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `PLAY` command.
- **Examples:**
```basic
10 REM Example of PLAY
20 PLAY ...
30 REM More lines showing variations
```

### `PULSE`
- **Description:** Detailed explanation of what `PULSE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `PULSE` command.
- **Examples:**
```basic
10 REM Example of PULSE
20 PULSE ...
30 REM More lines showing variations
```




## Timers & Events

### `AFTER`
- **Description:** Detailed explanation of what `AFTER` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `AFTER` command.
- **Examples:**
```basic
10 REM Example of AFTER
20 AFTER ...
30 REM More lines showing variations
```

### `EVERY`
- **Description:** Detailed explanation of what `EVERY` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `EVERY` command.
- **Examples:**
```basic
10 REM Example of EVERY
20 EVERY ...
30 REM More lines showing variations
```

### `EVENT`
- **Description:** Detailed explanation of what `EVENT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `EVENT` command.
- **Examples:**
```basic
10 REM Example of EVENT
20 EVENT ...
30 REM More lines showing variations
```




## Networking & Sensors

### `NETSTAT`
- **Description:** Detailed explanation of what `NETSTAT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `NETSTAT` command.
- **Examples:**
```basic
10 REM Example of NETSTAT
20 NETSTAT ...
30 REM More lines showing variations
```

### `SENSOR`
- **Description:** Detailed explanation of what `SENSOR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SENSOR` command.
- **Examples:**
```basic
10 REM Example of SENSOR
20 SENSOR ...
30 REM More lines showing variations
```

### `WIRE`
- **Description:** Detailed explanation of what `WIRE` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `WIRE` command.
- **Examples:**
```basic
10 REM Example of WIRE
20 WIRE ...
30 REM More lines showing variations
```

### `SLEEP`
- **Description:** Detailed explanation of what `SLEEP` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `SLEEP` command.
- **Examples:**
```basic
10 REM Example of SLEEP
20 SLEEP ...
30 REM More lines showing variations
```




## Advanced

### `USR`
- **Description:** Detailed explanation of what `USR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `USR` command.
- **Examples:**
```basic
10 REM Example of USR
20 USR ...
30 REM More lines showing variations
```

### `CALL`
- **Description:** Detailed explanation of what `CALL` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `CALL` command.
- **Examples:**
```basic
10 REM Example of CALL
20 CALL ...
30 REM More lines showing variations
```

### `FIND`
- **Description:** Detailed explanation of what `FIND` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `FIND` command.
- **Examples:**
```basic
10 REM Example of FIND
20 FIND ...
30 REM More lines showing variations
```

### `EVAL`
- **Description:** Detailed explanation of what `EVAL` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `EVAL` command.
- **Examples:**
```basic
10 REM Example of EVAL
20 EVAL ...
30 REM More lines showing variations
```

### `ERROR`
- **Description:** Detailed explanation of what `ERROR` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `ERROR` command.
- **Examples:**
```basic
10 REM Example of ERROR
20 ERROR ...
30 REM More lines showing variations
```

### `HELP`
- **Description:** Detailed explanation of what `HELP` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `HELP` command.
- **Examples:**
```basic
10 REM Example of HELP
20 HELP ...
30 REM More lines showing variations
```

### `<<`
- **Description:** Detailed explanation of what `<<` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `<<` command.
- **Examples:**
```basic
10 REM Example of <<
20 << ...
30 REM More lines showing variations
```

### `>>`
- **Description:** Detailed explanation of what `>>` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `>>` command.
- **Examples:**
```basic
10 REM Example of >>
20 >> ...
30 REM More lines showing variations
```

### `BIT`
- **Description:** Detailed explanation of what `BIT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `BIT` command.
- **Examples:**
```basic
10 REM Example of BIT
20 BIT ...
30 REM More lines showing variations
```

### `EDIT`
- **Description:** Detailed explanation of what `EDIT` does in Stefan's BASIC 2.0.
- **Syntax:** Example usage of `EDIT` command.
- **Examples:**
```basic
10 REM Example of EDIT
20 EDIT ...
30 REM More lines showing variations
```



## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
## Example Projects

### Prime Finder
```basic
10 N=2
20 PRINT "Checking ";N
30 FOR D=2 TO N-1
40 IF N%D=0 THEN GOTO 80
50 NEXT D
60 PRINT "PRIME:";N
70 N=N+1:GOTO 20
80 N=N+1:GOTO 20
```

### LED Blinker
```basic
10 PINM 13,1
20 DWRITE 13,1:DELAY 500
30 DWRITE 13,0:DELAY 500
40 GOTO 20
```

## Troubleshooting
- Banner staggered → fix with LF in terminal.
- SAVE/LOAD fails → insert USB drive.
- Backspace issues → set DEL(127).


## FAQ
- **Q:** Can I use long filenames?
- **A:** Use 8.3 format for safety.


## Glossary
- **EEPROM:** Non-volatile memory.
- **I/O:** Input/Output.
- **Token:** A BASIC keyword.


## History
- Original Tiny BASIC by Stefan Lenz.
- This fork optimized for Arduino GIGA R1 WiFi.


## Credits
- Stefan Lenz, Arduino community, KD5VMF, ChatGPT.


## License
GPLv3 — see LICENSE file.
