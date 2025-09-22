# 📘 Stefan’s BASIC 2.0 — Arduino **GIGA R1 WiFi** Edition  
*A Complete Handbook / Full Manual*

```
███████╗████████╗███████╗███████╗ █████╗ ███╗   ██╗
██╔════╝╚══██╔══╝██╔════╝██╔════╝██╔══██╗████╗  ██║
███████╗   ██║   █████╗  █████╗  ███████║██╔██╗ ██║
╚════██║   ██║   ██╔══╝  ██╔══╝  ██╔══██║██║╚██╗██║
███████║   ██║   ███████╗██║     ██║  ██║██║ ╚████║
╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═══╝
     Stefan’s BASIC 2.0 — GIGA R1 WiFi Edition
```

A friendly fork of Stefan Lenz’s Tiny BASIC interpreter, tuned for the **Arduino GIGA R1 WiFi** with smooth serial terminal UX (e.g., **Tera Term**) and **USB mass-storage** save/load support.  
This handbook serves as both **README** and **full user manual**.  

> License: GPLv3 (same as upstream)

---

## 📑 Table of Contents
- [Overview](#overview)
- [Hardware & Software Prerequisites](#hardware--software-prerequisites)
- [Build & Flash](#build--flash)
- [Terminal Setup](#terminal-setup)
  - [Tera Term (Windows)](#tera-term-setup-windows)
  - [PuTTY / minicom (Linux/macOS)](#putty--minicom-linuxmacos)
- [I/O Channels](#io-channels)
- [Storage & Filesystem](#storage--filesystem)
- [HELP / Keywords](#help--keywords)
- [Command Reference (Grouped)](#command-reference-grouped)
- [Usage Examples](#usage-examples)
- [Prime Finder Example](#prime-finder-example)
- [Troubleshooting](#troubleshooting)
- [Known Limitations](#known-limitations)
- [Credits](#credits)
- [License](#license)

---

## Overview
- ✅ **Arduino GIGA R1 WiFi** support (MBed core)
- ✅ **USB Mass Storage** support (`&16` channel)
- ✅ **Improved Serial UX** for Tera Term / PuTTY / minicom
- ✅ **Full BASIC 2.0 Command Set**
- ⚠️ Still improving ease-of-use with CR/LF handling in Tera Term

---

## Hardware & Software Prerequisites
- Arduino **GIGA R1 WiFi**
- Arduino IDE 2.x
- Arduino Mbed OS GIGA Core
- USB-C cable
- Optional: USB thumb drive (FAT/FAT32)
- Terminal: Tera Term / PuTTY / minicom

---

## Build & Flash
1. Open `Basic2/IoTBasic/IoTBasic.ino` in Arduino IDE  
2. Select **Board:** `Arduino GIGA R1 WiFi`  
3. Select **Port**  
4. Upload the sketch

On boot:
```
Stefan's Basic 2.0  Memory 65535  EEPROM 0
Language set: full
IO: 0 1 16
>
```

---

## Terminal Setup

### Tera Term Setup (Windows)
- Speed: `9600`
- Flow control: none
- Terminal → Receive: `LF`
- Transmit: `CR+LF`
- Auto wrap: ON
- Local echo: OFF
- Terminal size: `80 x 24`

### PuTTY / minicom (Linux/macOS)
- PuTTY: Serial line = COM port, Speed = 9600, Implicit CR in LF enabled
- minicom:  
  ```bash
  minicom -D /dev/ttyACM0 -b 9600
  ```

---

## I/O Channels
- `&0` — Internal buffer
- `&1` — USB Serial
- `&16` — Filesystem (USB drive)
- Pins 86/87/88 — Onboard RGB LED

---

## Storage & Filesystem
- `SAVE`, `LOAD`, `CATALOG`, `DELETE`, `FDISK`
- Errors are safe: interpreter continues

---

## HELP / Keywords
Full keyword set: `PRINT LET INPUT GOTO GOSUB RETURN IF FOR TO STEP NEXT STOP LIST NEW RUN ABS RND SIZE REM NOT AND OR LEN SGN PEEK DIM CLR HIMEM TAB THEN END POKE CONT SQR POW MAP DUMP BREAK SAVE LOAD GET PUT SET CLS LOCATE ELSE PINM DWRITE DREAD AWRITE AREAD DELAY MILLIS AZERO LED PLAY PULSE CATALOG DELETE OPEN CLOSE FDISK USR CALL SIN COS TAN ATAN LOG EXP INT DATA READ RESTORE DEF FN ON MALLOC FIND EVAL ERROR AVAIL STR INSTR VAL NETSTAT SENSOR WIRE SLEEP AFTER EVERY EVENT WHILE WEND REPEAT UNTIL SWITCH CASE SWEND DO DEND FEND ASC CHR RIGHT LEFT MID SPC EDIT HELP << >> BIT`

---

## Command Reference (Grouped)
*(each group explained in full in manual)*

- **Program Control:** PRINT, LET, GOTO, IF, FOR/NEXT…  
- **Math:** ABS, RND, POW, SQR…  
- **Memory & Variables:** DIM, PEEK, POKE, CLR…  
- **Strings:** LEN, STR$, VAL, MID, LEFT, RIGHT…  
- **Structured Flow:** WHILE/WEND, REPEAT/UNTIL, SWITCH/CASE…  
- **Filesystem:** SAVE, LOAD, CATALOG, DELETE…  
- **Arduino I/O:** PINM, DWRITE, DREAD, LED, AREAD…  
- **Timers & Events:** DELAY, MILLIS, EVERY, AFTER…  
- **Networking & Sensors:** NETSTAT, SENSOR, WIRE…  
- **Advanced:** USR, CALL, MALLOC, EVAL…  

---

## Usage Examples

### Blink LED (pin 13)
```basic
10 PINM 13,1
20 DWRITE 13,1
30 DELAY 500
40 DWRITE 13,0
50 DELAY 500
60 GOTO 20
```

### RGB LED cycle (pins 86–88)
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 300
60 NEXT P
70 GOTO 20
```

---

## Prime Finder Example
```basic
10 N=2
20 FOR I=2 TO N/2
30 IF N MOD I=0 THEN GOTO 60
40 NEXT I
50 PRINT N
60 N=N+1
70 GOTO 20
```

---

## Troubleshooting
- **Stair-step banner** → Set Tera Term Receive=LF  
- **SAVE/LOAD fails** → Insert FAT32 USB stick  
- **Backspace wrong** → Set Backspace=DEL (127)

---

## Known Limitations
- Single filesystem at a time  
- Filenames best in 8.3 format  
- Graphics/sensor commands depend on libraries

---

## Credits
- Stefan Lenz (original Tiny BASIC)  
- GIGA fork contributors  

---

## License
GPLv3  
