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
	.INCBIN ".\\images\\hero2.clr"

	.INCBIN ".\\Images\\ascii.clr"
	;.REPT 128
	;.DW 0
	;.ENDR

SpriteTiles:
;	.INCBIN ".\\images\\dwarf.pic"
	.INCBIN ".\\images\\hero.pic"
	.INCBIN ".\\images\\hero2.pic"

ASCIITiles:
	.INCBIN ".\\images\\ascii.pic"

.ENDS
