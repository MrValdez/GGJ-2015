;initially there are no pictures - this is incremented as pictures are added
.DEFINE NUM_PICTS 0	

; IncludePicture FILE
.MACRO IncludePicture
	.REDEFINE NUM_PICTS NUM_PICTS+1

	.BANK NUM_PICTS SLOT 0
	.ORG 0
	.SECTION "PictureData\@"
	clr_\1:
		.incbin "Images\\\1.clr"	
	map_\1:
		.incbin "Images\\\1.map"	
	pic_\1:
		.incbin "Images\\\1.pic"	
	endpic_\1:
	.ENDS
.ENDM


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
