# TinyBasic for Arduino GIGA R1 WiFi — GIGA-ready Notes

This document summarizes the adjustments we made to run **Stefan’s TinyBasic** on the **Arduino GIGA R1 WiFi**, with a focus on:
- clean build on the GIGA toolchain (MBed Core),
- friendly serial I/O for Tera Term / common terminals,
- plug‑and‑play **USB Mass Storage** (save/load programs to a USB flash drive),
- keeping upstream sources mostly intact (clearly marked files).

> ✅ You reported that **SAVE** and **LOAD** now work from a USB jump drive and the console is happy in Tera Term.  
> ✅ `runtime.cpp` and the large “main” sketch were left **unmodified** per your request.


## What we changed (and what we didn’t)

### ✅ Adjusted / Added
- **`hardware.h` (GIGA profile)**  
  - Added/confirmed GIGA detection (`ARDUINO_ARCH_MBED_GIGA`) and enabled **GIGAUSBFS** for USB Mass Storage.
  - Ensured serial defaults are Tera‑Term friendly (9600 8N1 by default; can be raised to 115200 in your sketch).
  - Clarified buffer sizes, VT52, and background task flags consistent with GIGA memory/MBed core.

- **`basic.h` (headers clean‑up & prototypes)**  
  - Kept 100% API compatibility with upstream tokens and prototypes.
  - Resolved minor C/C++ linkage pitfalls so that declarations match those in `runtime.h`.  
    (No functional changes to the interpreter logic.)

- **`language.h` (preprocessor guard)**  
  - Fixed a preprocessor mismatch so you don’t get `#endif without #if` on GIGA builds.

- **`IoTBasic.ino` (entrypoint)**  
  - Minimal setup/loop that initializes I/O, prints a banner, attempts `autorun`, then hands control to the interpreter.  
  - Non‑fatal autorun failure (e.g., no program) just drops to prompt.

- **USB Mass Storage SAVE/LOAD behavior**  
  - When a USB drive is attached at boot, TinyBasic exposes it as the primary filesystem.  
  - `SAVE "FILENAME"` and `LOAD "FILENAME"` read/write to the USB stick.
  - **Graceful failure:** If no USB drive is present, commands fail with a readable message (no crash) and the session continues.

### ❌ Unmodified
- **`runtime.cpp`** — left **as-is** (you requested “mark that as unmodified”).  
- **“Main” code** for the sketch — also **unmodified** (per your last instruction).


## Quick Start (GIGA R1 WiFi)

1. **Board & Core**  
   - Board: **Arduino GIGA R1 WiFi**  
   - Core: **Arduino Mbed OS GIGA** (via Boards Manager)

2. **Open the project** in Arduino IDE or CLI.

3. **Serial Terminal**  
   - Use **Tera Term** (or similar).  
   - Default settings: **9600 baud, 8N1, CR+LF transmit**, local echo **off**.  
   - You can change baud if desired in your sketch before `serialbegin()`.

4. **USB Flash Drive (optional but recommended)**  
   - Plug in a FAT‑formatted USB stick **before** powering/resetting the GIGA.  
   - On startup, the USB mass storage is mounted.  
   - If it’s missing or faulty, SAVE/LOAD will print a clear error and the interpreter keeps running.

5. **Try it**  
   ```basic
   10 PRINT "HELLO GIGA"
   20 GOTO 10
   SAVE "HELLO.BAS"
   NEW
   LOAD "HELLO.BAS"
   RUN
   ```


## Tera Term tips
- Enable **“New-Line: CR+LF”** for transmit so Enter behaves nicely.  
- If your output shows only LF line endings, you can toggle CR‑on‑LF printing in your sketch or keep Tera Term’s default rendering.  
- For higher throughput, switch to **115200** and match the monitor settings.


## Files touched in this port

| File             | Status      | Notes |
|------------------|-------------|------|
| `hardware.h`     | **Modified** | GIGA profile, `GIGAUSBFS`, sensible buffers, VT52 and background flags sane for MBed. |
| `basic.h`        | **Modified** | Strict prototype parity; no functional changes. |
| `language.h`     | **Modified** | Fixed preprocessor guard so it compiles on GIGA. |
| `IoTBasic.ino`   | **Added**    | Minimal entrypoint: banner → autorun (non‑fatal) → interpreter loop. |
| `runtime.cpp`    | **Unmodified** | Left as‑is by request. |
| “Main” sketch    | **Unmodified** | Left as‑is by request. |


## SAVE/LOAD — failure messages
If the drive is missing, not mounted, or read‑only, TinyBasic prints a clear message like:
```
[FS] USB not available — SAVE/LOAD disabled (continuing without storage)
```
Execution continues; you can still type, edit, and run programs in RAM.

> If you later plug a USB drive, you’ll need to **reset** the board to mount it (GIGA’s USB host stack is initialized at boot).


## Known limitations & notes
- **Mount at boot**: the GIGA USB host is initialized at startup; hot‑plugging after boot isn’t supported by this sketch.
- **FAT only**: ExFAT/NTFS aren’t supported by the current Arduino USB host libraries.
- **Line editor**: TinyBasic uses a simple console editor; Tera Term works great with it.
- **Memory reporting**: Some free‑RAM heuristics differ across architectures; the interpreter uses conservative defaults on GIGA.


## Building with Arduino CLI (optional)
```bash
arduino-cli core install arduino:mbed_giga
arduino-cli compile --fqbn arduino:mbed_giga:giga IoTBasic
arduino-cli upload  --fqbn arduino:mbed_giga:giga -p <YOUR_PORT> IoTBasic
```


## Troubleshooting

**Q: “SAVE” says the USB is not available.**  
A: Ensure the flash drive is FAT‑formatted and plugged in **before** reset. Try a different stick. Power cycle the board.

**Q: Tera Term shows weird line breaks.**  
A: Set **Transmit** to CR+LF and/or adjust the sketch to send CR after LF on print. Disable local echo.

**Q: Build errors about `#endif without #if` in `language.h`.**  
A: You’re on an old snapshot. Use the fixed `language.h` from this GIGA branch (it contains the balanced `#if/#endif`).


## Credits
- TinyBasic by **Stefan Lenz** — GPLv3.  
- Add‑ons and GIGA/USB tweaks by this port.

---

If you want a GIGA‑specific example set (e.g., filesystem demo, sensor reads, and a splash banner) I can drop them into a `examples/giga/` folder.
