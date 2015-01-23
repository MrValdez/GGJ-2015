;initially there are no pictures - this is incremented as pictures are added
.DEFINE NUM_PICTS 0	

; IncludePicture FILE
.MACRO IncludePicture
	.REDEFINE NUM_PICTS NUM_PICTS+1

	.BANK NUM_PICTS SLOT 0
	.ORG 0
	.SECTION "PictureData\@"
	clr_\1:
		.incbin "images\\\1.clr"	
	map_\1:
		.incbin "images\\\1.map"	
	pic_\1:
		.incbin "images\\\1.pic"	
	endpic_\1:
	.ENDS
.ENDM

; IncludePictInfo FILE
.MACRO IncludePictInfo
	.db :clr_\1 + $40			;picture bank number
	.db $03				;picture mode
	.dw clr_\1				;address offset - palette
	.dw map_\1				;address offset - map
	.dw endpic_\1 - pic_\1		;size of pic
	.dw pic_\1				;address offset - pic
.ENDM

.ENUM $00
pics_remaining	db
picture_bank	dw	;high byte not used, but is overwritten
pict_info_ptr	dw
.ENDE


