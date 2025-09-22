
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
> Complete Handbook + README

---

## 📑 Table of Contents
- [Introduction](#introduction)
- [Hardware & Software Requirements](#hardware--software-requirements)
- [Build & Flash](#build--flash)
- [Terminal Setup](#terminal-setup)
- [I/O Channels](#io-channels)
- [Filesystem](#filesystem)
- [Command Reference](#command-reference)
- [Example Programs](#example-programs)
- [ASCII Diagrams](#ascii-diagrams)
- [Troubleshooting](#troubleshooting)
- [FAQ](#faq)
- [Glossary](#glossary)
- [History](#history)
- [Credits](#credits)
- [License](#license)
## Command Reference

### PRINT
- **Description:** Displays text or numeric values on the screen.
- **Syntax:** `PRINT expr [, expr ...]`
- **Examples:**
```basic
10 PRINT "Hello World!"
20 PRINT 2+3
30 A=42: PRINT "The answer is";A
```

### SQR
- **Description:** Computes the square root of a number.
- **Syntax:** `SQR(expr)`
- **Examples:**
```basic
10 INPUT "Enter a number";N
20 PRINT "The square root of ";N;" is ";SQR(N)
30 GOTO 10
```

### FOR / NEXT
- **Description:** Creates a counted loop.
- **Syntax:** `FOR var = start TO end [STEP step]` ... `NEXT var`
- **Examples:**
```basic
10 FOR I=1 TO 10
20 PRINT "I=";I
30 NEXT I
40 PRINT "Loop done"
```
```basic
10 FOR J=10 TO 2 STEP -2
20 PRINT J
30 NEXT J
```

## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.## Example Programs
### Prime Finder
```basic
10 N=2
20 FLAG=1
30 FOR D=2 TO N-1
40 IF N%D=0 THEN FLAG=0
50 NEXT D
60 IF FLAG=1 THEN PRINT N;" is prime"
70 N=N+1:GOTO 20
```
### RGB LED Cycle
```basic
10 PINM 86,1:PINM 87,1:PINM 88,1
20 FOR P=86 TO 88
30 DWRITE 86,0:DWRITE 87,0:DWRITE 88,0
40 DWRITE P,1
50 DELAY 500
60 NEXT P
70 GOTO 20
```
## Troubleshooting
- **Staggered banner:** set LF in terminal settings.
- **SAVE/LOAD fails:** insert USB drive, FAT/FAT32 format.
## FAQ
- **Q:** Can I blink multiple LEDs? **A:** Yes, just configure each pin with PINM and use DWRITE.
## Glossary
- **EEPROM:** Electrically Erasable Programmable ROM.
- **Token:** Internal representation of a BASIC keyword.
## History
Derived from Stefan Lenz’s Tiny BASIC. Enhanced for Arduino GIGA R1 WiFi.
## Credits
- Stefan Lenz (original BASIC)
- Arduino Community
- KD5VMF (testing, direction)
- ChatGPT (co-creation)
## License
GPLv3 — see LICENSE file.
