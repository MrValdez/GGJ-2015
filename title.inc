.BANK 0 SLOT 0
.SECTION "title" SEMIFREE

TitleScreen:
    jsr SetupCutscene

    lda 0
    sta cheat1
    sta cheat2
    sta cheat3
    sta cheat4
    sta cheat5
    sta cheat6
    sta cheat7
    sta cheat8
    sta cheat9
    sta cheat10
    sta cheat11

start_show:
	lda.w num_pictures
	sta pics_remaining
	ldx #picture_list
	stx pict_info_ptr

next_picture:
	jsr DisplayPicture	
    
	rep #$20		; A/mem = 16 bits

	;move x to point to the next 'info structure pointer'
	lda pict_info_ptr
	clc
	adc #$000A		
	sta pict_info_ptr

	;clear 'player 1 buttons pressed' status
	stz Joy1Press

	sep #$20		; A/mem = 8 bits

	;wait for button press	
no_button:
	;lda	Joy1Press
	;and	#$F0    ; press any key
	
	jsr cheatcode

    lda currentStage
    cmp 1
    bne juststart
    rts

juststart:	
	
	lda	Joy1+1
	and #$10        ; press start
	beq	no_button
button_pressed:
    lda 1
    sta currentStage
    rts

;	dec pics_remaining
;	bne next_picture
;	bra start_show 



DisplayPicture:
      lda #$8F		;Turn off screen (force blank)
      sta $2100		

	ldx pict_info_ptr
	lda $0000, x	;load data bank
	sta picture_bank

	lda $0001, x	;load video mode
	sta $2105		

	rep #$20		; A/mem = 16 bits

	lda $0002, x	;load picture palette
	tax
	lda picture_bank
	jsr DMAPalette

	ldx pict_info_ptr
	lda $0004, x	;load picture map
	ldx #$0800
	stx $2116
	tax
	ldy #$0800
	lda picture_bank
	jsr LoadVRAM

	ldx pict_info_ptr
	lda $0006, x	;load picture size
	tay

	lda $0008, x	;load picture data
	ldx #$1000
	stx $2116
	tax
	lda picture_bank
	jsr LoadVRAM

	sep #$20		; A/mem = 8 bits

      lda #$0F		;Turn on screen, full brightness
      sta $2100		

	rts

cheatcode:
	;; cheat up
	lda cheat1
	cmp 0
	beq code1

	lda cheat2
	cmp 0
	beq code2

	lda cheat3
	cmp 0
	beq code3

	lda cheat4
	cmp 0
	beq code4

	lda cheat5
	cmp 0
	beq code5

    jsr cheatcode2
    	
code1:
	lda	Joy1+1
	and #$08
	beq code2
	lda 1
	sta cheat1
	rts
	
code2:
	lda	Joy1+1
	and #$08
	beq code3
	lda 1
	sta cheat2
    rts

code3:
	lda	Joy1+1
	and #$04
	beq code4
	lda 1
	sta cheat3
    rts

code4:
	lda	Joy1+1
	and #$04
	beq code5
	lda 1
	sta cheat4
    rts

code5:
	lda	Joy1+1
	and #$02
	beq cheatcode2
	lda 1
	sta cheat6
    rts

cheatcode2:
	lda cheat6
	cmp 0
	beq code6

	lda cheat7
	cmp 0
	beq code7

	lda cheat8
	cmp 0
	beq code8

	lda cheat9
	cmp 0
	beq code9

	lda cheat10
	cmp 0
	beq code10

	lda cheat11
	cmp 0
	beq code11
	rts

code6:
    rts
	lda	Joy1+1
	and #$01
	beq code7
	lda 1
	sta cheat6
    rts

code7:
	lda	Joy1+1
	and #$02
	beq code8
	lda 1
	sta cheat6
    rts

code8:
	lda	Joy1+1
	and #$01
	beq code9
	lda 1
	sta cheat7
    rts

code9:
	lda	Joy1+1
	and #$80
	beq code10
	lda 1
	sta cheat8
    rts
code10:
	lda	Joy1+1
	and #$40
	beq code11
	lda 1
	sta cheat9
    rts
code11:
	lda 1
	sta cheat10

    lda 1
    sta currentStage
    rts
    
;	dec pics_remaining
;	jsr next_picture
;	jsr start_show 
	;; cheat
	rts
.ENDS
    
    IncludePicture title

.BANK 0 SLOT 0
.ORG HEADER_OFF
.SECTION "SlideShowInfo" SEMIFREE

.db "Start of SlideShowInfo:"

num_pictures:
.db NUM_PICTS

picture_list:
	IncludePictInfo title

	
.ENDS
