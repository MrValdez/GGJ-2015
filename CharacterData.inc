.BANK 2 SLOT 0
.ORG 0
.SECTION "CharacterData"

;Map data
BackgroundMap:
	.INCBIN ".\\images\\mymap.map"

;Color data
BG_Palette:
	.INCBIN ".\\images\\mymap.clr"
;	.INCBIN ".\\images\\dwarf.clr"
	.INCBIN ".\\images\\hero.clr"
	.INCBIN ".\\images\\bullets.clr"

	.INCBIN ".\\Images\\ascii.clr"
	;.REPT 128
	;.DW 0
	;.ENDR

SpriteTiles:
;	.INCBIN ".\\images\\dwarf.pic"
	.INCBIN ".\\images\\hero.pic"
	.INCBIN ".\\images\\bullets.pic"

ASCIITiles:
	.INCBIN ".\\images\\ascii.pic"

.ENDS

.BANK 4 SLOT 0
.ORG 0
.SECTION "BG_CharacterData"

;character data
BackgroundPics:
	.INCBIN ".\\images\\mymap.pic"
.ENDS
