.INCLUDE "Hello.inc"

;=== Include Library Routines & Macros ===
.INCLUDE "common/InitSNES.asm"
.INCLUDE "common/LoadGraphics.asm"
.INCLUDE "common/2Input.asm"
.INCLUDE "common/Strings.asm"
.INCLUDE "common/Sprites.asm"

.INCLUDE "CharacterData.inc"
.INCLUDE "images.inc"
.INCLUDE "title.inc"
.INCLUDE "stage1.inc"
.INCLUDE "common/QuickSetup.asm"

;=== Global Variables ===

.ENUM $80
	var1	db
	var2	db
.ENDE

;=== Start ===

.ENUM $00
pics_remaining	db
picture_bank	dw	;high byte not used, but is overwritten
pict_info_ptr	dw
.ENDE

.BANK 0 SLOT 0
.ORG 0
.SECTION "MainCode"

Main:
    InitializeSNES
    jsr QuickSetup	; set VRAM, the video mode, background and character pointers, 
                    ; and turn on the screen

    JSR SpriteInit	;setup the sprite buffer
	JSR JoyInit		;setup joypads and enable NMI

;initialize:

    PrintString "\n Hello World!!"
    PrintString "\n\n"

; green background
;    sep #$20
;    lda #%10000000
;    sta $2100
    
;    lda     #%11100000  ; Load the low byte of the green color.
;    sta     $2122
;    lda     #%00000000  ; Load the high byte of the green color.
;    sta     $2122

;   lda     #%00001111  ; End VBlank, setting brightness to 15 (100%).
;   sta     $2100

	JSR SetupVideo	
    
    ;jsr TitleScreen
    jsr Stage1

forever:
    jmp forever    
.ENDS
