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

A full-featured fork of Stefan Lenz’s Tiny BASIC interpreter, tuned for the **Arduino GIGA R1 WiFi** with serial terminal UX, RGB LED, USB mass‑storage, timers, filesystem commands, and optional graphics.

---

## 📑 Table of Contents
- Overview
- Hardware & Software Prerequisites
- Build & Flash
- Terminal Setup (Tera Term, PuTTY, minicom)
- I/O Channels
- Filesystem & Storage
- Command Reference (Grouped, All Explained)
- Usage Examples (Programs)
- Prime Finder Example
- Troubleshooting
- FAQ
- Known Limitations
- History & Credits
- License

---

# 🔧 Hardware & Software Prerequisites
- Arduino **GIGA R1 WiFi**
- Arduino IDE 2.x (or CLI)
- Arduino Mbed OS GIGA core
- USB‑C data cable
- Optional: USB thumb drive (FAT/FAT32)
- Terminal: Tera Term (Windows) / PuTTY / minicom

---

# 🖥️ Terminal Setup (ASCII Diagram)
```
Tera Term → Setup → Serial port
  Speed = 9600
  Flow control = none

Tera Term → Setup → Terminal
  Receive = LF
  Transmit = CR+LF
  Local echo = OFF
  Auto wrap = ON
  Size = 80x24
  Backspace = DEL(127)
```

---

# 🔌 I/O Channels
- &0 — Internal buffer
- &1 — USB Serial (terminal)
- &16 — Filesystem (USB mass storage)
- Pins 86,87,88 — Onboard RGB LED (R,G,B)

---

# 💾 Filesystem Diagram
```
USB Mass Storage (FAT/FAT32)
 ├── HELLO.BAS   (saved program)
 ├── PRIME.BAS   (prime finder)
 ├── GAME1.BAS   (tic-tac-toe)
 └── DATA.DAT    (user data)
```

Commands: SAVE, LOAD, CATALOG, DELETE, OPEN, CLOSE, FDISK.

---

# 📜 Command Reference (Grouped, All Explained)

## Program Control
PRINT, LET, INPUT, GOTO, GOSUB, RETURN, IF, FOR...NEXT, STOP, LIST, NEW, RUN, REM  
➡ Control flow, branching, loops, comments.  
**Example:**  
```basic
10 FOR I=1 TO 10
20 PRINT I
30 NEXT
```

## Math & Numeric
ABS, RND, SIZE, SGN, INT, SQR, POW, MAP, SIN, COS, TAN, ATAN, LOG, EXP  
➡ Standard math functions and random numbers.  
**Example:**  
```basic
10 X = RND(100)
20 PRINT "Random:";X
```

## Variables & Memory
DIM, CLR, HIMEM, PEEK, POKE, MALLOC, FIND, EVAL  
➡ Array allocation, memory peek/poke, dynamic allocation.  

## Strings & Text
LEN, STR$, VAL, INSTR, ASC, CHR, RIGHT, LEFT, MID, SPC, TAB  
➡ String handling.  
**Example:**  
```basic
10 A$="HELLO"
20 PRINT LEFT(A$,3)
```

## Structured Flow
WHILE/WEND, REPEAT/UNTIL, SWITCH/CASE, DO/DEND, DEF FN/FEND, CONT, BREAK  
➡ Structured programming constructs.

## Data Handling
DATA, READ, RESTORE, GET, PUT, SET  
➡ Store and retrieve inline data.  

## Filesystem
CATALOG, DELETE, OPEN, CLOSE, FDISK, SAVE, LOAD, DUMP  
➡ File storage on USB.

## Arduino / MCU I/O
PINM, DWRITE, DREAD, AWRITE, AREAD, DELAY, MILLIS, AZERO, LED, PLAY, PULSE, TONE  
➡ Pin I/O, timing, analog/digital ops, buzzer control.  
**LED Example (pin 13):**  
```basic
10 PINM 13,1
20 DWRITE 13,1
30 DELAY 500
40 DWRITE 13,0
50 DELAY 500
60 GOTO 20
```

**RGB Example (pins 86,87,88):**  
```basic
10 PRINT "Rotate pins 86,87,88"
20 PINM 86,1:PINM 87,1:PINM 88,1
30 LET T=250
40 FOR P=86 TO 88
50 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
60 DWRITE P,1
70 DELAY T
80 NEXT P
90 GOTO 40
```

## Timers & Events
AFTER, EVERY, EVENT, SLEEP, MILLIS  
➡ Scheduling timed events.  
**Example:**  
```basic
10 EVERY 1000,100 GOSUB 1000
20 GOTO 20
1000 PRINT "Tick!" : RETURN
```

## Networking & Sensors
NETSTAT, SENSOR, WIRE (I2C), AVAIL, ERROR  
➡ Networking, I²C, and hardware sensors.

## Advanced
USR, CALL, CAM, EDIT, HELP, BIT, <<, >>  
➡ System extensions, editing, bit shifts.

---

# 🧮 Usage Examples

## Hello + Save/Load
```basic
10 PRINT "HELLO WORLD!!"
SAVE "HELLO"
NEW
LOAD "HELLO"
RUN
```

## Prime Finder (infinite)
```basic
10 N=2
20 F=0
30 FOR D=2 TO SQR(N)
40 IF N MOD D=0 THEN F=1:EXIT FOR
50 NEXT
60 IF F=0 THEN PRINT N
70 N=N+1:F=0
80 GOTO 30
```

---

# 🛠️ Troubleshooting
- **Staggered banner** → Set Receive=LF in terminal.  
- **SAVE/LOAD fail** → Ensure USB drive is inserted + FAT/FAT32.  
- **Weird chars** → Use monospace font, UTF-8 encoding.  
- **Backspace** → DEL(127).  

---

# ❓ FAQ
- **Q: Can I use long filenames?** → Stick to 8.3 for best compatibility.  
- **Q: Can I save to internal flash?** → No, only USB storage in this build.  
- **Q: What’s EEPROM?** → Reserved, not used in this fork.  

---

# ⚠️ Known Limitations
- One filesystem at a time (`&16` = USB mass storage).  
- Some advanced commands depend on optional hardware.  
- Keep filenames short.  

---

# 📜 History & Credits
- Stefan Lenz — Original Tiny BASIC  
- KD5VMF — Arduino GIGA fork + handbook  
- ChatGPT — Documentation & co-development partner  

---

# 📖 License
GPLv3 — see upstream repo and included LICENSE file.
