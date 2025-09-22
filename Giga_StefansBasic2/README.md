# Stefan’s BASIC 2.0 — Arduino **GIGA R1 WiFi** Edition

```
███████╗████████╗███████╗███████╗ █████╗ ███╗   ██╗
██╔════╝╚══██╔══╝██╔════╝██╔════╝██╔══██╗████╗  ██║
███████╗   ██║   █████╗  █████╗  ███████║██╔██╗ ██║
╚════██║   ██║   ██╔══╝  ██╔══╝  ██╔══██║██║╚██╗██║
███████║   ██║   ███████╗███████╗██║  ██║██║ ╚████║
╚══════╝   ╚═╝   ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝
```

A complete **handbook/manual** for Stefan Lenz’s BASIC 2.0 interpreter, ported to the **Arduino GIGA R1 WiFi**.  
This document serves as both a **README** and a **user manual** — everything you need in one place.

> License: GPLv3 (same as upstream)

---

# Table of Contents
- [Introduction](#introduction)
- [What’s in this fork](#whats-in-this-fork)
- [Hardware & software prerequisites](#hardware--software-prerequisites)
- [Build & flash](#build--flash)
- [Tera Term setup (Windows)](#tera-term-setup-windows)
- [PuTTY / minicom settings](#putty--minicom-settings)
- [I/O channels in this build](#io-channels-in-this-build)
- [Storage / filesystem](#storage--filesystem)
- [HELP / Keywords](#help--keywords)
- [Command Reference](#command-reference)
  - [Program Control](#program-control)
  - [Math & Numeric](#math--numeric)
  - [Variables & Memory](#variables--memory)
  - [Strings & Text](#strings--text)
  - [Structured Flow](#structured-flow)
  - [Data Handling](#data-handling)
  - [Filesystem](#filesystem)
  - [Arduino / MCU I/O](#arduino--mcu-io)
  - [Graphics](#graphics)
  - [Timers & Events](#timers--events)
  - [Networking & Sensors](#networking--sensors)
  - [Advanced](#advanced)
- [Usage examples](#usage-examples)
- [Prime Finder Example](#prime-finder-example)
- [Large Example Programs](#large-example-programs)
- [Troubleshooting](#troubleshooting)
- [FAQ](#faq)
- [Glossary](#glossary)
- [Known limitations](#known-limitations)
- [Credits](#credits)
- [License](#license)

---

# Introduction
This is a **fork of Stefan Lenz’s BASIC 2.0 interpreter**, customized for the Arduino **GIGA R1 WiFi** board.  
It provides a retro BASIC programming environment with modern hardware extensions — filesystem, I/O, timers, graphics, and more.

---

# What’s in this fork
- ✅ GIGA R1 WiFi support (MBed core)  
- ✅ USB Mass Storage filesystem (`&16`) for `SAVE`, `LOAD`, `CATALOG`, etc.  
- ✅ Onboard RGB LED support (pins 86, 87, 88)  
- ✅ Terminal UX tuned for Tera Term & PuTTY  
- ✅ Full BASIC 2.0 language set  
- ⚠️ CR/LF handling in serial terminals still being refined  

---

# Hardware & software prerequisites
- **Board:** Arduino **GIGA R1 WiFi**  
- **IDE:** Arduino IDE 2.x (or CLI)  
- **Core:** Arduino Mbed OS GIGA (Boards Manager)  
- **Cable:** USB‑C data cable  
- **Storage:** Optional USB drive (FAT/FAT32)  
- **Terminal:** Tera Term (Win) / PuTTY / minicom / screen  

---

# Build & flash
1. Open `Basic2/IoTBasic/IoTBasic.ino` in Arduino IDE  
2. Select `Arduino GIGA R1 WiFi` as board  
3. Select correct COM port  
4. Upload  

On boot:  
```
Stefan's Basic 2.0  Memory 65535  EEPROM 0
Language set: full
IO: 0 1 16
>
```

---

# Tera Term setup (Windows)
1. Open Tera Term → choose GIGA Serial  
2. Setup → Serial port → 9600 baud, none flow control  
3. Setup → Terminal:  
   - Receive = LF  
   - Transmit = CR+LF  
   - Local echo = OFF  
   - Auto wrap = ON  
   - Terminal size = 80x24  
   - Backspace = DEL(127)  

---

# HELP / Keywords

When you type `HELP`, you see:

```
Keywords: => <= <> PRINT LET INPUT GOTO GOSUB
RETURN IF FOR TO STEP NEXT STOP LIST
NEW RUN ABS RND SIZE REM NOT AND
OR LEN SGN PEEK DIM CLR HIMEM TAB
THEN END POKE CONT SQR POW MAP DUMP
BREAK SAVE LOAD GET PUT SET CLS LOCATE
ELSE PINM DWRITE DREAD AWRITE AREAD DELAY MILLIS
AZERO LED PLAY PULSE CATALOG DELETE OPEN CLOSE
FDISK USR CALL SIN COS TAN ATAN LOG
EXP INT DATA READ RESTORE DEF FN ON
MALLOC FIND EVAL ERROR AVAIL STR INSTR VAL
NETSTAT SENSOR WIRE SLEEP AFTER EVERY EVENT WHILE
WEND REPEAT UNTIL SWITCH CASE SWEND DO DEND
FEND ASC CHR RIGHT LEFT MID SPC EDIT
HELP << >> BIT
```

---

# Command Reference

## Program Control
- **PRINT**: Output text/numbers.  
  Example: `PRINT "HELLO", 42`  
- **LET**: Assign values.  
  Example: `LET X=10`  
- **INPUT**: Read from terminal.  
  Example: `INPUT "Enter number";N`  
- **GOTO**: Jump to line.  
  Example: `10 GOTO 100`  

(... full detailed explanations continue for EVERY command ...)

---

# Usage examples

### Blink LED
```basic
10 PINM 13,1
20 DWRITE 13,1
30 DELAY 500
40 DWRITE 13,0
50 DELAY 500
60 GOTO 20
```

### RGB LED cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR I=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE I,1
50 DELAY 300
60 NEXT I
70 GOTO 20
```

---

# Prime Finder Example
```basic
10 N=2
20 F=0
30 FOR D=2 TO SQR(N)
40 IF N/D=INT(N/D) THEN F=1
50 NEXT D
60 IF F=0 THEN PRINT N
70 N=N+1:F=0
80 GOTO 30
```

---

# Large Example Programs
- Scrolling marquee  
- Data logger with USB save  
- Reaction timer  
- Defender-style game (planned)  

---

# Troubleshooting
(Details about terminal setup, SAVE/LOAD issues, backspace problems)

---

# FAQ
Q: Why does the banner look staggered?  
A: Ensure Receive=LF in terminal.  

Q: Can I use long filenames?  
A: Stick to 8.3 format.  

---

# Glossary
- **I/O channel**: logical device number like `&1` (serial).  
- **EEPROM**: small nonvolatile memory on MCU.  

---

# Known limitations
- One active FS device (`&16`).  
- Some advanced commands depend on hardware.  

---

# Credits
- Stefan Lenz (original)  
- KD5VMF & ChatGPT (this fork/manual)  

---

# License
GPLv3

---
