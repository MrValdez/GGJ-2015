.DEFINE MapX		$18
.DEFINE MapY		$1A
.DEFINE CurrentFrame	(SpriteBuf1+sframe)

.DEFINE FrameWait		$1C

.BANK 0 SLOT 0
.SECTION "Stage1" SEMIFREE

Stage1:
	;Load palette to make our pictures look correct
	LoadPalette	BG_Palette

	;Load Tile and Character data to VRAM
	LoadBlockToVRAM	SpriteTiles, $6000, $2000	;16 32x32 tiles * (4bit color = 4 planes) --> 8192 bytes
    
	;Set the priority bit of all the BG2 tiles
	LDA #$80
	STA $2115		;set up the VRAM so we can write just to the high byte
	LDX #$5800
	STX $2116
	LDX #$0400		;32x32 tiles = 1024
	LDA #$20
Next_tile:
	STA $2119
	DEX
	BNE Next_tile
	
	JSR SpriteInit	;setup the sprite buffer
	JSR JoyInit		;setup joypads and enable NMI

	;         ---12345678901234567890123456789012---
	PrintString " 'Look Ma, I can Walk!' \n"
	PrintString "   Tile pics: from Darrok \n"
	PrintString "   Walker pics: from a Demo ROM\n"
	PrintString "     - coded by: Neviksti -  "

	;setup our walking sprite
	;put him in the center of the screen
	lda #($80-16) 		
	sta SpriteBuf1+sx
	lda #(224/2-16)
	sta SpriteBuf1+sy

	;put sprite #0 on screen
	lda #$54
	sta SpriteBuf2

	;set the sprite to the highest priority
	lda #$30			
	sta SpriteBuf1+spriority

	;setup the video modes and such, then turn on the screen
	JSR SetupVideo	

InfiniteLoop:

	WAI

	;See what buttons were pressed
_up:
	lda	Joy1+1
	and	#$08
	beq	_down

	ldx	MapY
	dex
	dex
	stx	MapY

	lda	CurrentFrame
	and	#$F0
	cmp	#$40
	beq	IncrementFrame
	lda	#$40
	sta	CurrentFrame
	bra	_done

_down:
	lda	Joy1+1
	and	#$04
	beq	_left

	ldx	MapY
	inx
	inx
	stx	MapY

	lda	CurrentFrame
	and	#$F0
	cmp	#$C0
	beq	IncrementFrame
	lda	#$C0
	sta	CurrentFrame
	bra	_done

_left:
	lda	Joy1+1
	and	#$02
	beq	_right

	ldx	MapX
	dex
	dex
	stx	MapX

	lda	CurrentFrame
	and	#$F0
	cmp	#$80
	beq	IncrementFrame
	lda	#$80
	sta	CurrentFrame
	bra	_done

_right:
	lda	Joy1+1
	and	#$01
	beq	_standing_still

	ldx	MapX
	inx
	inx
	stx	MapX

	lda	CurrentFrame
	and	#$F0
	cmp	#$00
	beq	IncrementFrame
	lda	#$00
	sta	CurrentFrame
	bra	_done

_standing_still:
	lda	CurrentFrame
	and	#$F0
	sta	CurrentFrame
	bra	_done

IncrementFrame:
	inc	FrameWait
	lda	FrameWait
	cmp	#$06
	bne	_done

	lda	CurrentFrame
	and	#$F0
	sta	FrameWait
	lda	CurrentFrame
	clc
	adc	#$04
	and	#$0C
	adc	FrameWait
	sta	CurrentFrame	

	stz	FrameWait
	bra	_done

_done:

	
	JMP InfiniteLoop	;Do this forever

;==========================================================================================


;============================================================================
; SetupVideo -- Set the video mode for the demo
;----------------------------------------------------------------------------
; In: None
;----------------------------------------------------------------------------
; Out: None
;----------------------------------------------------------------------------
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


.ENDS