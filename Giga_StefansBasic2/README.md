# Stefan’s BASIC 2.0 — Arduino **GIGA R1 WiFi** Edition

A friendly fork of Stefan Lenz’s Tiny BASIC interpreter, tuned for the **Arduino GIGA R1 WiFi** with smooth serial terminal UX (e.g., **Tera Term**) and **USB mass‑storage** save/load support. You get the classic BASIC feel with modern I/O, timers, filesystem commands, and optional graphics.

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
- [Usage examples](#usage-examples)
- [Troubleshooting](#troubleshooting)
- [Known limitations](#known-limitations)
- [Credits](#credits)
- [License](#license)

---

## What’s in this fork?

- ✅ **GIGA R1 WiFi** support (MBed core)
- ✅ **USB Mass Storage** filesystem (`&16`) for `SAVE`, `LOAD`, `CATALOG`, etc.  
  - **Safe‑fail**: if no USB drive is present or filesystem is unavailable, commands print a clear error and the interpreter keeps running.
- ✅ Solid default serial UX for **Tera Term** / PuTTY / minicom
- ✅ Full language set enabled (see below)

---

## Hardware & software prerequisites

- **Board:** Arduino **GIGA R1 WiFi**
- **IDE:** Arduino IDE 2.x (or CLI)
- **Core:** Arduino Mbed OS GIGA (install via Boards Manager)
- **Cable:** USB‑C data cable
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

If the banner looks “stair‑stepped” or duplicated, see **Tera Term setup** below.

---

## Tera Term setup (Windows)

1) **Open** Tera Term → choose your GIGA **Serial** port.  
2) **Setup → Serial port…**
   - **Speed:** `9600`
   - **Flow control:** `none`

3) **Setup → Terminal…**
   - **New‑line → Receive = `LF`**  ✅ *(this fixes the stair‑step banner)*
   - **New‑line → Transmit = `CR+LF`**
   - **Local echo = `OFF`**
   - **Auto wrap = `ON`**
   - **Terminal size = `80 x 24`** (or 25)
   - **Backspace = `DEL (127)`**
   - Select a **monospace font** (Consolas / Courier New)

4) **Setup → Save setup…** (so the settings persist).

> If your output still looks off: press `Enter` a few times to resync, then verify **Receive = LF** is set.

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

Handy DOS‑like helpers:
- `CATALOG` – list files
- `DELETE "NAME"` – delete a file
- `FDISK` – format/initialize (where supported)
- `OPEN` / `CLOSE` – low‑level file streams when needed

> Tip: Use simple 8.3 file names where possible for maximum compatibility.

---

## BASIC language — full command set

Commands are case‑insensitive. Availability of some features depends on the hardware & compile options, but this GIGA build ships the **full** set by default.

### Core
`PRINT`, `LET`, `INPUT`, `GOTO`, `GOSUB`, `RETURN`,  
`IF ... THEN ... [ELSE ...]`,  
`FOR ... TO ... [STEP ...]` / `NEXT`,  
`STOP`, `LIST`, `NEW`, `RUN`, `REM`

### Numeric & utility
`ABS`, `RND`, `SIZE` (free memory), `SGN`, `INT`, `SQR`, `POW`, `MAP`

### Variables, arrays, strings
`DIM`, `CLR`, `HIMEM`, `PEEK`, `POKE`, `TAB`, `LEN`,  
`STR$`, `VAL`, `INSTR`, substring `X$(i TO j)`

### Program/data
`DATA`, `READ`, `RESTORE`,  
`DEF FN ... FEND` (user functions), `FN`, `ON ... GOTO/GOSUB`

### Control flow (structured)
`WHILE ... WEND`, `REPEAT ... UNTIL`,  
`SWITCH ... CASE ... SWEND`,  
`DO ... DEND`, `BREAK`, `CONT`

### Filesystem (DOS‑style)
`CATALOG`, `DELETE`, `OPEN`, `CLOSE`, `FDISK`,  
`SAVE`, `LOAD`, `DUMP` (memory dump)

### Arduino / MCU I/O
`PINM` (pinMode), `DWRITE`, `DREAD`, `AWRITE`, `AREAD`,  
`DELAY`, `MILLIS`, `TONE`, `PULSE`, `AZERO`, `LED`

Example:  
```basic
10 PINM 13,1
20 DWRITE 13,1
30 DELAY 500
40 DWRITE 13,0
50 DELAY 500
60 GOTO 20
```

### Graphics (if a graphics display is present/compiled)
`COLOR`, `PLOT`, `LINE`, `RECT`, `FRECT`, `CIRCLE`, `FCIRCLE`, `LOCATE`, `CLS`

### Timers, events
`AFTER`, `EVERY`, `EVENT` (attach Arduino interrupts where available)

### IoT / Wire / Sensors (compile‑time dependent)
`AVAIL` (bytes available), `ERROR` (I/O error),  
`WIRE`/`F.WIRE` (I²C tools), `SLEEP`, `NETSTAT`, `SENSOR`

### Low‑level / advanced
`USR`, `CALL` (jump into C routines if enabled),  
`MALLOC`, `FIND`, `EVAL`, `CAM` (if camera build)

### Math (floating point where enabled)
`SIN`, `COS`, `TAN`, `ATAN`, `LOG`, `EXP`, `INT`

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

### 2) Blink the built‑in LED (pin 13)
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

### 4) Read an analog pin & print a bar
```basic
10 A = AREAD A0
20 N = A / 32
30 S$ = ""
40 FOR I = 1 TO N : S$ = S$ + "*" : NEXT
50 PRINT "A0=";A; " "; S$
60 DELAY 100
70 GOTO 10
```

### 5) Structured loop + condition
```basic
10 X=0
20 WHILE X<10
30   PRINT "X=";X
40   X=X+1
50 WEND
```

### 6) Timed message (EVERY 1s)
```basic
10 T=0
20 EVERY 1000,100 GOSUB 1000
30 GOTO 30
1000 T=T+1 : PRINT "Tick";T : RETURN
```

### 7) Filesystem listing and delete
```basic
CATALOG
DELETE "OLDPRG"
```

---

## Troubleshooting

**Banner looks staggered / doubled**  
→ In Tera Term: **Setup → Terminal → New‑line → Receive = LF**.  
Then press `Enter` a couple times.

**Nothing prints / wrong port**  
→ Check Arduino IDE **Tools → Port**, then reconnect Tera Term to that COM port.

**`SAVE`/`LOAD` fails**  
→ Ensure a USB thumb drive is inserted and mounted. If absent, BASIC will show an error and continue. Try different drive or format FAT/FAT32.

**Weird characters / accents**  
→ Use a **monospace** font and UTF‑8 encoding in your terminal. Ensure Local Echo is **OFF**.

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
- This GIGA‑focused fork: community tweaks for serial UX and USB storage.  
- Thanks to contributors and testers who validated Tera Term settings and GIGA behavior.

---

## License

GPLv3 — see the upstream repo and included license files.
