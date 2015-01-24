	
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

UpdateShots:
	;See what buttons were pressed
_BButton:
    lda	Joy1+1
	and	#Button_Y
	beq	_BButtonExit

	ldx	MapY
	dex
	dex
	stx	MapY
	
_BButtonExit:
	RTS
