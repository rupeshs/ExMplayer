;Written by Rupesh Sreeraman
;--------------------------------
;Include Modern UI
!include "MUI2.nsh"
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply
; prompts the user asking them where to install, and drops a copy of example1.nsi
; there.
 
;--------------------------------
Caption "youtube-dl updater" 
; The name of the installer
Name "youtube-dl"

BrandingText "Updater for youtube-dl" 
; The file to write
OutFile "update-youtube-dl.exe"
 
# Installer icons
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico" 
 ;Languages
!insertmacro MUI_LANGUAGE "English"
; Request application privileges for Windows Vista
RequestExecutionLevel admin ;Require admin rights on NT6+ (When UAC is turned on)
 
;--------------------------------
 
; Pages
Page instfiles
 
;--------------------------------
ShowInstDetails show

LangString PAGE_SUBTITLE ${LANG_ENGLISH} "ExMplayer Video-dl checking for updates..."

  


; The stuff to install
Section "" ;No components page, name is not important
!insertmacro MUI_HEADER_TEXT $(PAGE_TITLE) $(PAGE_SUBTITLE)
DetailPrint "Please wait..."
GetFullPathName /SHORT $0 '$EXEDIR\up.cmd'
  ; Set output path to the installation directory.
 nsExec::ExecToLog $0 
 
SectionEnd ; end the section