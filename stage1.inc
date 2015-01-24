.DEFINE MapX		$18
.DEFINE MapY		$1A
.DEFINE CurrentFrame	(SpriteBuf1+sframe)

.DEFINE FrameWait		$1C

.DEFINE GravityStrength  3
.DEFINE JumpStrength     8
.DEFINE PlayerSpeed      3

.BANK 0 SLOT 0
.SECTION "Stage1" SEMIFREE

.include "shots.inc"

Stage1:	
    ; initialize variables
    lda #0
    sta PlayerPosX
    lda #1
    sta PlayerPosY
    lda #0
    sta JumpPower
    lda #1
    sta PlayerFaceR
	    
	sta $210D

	;put sprite #0 on screen
	lda #$54
	sta SpriteBuf2

	;set the sprite to the highest priority
    ;lda #%01110000
    lda #$30
    sta SpriteBuf1+spriority

	;setup the video modes and such, then turn on the screen
	JSR SetupVideo	

    ; Green Color
    sep #$20
    lda #%10000000
    sta $2100
    
    lda     #%11100000  ; Load the low byte of the green color.
    sta     $2122
    lda     #%00000000  ; Load the high byte of the green color.
    sta     $2122
    
   lda     #%00001111  ; End VBlank, setting brightness to 15 (100%).
   sta     $2100


InfiniteLoop:
	WAI

	jsr MoveCharacter
    jsr ButtonCheck

    jsr UpdateShots
	
	JMP InfiniteLoop	;Do this forever

;====
MoveCharacter:
    ; mirror
    lda PlayerFaceR
    bne notFacingR

    lda #$40
	tsb SpriteBuf1+spriority
	jmp endMirror
notFacingR:
    ; forward facing
    lda #$40
	trb SpriteBuf1+spriority
endMirror:

; Check if we are jumping
	lda JumpPower
	cmp #$00
	beq noJump
	lda PlayerPosY
	cmp #$10
	bcc noJump          ; don't jump if we are near the ceiling
	sbc JumpPower
	sta PlayerPosY
	dec JumpPower
noJump:	

; collision against ceiling
; Gravity

	lda PlayerPosY
	cmp #170        ; Check if we hit floor
	bcs noFall
Fallnow:		

	jsr IncrementFrame
	lda	CurrentFrame
	and	#$F0
	cmp	#$40
	beq	exitFallAnim
	lda	#$40
	sta	CurrentFrame
exitFallAnim:

	lda PlayerPosY
	adc #GravityStrength
	sta PlayerPosY
    
noFall:
	
	lda PlayerPosX
	sta SpriteBuf1+sx
	lda PlayerPosY
	sta SpriteBuf1+sy
    rts
    
;====
ButtonCheck
	;See what buttons were pressed
_AButton:
    lda	Joy1+1
	and	#$80
	beq	_down

	ldx	MapY
	dex
	dex
	stx	MapY
	
	lda #JumpStrength
	sta JumpPower

	lda	CurrentFrame
	and	#$F0
	cmp	#$80
	beq	IncrementFrame
	lda	#$80
	sta	CurrentFrame
	RTS

_down:
	lda	Joy1+1
	and	#$04
	beq	_left

	ldx	MapY
	inx
	inx
	stx	MapY

	RTS

IncrementFrame:
	inc	FrameWait
	lda	FrameWait
	cmp	#$06
	bne _ExitIncrementFrame

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
_ExitIncrementFrame:
	RTS

_left:
	lda	Joy1+1
	and	#$02
	beq	_right

    lda #0
    sta PlayerFaceR

    ; don't go past left
    lda PlayerPosX
    cmp #PlayerSpeed
    beq DontMoveLeft
    bcc DontMoveLeft

    lda PlayerPosX
	sbc #PlayerSpeed
	sta PlayerPosX
DontMoveLeft:

	ldx	MapX
	dex
	dex
	stx	MapX

	lda	CurrentFrame
	and	#$F0
	cmp	#00
	beq	IncrementFrame
	lda	#00
	sta	CurrentFrame
	RTS

_right:
	lda	Joy1+1
	and	#$01
	beq	_standing_still

    lda #1
    sta PlayerFaceR

    lda PlayerPosX
    cmp #(224 - PlayerSpeed)
    beq DontMoveRight
    bcs DontMoveRight

    lda PlayerPosX
	adc #PlayerSpeed
	sta PlayerPosX
DontMoveRight:

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
	RTS

_standing_still:
	lda	CurrentFrame
	and	#$F0
	sta	CurrentFrame
	RTS
    
.ENDS