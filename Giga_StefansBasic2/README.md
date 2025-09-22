# Stefan’s BASIC 2.0 — Arduino **GIGA R1 WiFi** Edition

A friendly fork of Stefan Lenz’s Tiny BASIC interpreter, tuned for the **Arduino GIGA R1 WiFi** with smooth serial terminal UX (e.g., **Tera Term**) and **USB mass-storage** save/load support. You get the classic BASIC feel with modern I/O, timers, filesystem commands, and optional graphics.

> License: GPLv3 (same as upstream)

---

## Contents
- [What’s in this fork?](#whats-in-this-fork)
- [Hardware & software prerequisites](#hardware--software-prerequisites)
- [Build & flash](#build--flash)
- [Tera Term setup (Windows)](#tera-term-setup-windows)
- [PuTTY / minicom settings (alternatives)](#putty--minicom-settings-alternatives)
- [I/O channels in this build](#io-channels-in-this-build)
- [Storage / filesystem](#storage--filesystem)
- [BASIC language — full command set](#basic-language--full-command-set)
- [HELP / Keywords](#help--keywords)
- [Usage examples](#usage-examples)
- [Prime Finder Example](#prime-finder-example)
- [Troubleshooting](#troubleshooting)
- [Known limitations](#known-limitations)
- [Credits](#credits)
- [License](#license)

---

## What’s in this fork?

- ✅ **GIGA R1 WiFi** support (MBed core)
- ✅ **USB Mass Storage** filesystem (`&16`) for `SAVE`, `LOAD`, `CATALOG`, etc.  
  - **Safe-fail**: if no USB drive is present or filesystem is unavailable, commands print a clear error and the interpreter keeps running.
- ✅ Solid default serial UX for **Tera Term** / PuTTY / minicom
- ✅ Full language set enabled (see below)
- ⚠️ Still improving ease-of-use with **Tera Term and other terminals** (banner alignment, CR/LF handling).  

---

## Hardware & software prerequisites

- **Board:** Arduino **GIGA R1 WiFi**
- **IDE:** Arduino IDE 2.x (or CLI)
- **Core:** Arduino Mbed OS GIGA (install via Boards Manager)
- **Cable:** USB-C data cable
- **Optional storage:** USB thumb drive (FAT/FAT32 recommended)
- **Terminal:** Tera Term (Windows) / PuTTY / minicom / screen

---

## Build & flash

1. Open `Basic2/IoTBasic/IoTBasic.ino` in Arduino IDE.
2. **Board:** `Arduino GIGA R1 WiFi`  
   **Port:** your GIGA’s serial port
3. **Upload** the sketch.

On first boot you should see something like:
```
Stefan's Basic 2.0  Memory 65535  EEPROM 0
Language set: full
IO: 0 1 16
>
```

If the banner looks “stair-stepped” or duplicated, see **Tera Term setup** below.

---

## Tera Term setup (Windows)

1) **Open** Tera Term → choose your GIGA **Serial** port.  
2) **Setup → Serial port…**
   - **Speed:** `9600`
   - **Flow control:** `none`

3) **Setup → Terminal…**
   - **New-line → Receive = `LF`**  ✅ *(this fixes the stair-step banner)*
   - **New-line → Transmit = `CR+LF`**
   - **Local echo = `OFF`**
   - **Auto wrap = `ON`**
   - **Terminal size = `80 x 24`** (or 25)
   - **Backspace = `DEL (127)`**
   - Select a **monospace font** (Consolas / Courier New)

4) **Setup → Save setup…** (so the settings persist).

> If your output still looks off: press `Enter` a few times to resync, then verify **Receive = LF** is set.  
> We are still refining this experience for easier setup in Tera Term and similar terminals.

---

## PuTTY / minicom settings (alternatives)

**PuTTY:**
- **Serial line:** your COM port
- **Speed:** `9600`
- **Connection type:** `Serial`
- **Terminal → Local echo:** `Force off`
- **Terminal → Implicit CR in every LF:** **enabled** (equivalent to Receive=LF)
- Save the session.

**minicom (Linux/macOS):**
- `minicom -D /dev/ttyACM0 -b 9600`
- `Ctrl+A` → `Z` → `O` (setup)  
  - Serial device `/dev/ttyACM0` (or similar)  
  - Bps/Par/Bits: `9600 8N1`
  - Turn **Local Echo** off
  - Ensure **Add carriage return** ON if your input needs CR+LF

---

## I/O channels in this build

- `&0` — Internal print buffer (readable as string via `@$`)
- `&1` — USB Serial (your terminal)
- `&16` — Filesystem (USB mass storage)
- `Pins 86,87,88` — Onboard RGB LED (Red, Green, Blue)

---

## Storage / filesystem

On the GIGA R1:
- `&16` is the **USB Mass Storage** device (your USB thumb drive).

Typical workflow:
```basic
10 PRINT "Hello World!!"
SAVE "HELLO"     ' saves to USB drive
NEW
LOAD "HELLO"
RUN
```

If there’s **no USB drive** or it **can’t be mounted**:
- Commands such as `LOAD`, `SAVE`, `CATALOG` **print a clear error** (e.g., `Filesystem not available` or `File not found`) and **continue running**.

Handy DOS-like helpers:
- `CATALOG` – list files
- `DELETE "NAME"` – delete a file
- `FDISK` – format/initialize (where supported)
- `OPEN` / `CLOSE` – low-level file streams when needed

> Tip: Use simple 8.3 file names where possible for maximum compatibility.

---

## BASIC language — full command set

Commands are case-insensitive. Availability of some features depends on the hardware & compile options, but this GIGA build ships the **full** set by default.

(see detailed list above + HELP output)

---

## HELP / Keywords

The `HELP` command in this build prints:

```
Stefan's Basic 2.0  Memory 65535  EEPROM 0
Language set: full
IO: 0 1 16
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

## Usage examples

### 1) Hello + save/load
```basic
10 PRINT "Hello World!!"
SAVE "HELLO"
NEW
LOAD "HELLO"
RUN
```

### 2) Blink the built-in LED (pin 13)
```basic
10 PINM 13,1
20 DWRITE 13,1
30 DELAY 500
40 DWRITE 13,0
50 DELAY 500
60 GOTO 20
```

### 3) Onboard RGB LED cycle (pins 86,87,88)
```basic
10 PRINT "Rotate pins 86,87,88"
20 PINM 86,1: PINM 87,1: PINM 88,1
30 LET T=250
40 DWRITE 86,0: DWRITE 87,0: DWRITE 88,0
50 FOR P=86 TO 88
60 DWRITE 86,0: DWRITE 87,0: DWRITE 88,0
70 DWRITE P,1
80 DELAY T
90 NEXT P
100 GOTO 40
```

---

## Prime Finder Example

An optimized prime number calculator that runs forever and prints only **real primes**:

```basic
10 PRINT "PRIME FINDER - CTRL+C TO STOP"
20 N=2
30 F=0
40 LIMIT=INT(SQR(N))
50 FOR D=2 TO LIMIT
60   R=N
70   WHILE R>=D
80     R=R-D
90   WEND
100  IF R=0 THEN F=1: GOTO 120
110 NEXT D
120 IF F=0 THEN PRINT N
130 N=N+1
140 GOTO 30
```

- Uses trial division up to **√N** for efficiency.  
- Remainder check is done by repeated subtraction (since `MOD` isn’t in BASIC).  
- Runs indefinitely, printing primes only.  

---

## Troubleshooting

**Banner looks staggered / doubled**  
→ In Tera Term: **Setup → Terminal → New-line → Receive = LF**.  
Then press `Enter` a couple times.

**Nothing prints / wrong port**  
→ Check Arduino IDE **Tools → Port**, then reconnect Tera Term to that COM port.

**`SAVE`/`LOAD` fails**  
→ Ensure a USB thumb drive is inserted and mounted. If absent, BASIC will show an error and continue. Try different drive or format FAT/FAT32.

**Weird characters / accents**  
→ Use a **monospace** font and UTF-8 encoding in your terminal. Ensure Local Echo is **OFF**.

**Backspace not working**  
→ In Tera Term: **Backspace = DEL (127)**.

---

## Known limitations

- Only **one** active filesystem at a time (`&16` = USB mass storage for this build).
- Some advanced commands depend on optional libraries or hardware (graphics, camera, sensors).
- Filenames are best kept short (8.3) for broadest compatibility.

---

## Credits

- Original interpreter: **Stefan Lenz** — https://github.com/slviajero/tinybasic  
- This GIGA-focused fork: community tweaks for serial UX and USB storage.  
- Thanks to contributors and testers who validated Tera Term settings and GIGA behavior.

---

## License

GPLv3 — see the upstream repo and included license files.
