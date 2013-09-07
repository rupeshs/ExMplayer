; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "fileass"
; The file to write
OutFile "fileass.exe"
; The default installation directory
InstallDir $PROGRAMFILES\rphMPFE
!include FileAssociation.nsh
; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page instfiles
;--------------------------------
; The stuff to install
Section "Associate"
!insertmacro APP_ASSOCIATE "mp3"\
                           "rphMPFE.audiofle" \
						   "Audio file"\
						   "D:\rphMPFE(4)\rphMPFE\Setup\AudioFile.ico" \
                           "Open with rphMPFE" \
	                       "$INSTDIR\rphMPFE.exe $\"%1$\"" \
	                       "Enqueue in rphMPFE"\
	                       '"$INSTDIR\rphMPFE.exe" -add-to-playlist "%1"'

;Update shell
!insertmacro  UPDATEFILEASSOC

SectionEnd

; Optional section (can be disabled by the user)
Section "UnAssociate"
 
 !insertmacro APP_UNASSOCIATE "mp3" "rphMPFE.audiofle"
 !insertmacro  UPDATEFILEASSOC
 SectionEnd

;--------------------------------

; Uninstaller
