#ifndef TINYBASIC_HARDWARE_H
#define TINYBASIC_HARDWARE_H
/*
 * Stefan's basic interpreter.  
 *
 * Playing around with frugal programming. See the licence file on 
 * https://github.com/slviajero/tinybasic
 *   (GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007)
 *
 * Author: Stefan Lenz, sl001@serverfabrik.de
 *
 * ----
 * Hardware configuration header
 * Tuned for: Arduino GIGA R1 WiFi + Tera Term (USB CDC Serial)
 * Features:  USB Mass Storage filesystem (SAVE/LOAD) with safe-fail behavior
 * ----
 *
 * SAFE-FAIL FS BEHAVIOR
 * ---------------------
 * We define the following macros so the runtime/filesystem layer can:
 *  - try to mount/format the drive
 *  - if the drive is missing or faulty, KEEP RUNNING and
 *    report readable errors for FILE I/O commands:
 *      "No disk / USB storage not found"
 *      "Disk I/O error"
 *
 *   FILESYSTEM_OPTIONAL   -> FS is desirable but not fatal if absent
 *   FS_REPORT_ERRORS      -> runtime should print a user-facing error
 *   FS_TRY_FORMAT_ON_FAIL -> runtime may try a format after a mount failure
 *
 * Your runtime/file layer should check these defines to choose friendly
 * error paths (they’re harmless if ignored).
 */

/* ===== Optional board preset (kept to not break existing setups) ===== */
#define PREDEFINEDBOARD "boards/dummy.h"

/* If you want to override *everything* manually, undef this. */
#define HARDWAREHEURISTICS

/* ===== Runtime debug ===== */
#define RTDEBUG 0
#define RTDEBUGSTREAM 1

/* ===== Memory size =====
 * 0 = auto. If >65535 then address_t becomes 32-bit. */
#define MEMSIZE 0

/* ===== Tabs, terminal emulation ===== */
#define HASMSTAB        /* tab stops by counting characters */
#define HASVT52         /* VT52 escape support (Tera Term handles VT100/VT52) */
#undef  VT52WIRING

/* ===== Optional: built-in BASIC programs in flash (read-only FS) ===== */
/* #define HASBUILDIN */
#define BUILDINMODULE "buildin/buildin-games.h"

/* Arduino interrupt glue for EVENT */
#define ARDUINOINTERRUPTS

/* Background BREAK handling (leave off unless needed for keyboards) */
/* #define BREAKINBACKGROUND */

/* Micro-profiler */
/* #define FASTTICKERPROFILE */

/* Dummy size for fake EEPROM shims (kept for portability) */
#define EEPROMSIZE 1024

/* ===== PS/2 & ZX81 keyboard defaults (kept for portability) ===== */
#define PS2DATAPIN 3
#define PS2IRQPIN  2

#ifdef ARDUINO_AVR_MEGA2560
  #define ZX81PINS 37,35,33,31,29,27,25,23, 47,45,43,41,39
#else
  #define ZX81PINS 7,8,9,10,11,12,A0,A1, 2,3,4,5,6
#endif

/* Pretzelboard soft-serial defaults (kept for portability) */
#define SOFTSERIALRX 11
#define SOFTSERIALTX 12

/* NRF24 CE/CSN (kept for portability) */
#define RF24CEPIN 8
#define RF24CSNPIN 9

/* I2C pins left as board defaults (Wire picks them) */
#undef SDA_PIN
#undef SCL_PIN

/* BREAK from serial */
#define BREAKCHAR '#'
/* Optional BREAK pin (kept undefined) */
#undef BREAKPIN

/* ===== Serial ports =====
 * On GIGA, use native USB CDC for SERIALPORT; Tera Term 115200 8N1 CR+LF. */
#ifndef ALTSERIAL
  #define SERIALPORT Serial
#else
  #define SERIALPORT ALTSERIAL
#endif

#ifndef PRTSERIAL
  #define PRTSERIAL  Serial1
#endif

/* Soft SPI for SD shields only meaningful on MEGA2560 */
#ifdef ARDUINO_AVR_MEGA2560
  #define SOFTWARE_SPI_FOR_SD
#else
  #undef  SOFTWARE_SPI_FOR_SD
#endif

/* ===== Default I2C device addresses (kept for portability) ===== */
#define EFSEEPROMADDR 0x50
#define RTCI2CADDR    0x68
#define I2CEEPROMADDR 0x50
/* #define ARDUINOI2CEEPROM_BUFFERED */

/* ===== Optional sensor set (kept for portability) ===== */
#ifdef ARDUINOSENSORS
  #undef  ARDUINODHT
  #define DHTTYPE DHT22
  #define DHTPIN  2
  #define ARDUINOSHT
  #define ARDUINOMQ2
  #define MQ2PIN A0
  /* Optionally:
     #define ARDUINOLMS6
     #define ARDUINOAHT
     #define ARDUINOBMP280
     #define ARDUINOBME280
  */
#endif

#if defined(ARDUINOSHT) || defined(ARDUINOLMS6) || defined(ARDUINOAHT) || defined(ARDUINOBMP280) || defined(ARDUINOBME280)
  #define ARDUINOSIMPLEWIRE
#endif

/* ===== Keyboard language (USB/PS2) ===== */
/* #define ARDUINOKBDLANG_US */
#define ARDUINOKBDLANG_GERMAN

/* ===== Core buffers/stacks ===== */
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_LGT8F)
  #define BUFSIZE         80
  #define STACKSIZE       15
  #define GOSUBDEPTH       4
  #define FORDEPTH         4
  #define LINECACHESIZE    4
#else
  #define BUFSIZE        128
  #define STACKSIZE       64
  #define GOSUBDEPTH       8
  #define FORDEPTH         8
  #define LINECACHESIZE   16
#endif

/* ======================================================================
 *                        HARDWARE HEURISTICS
 * ====================================================================== */
#ifdef HARDWAREHEURISTICS

/* ---- Tiny AVR boards ---- */
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO)
  #define ARDUINOEEPROM
  #define ARDUINOPICOSERIAL
  #define ARDUINOPGMEEPROM
  #undef  LINECACHESIZE
  #undef  HASMSTAB
  #define MEMSIZE 512
#endif

#if defined(ARDUINO_AVR_PRO)
  #define ARDUINOEEPROM
  #define ARDUINOPGMEEPROM
  #undef  LINECACHESIZE
  #undef  HASMSTAB
  #undef  HASVT52
  #define MEMSIZE 768
#endif

#if defined(ARDUINO_AVR_DUEMILANOVE)
  #define ARDUINOEEPROM
  #define ARDUINOPICOSERIAL
  #define ARDUINOPGMEEPROM
  #undef  LINECACHESIZE
  #undef  HASMSTAB
  #undef  HASVT52
  #define MEMSIZE 128
#endif

/* LGT8F (UNO-like) */
#if defined(ARDUINO_ARCH_LGT8F)
  #define ARDUINOEEPROM
  #define ARDUINOPICOSERIAL
  #undef  LINECACHESIZE
  #undef  HASMSTAB
  #undef  HASVT52
  #define MEMSIZE 256
#endif

/* All AVR 8-bit typically have EEPROM */
#if defined(ARDUINO_ARCH_AVR)
  #ifndef ARDUINOEEPROM
    #define ARDUINOEEPROM
  #endif
#endif

/* ESPs prefer SPIFFS + EEPROM emu */
#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
  #define ARDUINOEEPROM
  #define ESPSPIFFS
#endif

/* RP2040 boards prefer LittleFS */
#if defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_RP2040)
  #define RP2040LITTLEFS
#endif

/* Renesas and XMC offer EEPROM/emulation */
#if defined(ARDUINO_ARCH_RENESAS) || defined(ARDUINO_ARCH_XMC)
  #define ARDUINOEEPROM
#endif

/* ======================================================================
 *                         GIGA R1 WiFi (THIS BUILD)
 * ====================================================================== */
#if defined(ARDUINO_ARCH_MBED_GIGA) || defined(ARDUINO_GIGA)
/* Use GIGA’s USB Mass Storage as BASIC’s filesystem */
  #define GIGAUSBFS
  #define FILESYSTEMDRIVER
  #define NEEDSUSB

/* SAFE-FAIL flags for a friendly user experience */
  #define FILESYSTEM_OPTIONAL     1   /* not fatal if absent */
  #define FS_REPORT_ERRORS        1   /* print clear errors on failures */
  #define FS_TRY_FORMAT_ON_FAIL   1   /* attempt format after mount error */

/* No true EEPROM on GIGA core; avoid accidental EEPROM paths */
  #undef  ARDUINOEEPROM

/* Roomy buffers for comfort */
  #undef  BUFSIZE
  #undef  STACKSIZE
  #undef  GOSUBDEPTH
  #undef  FORDEPTH
  #undef  LINECACHESIZE
  #define BUFSIZE        256
  #define STACKSIZE       96
  #define GOSUBDEPTH      12
  #define FORDEPTH        12
  #define LINECACHESIZE   32

/* Keep terminal niceties */
  #ifndef HASMSTAB
    #define HASMSTAB
  #endif
  #ifndef HASVT52
    #define HASVT52
  #endif

/* Serial mapping (native USB) */
  #ifndef ALTSERIAL
    #define SERIALPORT Serial
  #endif
  #ifndef PRTSERIAL
    #define PRTSERIAL  Serial1
  #endif

/* Let runtime choose best heap size */
  #undef  MEMSIZE
  #define MEMSIZE 0

/* Background tasks useful with USB (and future net/keyboard) */
  #ifndef BASICBGTASK
    #define BASICBGTASK
  #endif
#endif /* GIGA */

#endif /* HARDWAREHEURISTICS */

/* ======================================================================
 *                   Dependencies & driver selection
 * ====================================================================== */

/* DUE has no tone() */
#ifdef ARDUINO_SAM_DUE
  #define ARDUINOTONEEMULATION
#endif

/* ARDUINODIRECTI2C only valid on AVR with TWDR */
#if !defined(ARDUINO_ARCH_AVR) || !defined(TWDR)
  #undef ARDUINODIRECTI2C
#endif

/* Wire dependencies */
#ifdef ARDUINORTC
  #define HASSIMPLEWIRE
#endif
#if defined(ARDUINOLCDI2C) || defined(ARDUINOSSD1306)
  #define HASSIMPLEWIRE
#endif
#ifdef ARDUINOEFS
  #define HASSIMPLEWIRE
#endif
#ifdef ARDUINOI2CEEPROM
  #define HASSIMPLEWIRE
#endif
#if defined(ARDUINOI2CEEPROM) && defined(ARDUINOI2CEEPROM_BUFFERED)
  #define HASWIRE
#endif
#if defined(ARDUINOWIRE) || defined(ARDUINOWIRESLAVE)
  #define HASWIRE
#endif
#ifdef ARDUINOI2CKBD
  #define HASSIMPLEWIRE
#endif
#ifdef ARDUINOSIMPLEWIRE
  #define HASSIMPLEWIRE
#endif

/* SPI dependencies */
#ifdef ARDUINORF24
  #define ARDUINOSPI
#endif
#if defined(ARDUINOSD) || defined(ESPSPIFFS) || defined(ESP32FAT)
  #define ARDUINOSPI
#endif
#ifdef ARDUINOMQTT
  #define ARDUINOSPI
#endif
#if defined(ARDUINONOKIA51) || defined(ARDUINOILI9488) || defined(TFTESPI)
  #define ARDUINOSPI
#endif
#ifdef ARDUINOSPIRAM
  #define ARDUINOSPI
#endif

/* Background tasks for network/keyboards */
#if defined(ARDUINOMQTT) || defined(ARDUINOETH) || defined(ARDUINOUSBKBD) || defined(ARDUINOZX81KBD) || defined(ARDUINOI2CKBD) || defined(GIGAUSBKBD)
  #ifndef BASICBGTASK
    #define BASICBGTASK
  #endif
#endif

#ifdef ARDUINO_ARCH_ESP8266
  #ifndef BASICBGTASK
    #define BASICBGTASK
  #endif
#endif

#ifdef BREAKINBACKGROUND
  #ifndef BASICBGTASK
    #define BASICBGTASK
  #endif
#endif

/* picoserial only if UCSR0A exists */
#ifdef ARDUINOPICOSERIAL
  #ifndef UCSR0A
    #undef ARDUINOPICOSERIAL
  #endif
#endif

/* Platforms without built-in EEPROM */
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_GIGA)
  #undef ARDUINOEEPROM
#endif

/* Filesystem driver selections */
#ifdef ARDUINOSD
  #define FILESYSTEMDRIVER
#endif
#ifdef ESPSPIFFS
  #define FILESYSTEMDRIVER
#endif
#ifdef ESP32FAT
  #define FILESYSTEMDRIVER
#endif
#ifdef RP2040LITTLEFS
  #define FILESYSTEMDRIVER
#endif
#ifdef STM32SDIO
  #define FILESYSTEMDRIVER
#endif
#ifdef GIGAUSBFS
  #define FILESYSTEMDRIVER
  #define NEEDSUSB
#endif

/* External EEPROM FS overrides others */
#ifdef ARDUINOEFS
  #undef ESPSPIFFS
  #undef ESP32FAT
  #undef RP2040LITTLEFS
  #undef ARDUINOSD
  #undef STM32SDIO
  #undef GIGAUSBFS
  #define FILESYSTEMDRIVER
#endif

/* Built-in read-only FS (if chosen) */
#ifdef HASBUILDIN
  #ifndef FILESYSTEMDRIVER
    #define FILESYSTEMDRIVER
  #endif
  #include BUILDINMODULE
#endif

/* Soft SPI only on MEGA2560 */
#ifndef ARDUINO_AVR_MEGA2560
  #undef SOFTWARE_SPI_FOR_SD
#endif

/* Built-in RTC hints */
#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_RENESAS)
  #define HASBUILTINRTC
#endif

/* RTC availability */
#if defined(ARDUINORTC) || defined(HASBUILTINRTC) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINORTCEMULATION) || defined(ARDUINO_ARCH_MBED_GIGA)
  #define HASCLOCK
#endif

/* Second serial port flag */
#ifdef ARDUINOPRT
  #define HASSERIAL1
#endif

/* RF24 flag */
#ifdef ARDUINORF24
  #define HASRF24
#endif

/* MQTT implies some low-level net */
#ifdef ARDUINOMQTT
  #define HASMQTT
  #ifndef ARDUINOETH
    #define ARDUINOWIFI
  #endif
#endif

/* Camera */
#ifdef ESP32CAMERA
  #define HASCAMERA
  #define ESPSDMMC
#endif

/* PROGMEM handling */
#ifdef ARDUINO_ARCH_MBED
  #define PROGMEM
#endif
#ifdef PROGMEM
  #define ARDUINOPROGMEM
#else
  #undef  ARDUINOPROGMEM
  #define PROGMEM
#endif
#ifdef ARDUINO_ARCH_XMC
  #undef  ARDUINOPROGMEM
  #define PROGMEM
#endif

/* EEPROM as program memory only on AVR/LGT8F */
#if defined(ARDUINOPGMEEPROM) && !(defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_LGT8F))
  #undef ARDUINOPGMEEPROM
#endif

#ifdef ARDUINOPGMEEPROM
  #define USEMEMINTERFACE
  #define EEPROMMEMINTERFACE
#else
  #undef  EEPROMMEMINTERFACE
#endif

#ifdef ARDUINOSPIRAM
  #define USEMEMINTERFACE
  #define SPIRAMINTERFACE
#endif

/* String op scratch buffer for mem interfaces */
#ifdef ARDUINO_AVR_MEGA2560
  #define SPIRAMSBSIZE 512
#else
  #define SPIRAMSBSIZE 128
#endif

/* No command line args on Arduinos */
#undef HASARGS

/* Recursion limit per arch */
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR) || defined(ARDUINO_ARCH_LGT8F) || defined(ARDUINO_AVR_PRO)
  #define FNLIMIT 4
#elif defined(ARDUINO_ARCH_ESP8266)
  #define FNLIMIT 64
#elif defined(ARDUINO_ARCH_ESP32)
  #define FNLIMIT 128
#elif defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_RP2040)
  #define FNLIMIT 128
#elif defined(ARDUINO_ARCH_SAM) && defined(ARDUINO_ARCH_SAMD)
  #define FNLIMIT 64
#elif defined(ARDUINO_ARCH_XMC)
  #define FNLIMIT 64
#elif defined(ARDUINO_ARCH_SMT32)
  #define FNLIMIT 128
#elif defined(ARDUINO_ARCH_RENESAS)
  #define FNLIMIT 32
#else
  #define FNLIMIT 128
#endif

/* ===== Language model heuristic (unchanged, but listed) ===== */
#if defined(ARDUINO_ARCH_AVR)
  #if defined(ARDUINO_AVR_DUEMILANOVE)
    #define BASICMINIMAL
  #endif
  #if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_PRO)
    #define BASICSIMPLE
  #endif
  #if defined(ARDUINO_AVR_LEONARDO)
    #define BASICSMALL
  #endif
  #if defined(ARDUINO_AVR_MEGA2560)
    #define BASICFULL
  #endif
#elif defined(ARDUINO_ARCH_LGT8F)
  #define BASICSIMPLE
#elif defined(ARDUINO_ARCH_MEGAAVR)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_ESP8266)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_ESP32)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_RP2040)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_SAM) && defined(ARDUINO_ARCH_SAMD)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_XMC)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_SMT32)
  #define BASICFULL
#elif defined(ARDUINO_ARCH_RENESAS)
  #define BASICFULL
#else
  #define BASICFULL
#endif

/* ===== Include preset AFTER all defaults so it can override as needed ===== */
#ifdef PREDEFINEDBOARD
  #include PREDEFINEDBOARD
#endif

#endif /* TINYBASIC_HARDWARE_H */