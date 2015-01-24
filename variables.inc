.ENUM $0000

; 2input.asm
Joy1 		DW		; Current button state of joypad1, bit0=0 if it is a valid joypad
Joy2		DW		;same thing for all pads...

Joy1Press	DW		; Holds joypad1 keys that are pressed and have been pressed since clearing this mem location
Joy2Press	DW		;same thing for all pads...

; stage1.inc
PlayerPosX  DW
PlayerPosY  DW
PlayerFaceR DW
JumpPower   DW

.ENDE

