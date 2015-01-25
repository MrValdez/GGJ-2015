;------------------------------------------------------------------------
;-  Written by: Neviksti
;-     If you use my code, please share your creations with me
;-     as I am always curious :)
;------------------------------------------------------------------------
      
.BANK 0 SLOT 0
.ORG HEADER_OFF
.SECTION "QuickCodeSection" SEMIFREE

.DEFINE FrameNum $12		

VBlank:
	rep #$30		;A/Mem=16bits, X/Y=16bits
	phb
	pha
	phx
	phy
	phd

	sep #$20		; mem/A = 8 bit, X/Y = 16 bit

	;*********transfer sprite data

	stz $2102		; set OAM address to 0
	stz $2103
	
	LDY #$0400
	STY $4300		; CPU -> PPU, auto increment, write 1 reg, $2104 (OAM data write)
	LDY #$0400
	STY $4302		; source offset
	LDY #$0220
	STY $4305		; number of bytes to transfer
	LDA #$7E
	STA $4304		; bank address = $7E  (work RAM)
	LDA #$01
	STA $420B		;start DMA transfer

	;*********transfer BG2 data
	LDA #$00
	STA $2115		;set up VRAM write to write only the lower byte

	LDX #$5800
	STX $2116		;set VRAM address to BG3 tile map

	LDY #$1800
	STY $4300		; CPU -> PPU, auto increment, write 1 reg, $2118 (Lowbyte of VRAM write)
	LDY #$0000
	STY $4302		; source offset
	LDY #$0400
	STY $4305		; number of bytes to transfer
	LDA #$7F
	STA $4304		; bank address = $7F  (work RAM)
	LDA #$01
	STA $420B		;start DMA transfer

	;update the map co-ordinates
	lda MapX
	sta $210D
	lda MapX+1
	sta $210D

	lda MapY
	sta $210E
	lda MapY+1
	sta $210E

	;update the joypad data
	JSR GetInput

	lda $4210		;clear NMI Flag

	REP #$30		;A/Mem=16bits, X/Y=16bits
	
	inc FrameNum

	PLD 
	PLY 
	PLX 
	PLA 
	PLB 
      RTI

;============================================================================

QuickSetup:
	php

	rep #$10		;A/mem = 8bit, X/Y=16bit
	sep #$20

	;Load palette to make our pictures look correct
	LoadPalette	BG_Palette

	;Load Tile and Character data to VRAM
	LoadBlockToVRAM	BackgroundMap, $0000, $2000	; 64x64 tiles = 4096 words = 8192 bytes
	LoadBlockToVRAM	BackgroundPics, $2000, $6000	; 384 tiles * (8bit color)= 0x6000 bytes
    LoadBlockToVRAM	ASCIITiles, $5000, $0800	;128 tiles * (2bit color = 2 planes) --> 2048 bytes
	;LoadBlockToVRAM	SpriteBullets, $8000, $2000	;16 32x32 tiles * (4bit color = 4 planes) --> 8192 bytes ((16*32*32)/2)
	LoadBlockToVRAM	SpriteTiles, $6000, $2000	;16 32x32 tiles * (4bit color = 4 planes) --> 8192 bytes ((16*32*32)/2)
	;LoadBlockToVRAM	SpriteTiles, $6000, $4000	;32 32x32 tiles * (4bit color = 4 planes) --> 16384 bytes
	
	;Set the priority bit of all the BG2 tiles
	LDA #$80
	STA $2115		;set up the VRAM so we can write just to the high byte
	LDX #$5800
	STX $2116
	LDX #$0400		;32x32 tiles = 1024
	LDA #$20
Next_tile:
	STA	 $2119
	DEX
	BNE Next_tile
	
	PLP
	RTS
    
SetupVideo:    
    php
	rep #$10		;A/mem = 8bit, X/Y=16bit
	sep #$20
      
	lda #$A3		;Sprites 32x32 or 64x64, character data at $6000 (word address)
      sta $2101         

	lda #$04		;Set video mode 4, 8x8 tiles (256 color BG1, 4 color BG2)
      sta $2105         

	lda #$03		;Set BG1's Tile Map VRAM offset to $0000 (word address)
      sta $2107		;   and the Tile Map size to 64 tiles x 64 tiles

	lda #$52		;Set BG1's Character VRAM offset to $2000 (word address)
      sta $210B		;Set BG2's Character VRAM offset to $5000 (word address)

	lda #$58		;Set BG2's Tile Map VRAM offset to $5800 (word address)
      sta $2108		;   and the Tile Map size to 32 tiles x 32 tiles

	lda #$13		;Turn on BG1 and BG2 and Sprites
      sta $212C

      lda #$0F		;Turn on screen, full brightness
      sta $2100		

	lda #$FF		;Scroll BG2 down 1 pixel
	sta $2110
	sta $2110         

	plp
	rts
	
SetupCutscene:    
; Same as above but for Title Screen
; - I couldn't figure the difference between the two. Perhaps memory address used? -MrValdez
	php

	rep #$10		;A/mem = 8bit, X/Y=16bit
	sep #$20
      
	lda #$03		;Set video mode 3, 8x8 tiles (256 color BG1, 16 color BG2)
      sta $2105         

	lda #$08		;Set BG1's Tile Map VRAM offset to $0800 (word address)
      sta $2107		;   and the Tile Map size to 32 tiles x 32 tiles

	lda #$21		;Set BG1's Character VRAM offset to $1000 (word address)
      sta $210B		;Set BG2's Character VRAM offset to $2000 (word address)

	lda #$01		;Turn on BG1
      sta $212C

	lda #$FF		;Scroll BG1 down 1 pixel
	sta $210E
	sta $210E

	plp
	rts
	
.ENDS
