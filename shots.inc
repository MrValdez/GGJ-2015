; future reference: http://www.cs.umb.edu/~bazz/snes/wladx/loromtohirom/
	
; $4218
.EQU Button_A		$80
.EQU Button_X		$40
.EQU Button_L		$20
.EQU Button_R		$10
; $4219
.EQU Button_B		$80
.EQU Button_Y		$40
.EQU Button_Select	$20
.EQU Button_Start	$10
.EQU Button_Up		$08
.EQU Button_Down	$04
.EQU Button_Left	$02
.EQU Button_Right	$01

; next struct
.DEFINE a1	$0400 + $8
.DEFINE a2	a1 + $200 

UpdateShots:
    RTS
	lda #(256/2 - 16)
    sta a1 + sx          ; Sprite X-Coordinate

    lda #(224/2 - 16)   ; Sprite Y-Coordinate
    sta a1 + sy
	
    lda %#0101 0100
	sta a2

	;set the sprite to the highest priority
    ;lda #%01110000
    lda #$30
    sta a1+spriority
 
	;lda	#($40 + $10)
	;lda	#$c0
	;lda	#($e0 + $12)
	;ldx	#$100
	;lda #$04   ;one frame = 4bytes
	;lda #$c0
	;ldx #($40 + $40 + $40 + $40 + $40)
	ldx #$100
	
	sta	a1+sframe


_BButton:
    lda	Joy1+1
	and	#Button_Y
	beq	_BButtonExit

	ldx	MapY
	dex
	dex
	stx	MapY
	
	;put sprite #0 on screen
	lda #$54
	sta SpriteBuf2 + 100

	;set the sprite to the highest priority
    ;lda #%01110000
    lda #$30
    sta SpriteBuf1+spriority  + 100

_BButtonExit:
	RTS
