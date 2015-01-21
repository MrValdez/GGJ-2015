.INCLUDE "Hello.inc"

;=== Include Library Routines & Macros ===
.INCLUDE "common/InitSNES.asm"
.INCLUDE "common/LoadGraphics.asm"
.INCLUDE "common/2Input.asm"
.INCLUDE "common/Strings.asm"
.INCLUDE "common/QuickSetup.asm"

;=== Global Variables ===

.ENUM $80
	var1	db
	var2	db
.ENDE

.BANK 0 SLOT 0
.ORG 0
.SECTION "MainCode"

Main:
        InitializeSNES

        stz $2121           ; Edit color 0 - snes' screen color you can write it in binary or hex
        lda #%00011111      ; binary is more visual, but if you wanna be cool, use hex ;)
        sta $2122
        stz $2122           ; second byte has no data, so we write a 0

        lda #$0F            ; = 00001111
        sta $2100           ; Turn on screen, full brightness

forever:
        jmp forever

.ENDS