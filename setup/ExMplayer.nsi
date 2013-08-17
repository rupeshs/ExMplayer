;Created by Rupesh.s for ExMplayer
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;6-oct-2010
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;12-march-2011
;9-dec-2012
;10-feb-2013
;v2.0.0
;Output
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Compressor

  SetCompressor /SOLID lzma
  SetCompressorDictSize 32
;setup file
;--------------------------------
OutFile ExMplayer_setup_2.0.0(beta).exe 
;--------------------------------
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Defines & includes
!define PRODUCT_NAME "ExMplayer"
!define PRODUCT_VERSION "1.1.0"
!define PRODUCT_PUBLISHER "Rupesh.S<rupesh.rupeshs@gmail.com>"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_GROUP "ExMplayer"
Var ext
!include MUI2.nsh
!include "TextFunc.nsh"
!include FileAssociation.nsh
!include "LogicLib.nsh"
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Configuration
;General
;Version tab on file properties
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
VIProductVersion "1.1.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "ExMplayer Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments""Media player for windows no codec is required."
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Rupesh.S<rupesh.rupeshs@gmail.com>"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© Rupesh 2010-2013"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "ExMplayer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "2.0.0"

/* Sets default install dir to $PROGRAMFILES\ExMplayer.
  If InstallDirRegKey exists (from a previous installation,
  it will default to that directory instead. */
  InstallDir "$PROGRAMFILES\ExMplayer"
  InstallDirRegKey HKLM "Software\ExMplayer" "Path"
  
  ;Put on a show
  ShowInstDetails show
  ShowUnInstDetails show
  
  ;Vista+ XML manifest, does not affect older OSes
  RequestExecutionLevel admin
  
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Interface Settings
XPStyle on

   !define  MUI_LANGDLL_ALWAYSSHOW

  !define MUI_ABORTWARNING
  !define MUI_COMPONENTSPAGE_SMALLDESC
  !define MUI_LICENSEPAGE_CHECKBOX
  !define MUI_FINISHPAGE_RUN $INSTDIR\ExMplayer.exe
  !define MUI_FINISHPAGE_RUN_NOTCHECKED
  !define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange.bmp"

  # Installer/Uninstaller icons
  !define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
  !define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"

  # Language Selection Dialog Settings
  !define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
  !define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
  !define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"
;--------------------------------
;Pages
;MUI_PAGE_WELCOME should always be first and MUI_PAGE_FINISH should be last

  # Install Pages
  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "c:\Copying.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  # UnInstall Pages
  !insertmacro MUI_UNPAGE_INSTFILES
;--------------------------------
; Languages

  !insertmacro MUI_LANGUAGE "Basque"
  !insertmacro MUI_LANGUAGE "Catalan"
  !insertmacro MUI_LANGUAGE "Czech"
  !insertmacro MUI_LANGUAGE "Danish"
  !insertmacro MUI_LANGUAGE "Dutch"
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "Finnish"
  !insertmacro MUI_LANGUAGE "French"
  !insertmacro MUI_LANGUAGE "German"
  !insertmacro MUI_LANGUAGE "Hebrew"
  !insertmacro MUI_LANGUAGE "Hungarian"
  !insertmacro MUI_LANGUAGE "Italian"
  !insertmacro MUI_LANGUAGE "Norwegian"
  !insertmacro MUI_LANGUAGE "NorwegianNynorsk"
  !insertmacro MUI_LANGUAGE "Polish"
  !insertmacro MUI_LANGUAGE "Portuguese"
  !insertmacro MUI_LANGUAGE "PortugueseBR"
  !insertmacro MUI_LANGUAGE "Russian"
  !insertmacro MUI_LANGUAGE "Slovak"
  !insertmacro MUI_LANGUAGE "Slovenian"
  !insertmacro MUI_LANGUAGE "Spanish"
  !insertmacro MUI_LANGUAGE "SpanishInternational"

;--------------------------------
;Reserve Files

  ;These files should be inserted before other files in the data block
  ;Keep these lines before any File command
  ;Only for solid compression (by default, solid compression is enabled for BZIP2 and LZMA)

  !insertmacro MUI_RESERVEFILE_LANGDLL
  
;--------------------------------

;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Section "Full install"
SectionIn RO
SetOutPath "$INSTDIR"
File "D:\ExMplayer_setup\styles.ass"
File "D:\ExMplayer_setup\VideoFile.ico"
File "D:\ExMplayer_setup\AudioFile.ico"
File "D:\ExMplayer_setup\help.hlpx"
File "D:\ExMplayer_setup\ExMplayer.exe.manifest"
File "D:\ExMplayer_setup\fmtsa.aud"
File "D:\ExMplayer_setup\fmtsv.vid"
File "D:\ExMplayer_setup\ffmpeg.exe"
File "D:\ExMplayer_setup\fmts"
File "D:\ExMplayer_setup\libgcc_s_dw2-1.dll"
File "D:\ExMplayer_setup\mingwm10.dll"
File "D:\ExMplayer_setup\QtCore4.dll"
File "D:\ExMplayer_setup\QtGui4.dll"
File "D:\ExMplayer_setup\QtNetwork4.dll"
File "D:\ExMplayer_setup\QtWebKit4.dll"
File "D:\ExMplayer_setup\QtXml4.dll"
File "D:\ExMplayer_setup\QtXmlPatterns4.dll"
File "D:\ExMplayer_setup\ExMplayer.exe"
File "D:\ExMplayer_setup\sc_default.xml"
File "D:\ExMplayer_setup\TagReader.dll"
SetOutPath "$INSTDIR\imageformats"
File  "D:\ExMplayer_setup\imageformats\qgif4.dll"
File  "D:\ExMplayer_setup\imageformats\qico4.dll"
File  "D:\ExMplayer_setup\imageformats\qjpeg4.dll"
File  "D:\ExMplayer_setup\imageformats\qmng4.dll"
File  "D:\ExMplayer_setup\imageformats\qsvg4.dll"
File  "D:\ExMplayer_setup\imageformats\qtiff4.dll"
SetOutPath "$INSTDIR\mplayer"
File "D:\ExMplayer_setup\mplayer\config"
File "D:\ExMplayer_setup\mplayer\drv43260.dll"
File "D:\ExMplayer_setup\mplayer\dsnative.dll"
File "D:\ExMplayer_setup\mplayer\LICENSE.txt"
File "D:\ExMplayer_setup\mplayer\mplayer.exe"
File "D:\ExMplayer_setup\mplayer\mplayer.html"
File "D:\ExMplayer_setup\mplayer\README.txt"
File "D:\ExMplayer_setup\mplayer\vfw2menc.exe"
SetOutPath "$INSTDIR\mplayer\mplayer"
File "D:\ExMplayer_setup\mplayer\mplayer\codecs.conf"
File "D:\ExMplayer_setup\mplayer\mplayer\config"
File "D:\ExMplayer_setup\mplayer\mplayer\input.conf"
File "D:\ExMplayer_setup\mplayer\mplayer\subfont.ttf"
SetOutPath "$INSTDIR\mplayer\fonts"
File "D:\ExMplayer_setup\mplayer\fonts\fonts.conf"
File "D:\ExMplayer_setup\mplayer\fonts\fonts.dtd"
SetOutPath "$INSTDIR\mplayer\fonts\conf.d"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\20-fix-globaladvance.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\20-unhint-small-vera.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\30-metric-aliases.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\30-urw-aliases.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\40-nonlatin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\45-latin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\49-sansserif.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\50-user.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\51-local.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\60-latin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\65-fonts-persian.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\65-nonlatin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\69-unifont.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\80-delicious.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\90-synthetic.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.d\README"
SetOutPath "$INSTDIR\mplayer\fonts\conf.avail"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-autohint.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-no-sub-pixel.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-sub-pixel-bgr.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-sub-pixel-rgb.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-sub-pixel-vbgr.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-sub-pixel-vrgb.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\10-unhinted.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\20-fix-globaladvance.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\20-unhint-small-vera.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\25-unhint-nonlatin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\30-metric-aliases.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\30-urw-aliases.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\40-nonlatin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\45-latin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\49-sansserif.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\50-user.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\51-local.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\60-latin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\65-fonts-persian.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\65-khmer.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\65-nonlatin.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\69-unifont.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\70-no-bitmaps.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\70-yes-bitmaps.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\80-delicious.conf"
File "D:\ExMplayer_setup\mplayer\fonts\conf.avail\90-synthetic.conf"
SetOutPath "$INSTDIR\mplayer\codecs"
File "D:\ExMplayer_setup\mplayer\codecs\drv43260.dll"
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"
ClearErrors

FileOpen $0 "$INSTDIR\fmtsa.aud"  r
IfErrors done
;///////////////////////////////////
loop:
FileRead $0 $1
${TrimNewLines} $1	$ext
DetailPrint $ext
StrCmp  $1 "eof" done asso
asso:
!insertmacro APP_ASSOCIATE  $ext \
                           "ExMplayer.AudioFile"\
						   "Audio file"\
						   "$INSTDIR\AudioFile.ico" \
                           "Open with ExMplayer" \
	                       "$INSTDIR\ExMplayer.exe $\"%1$\"" \
	                       "Enqueue in ExMplayer"\
	                       '"$INSTDIR\ExMplayer.exe" -add-to-playlist "%1"'

						   
StrCmp  $1 "" done loop
;//////////////////////////////////////////////
FileClose $0

done:
;Update shell
!insertmacro  UPDATEFILEASSOC
ClearErrors

FileOpen $0 "$INSTDIR\fmtsv.vid"  r
IfErrors vdone
;///////////////////////////////////
vloop:
FileRead $0 $1

${TrimNewLines} $1	$ext
DetailPrint $ext
StrCmp  $1 "eof" vdone vasso
vasso:
!insertmacro APP_ASSOCIATE  $ext \
                           "ExMplayer.VideoFile"\
						   "Video file"\
						   "$INSTDIR\VideoFile.ico" \
                           "Open with ExMplayer" \
	                       "$INSTDIR\ExMplayer.exe $\"%1$\"" \
	                       "Enqueue in ExMplayer"\
	                       '"$INSTDIR\ExMplayer.exe" -add-to-playlist "%1"'
StrCmp  $1 "" vdone vloop
;//////////////////////////////////////////////
FileClose $0

vdone:
;Update shell
!insertmacro  UPDATEFILEASSOC
;--------------------------------
; Desktop shortcut

  SetOutPath "$INSTDIR"
  # all = global; current = current user
  SetShellVarContext all
  CreateShortCut "$DESKTOP\ExMplayer.lnk" "$INSTDIR\ExMplayer.exe"

 
  SetOutPath "$INSTDIR"
  # Start menu shortcut creation
  SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}\${PRODUCT_NAME}.lnk" "$INSTDIR\ExMplayer.exe"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}\Uninstall ${PRODUCT_NAME}.lnk" "$INSTDIR\uninstall.exe"

SectionEnd


Section "un.Uninstaller Section"
ClearErrors
FileOpen $0 "$INSTDIR\fmtsa.aud"  r
IfErrors uadone
;///////////////////////////////////
ualoop:
FileRead $0 $1
${TrimNewLines} $1	$ext
DetailPrint $ext
StrCmp  $1 "eof" uadone uaunasso
uaunasso:
!insertmacro APP_UNASSOCIATE $ext "ExMplayer.AudioFile"	
StrCmp $1 "" uadone ualoop
;////////////////////////////////////////////////
FileClose $0
uadone:
;Update shell
!insertmacro  UPDATEFILEASSOC
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ClearErrors
FileOpen $0 "$INSTDIR\fmtsv.vid"  r
IfErrors uvdone
;///////////////////////////////////
uvloop:
FileRead $0 $1
${TrimNewLines} $1	$ext
DetailPrint $ext
StrCmp  $1 "eof" uvdone uvunasso
uvunasso:
!insertmacro APP_UNASSOCIATE $ext "ExMplayer.VideoFile"	
StrCmp  $1 "" uvdone uvloop
;////////////////////////////////////////////////
FileClose $0
uvdone:
;Update shell
!insertmacro  UPDATEFILEASSOC
Delete "$INSTDIR\ExMplayer.ini"
Delete "$INSTDIR\styles.ass"
Delete "$INSTDIR\VideoFile.ico"
Delete "$INSTDIR\AudioFile.ico"
Delete "$INSTDIR\ExMplayer.ini"
Delete "$INSTDIR\help.hlpx"
Delete "$INSTDIR\ExMplayer.exe.manifest" 
Delete "$INSTDIR\fmtsa.aud"
Delete "$INSTDIR\fmtsv.vid"
Delete "$INSTDIR\ffmpeg.exe"
Delete "$INSTDIR\fmts"
Delete "$INSTDIR\libgcc_s_dw2-1.dll"
Delete "$INSTDIR\mingwm10.dll"
Delete "$INSTDIR\QtCore4.dll"
Delete "$INSTDIR\QtGui4.dll"
Delete "$INSTDIR\QtNetwork4.dll"
Delete "$INSTDIR\QtWebKit4.dll"
Delete "$INSTDIR\QtXml4.dll"
Delete "$INSTDIR\QtXmlPatterns4.dll"
Delete "$INSTDIR\ExMplayer.exe"
Delete "$INSTDIR\sc_default.xml"
Delete "$INSTDIR\TagReader.dll"
Delete "$INSTDIR\mplayer\config"
Delete "$INSTDIR\mplayer\drv43260.dll"
Delete "$INSTDIR\mplayer\dsnative.dll"
Delete "$INSTDIR\mplayer\LICENSE.txt"
Delete "$INSTDIR\mplayer\mplayer.exe"
Delete "$INSTDIR\mplayer\mplayer.html"
Delete "$INSTDIR\mplayer\README.txt"
Delete "$INSTDIR\mplayer\vfw2menc.exe"
Delete "$INSTDIR\mplayer\mplayer\codecs.conf"
Delete "$INSTDIR\mplayer\mplayer\config"
Delete "$INSTDIR\mplayer\mplayer\input.conf"
Delete "$INSTDIR\mplayer\mplayer\subfont.ttf"
Delete "$INSTDIR\mplayer\fonts\fonts.conf"
Delete "$INSTDIR\mplayer\fonts\fonts.dtd"
Delete "$INSTDIR\mplayer\fonts\conf.d\20-fix-globaladvance.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\20-unhint-small-vera.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\30-metric-aliases.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\30-urw-aliases.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\40-nonlatin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\45-latin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\49-sansserif.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\50-user.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\51-local.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\60-latin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\65-fonts-persian.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\65-nonlatin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\69-unifont.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\80-delicious.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\90-synthetic.conf"
Delete "$INSTDIR\mplayer\fonts\conf.d\README"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-autohint.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-no-sub-pixel.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-sub-pixel-bgr.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-sub-pixel-rgb.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-sub-pixel-vbgr.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-sub-pixel-vrgb.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\10-unhinted.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\20-fix-globaladvance.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\20-unhint-small-vera.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\25-unhint-nonlatin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\30-metric-aliases.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\30-urw-aliases.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\40-nonlatin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\45-latin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\49-sansserif.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\50-user.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\51-local.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\60-latin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\65-fonts-persian.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\65-khmer.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\65-nonlatin.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\69-unifont.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\70-no-bitmaps.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\70-yes-bitmaps.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\80-delicious.conf"
Delete "$INSTDIR\mplayer\fonts\conf.avail\90-synthetic.conf"
Delete "$INSTDIR\mplayer\codecs\drv43260.dll"
Delete "$INSTDIR\imageformats\qgif4.dll"
Delete "$INSTDIR\imageformats\qico4.dll"
Delete "$INSTDIR\imageformats\qjpeg4.dll"
Delete "$INSTDIR\imageformats\qmng4.dll"
Delete "$INSTDIR\imageformats\qsvg4.dll"
Delete "$INSTDIR\imageformats\qtiff4.dll"

RMDir "$INSTDIR\imageformats"
RMDir "$INSTDIR\mplayer\codecs"
RMDir "$INSTDIR\mplayer\fonts\conf.avail"
RMDir "$INSTDIR\mplayer\fonts\conf.d"
RMDir "$INSTDIR\mplayer\fonts"
RMDir "$INSTDIR\mplayer\mplayer"
RMDir "$INSTDIR\mplayer"

 

Delete "$INSTDIR\uninstall.exe"

 # Delete desktop and start menu shortcuts
  SetShellVarContext all
  Delete "$DESKTOP\ExMplayer.lnk"
  RMDir /r "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}"

SectionEnd


;--------------------------------
;Installer Functions

Function .onInit

System::Call 'kernel32::CreateMutexA(i 0, i 0, t "$(^Name)") i .r1 ?e'
 
 Pop $R0
 StrCmp $R0 0 +3
 MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
 Abort

!insertmacro MUI_LANGDLL_DISPLAY
  
;LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

  ;${MementoSectionRestore}

FunctionEnd

;--------------------------------
;UnInstaller Functions
Function un.onInit
 ;Get the stored language preference
  !insertmacro MUI_UNGETLANGUAGE
  
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
   Abort
FunctionEnd

Function un.onUninstSuccess

  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."

FunctionEnd