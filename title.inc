.BANK 0 SLOT 0
.SECTION "title" SEMIFREE

TitleScreen:
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
	lda	Joy1Press
	and	#$F0
	bne	button_pressed
	lda	Joy1Press+1
	beq	no_button
button_pressed:

	dec pics_remaining
	bne next_picture
	bra start_show 
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
