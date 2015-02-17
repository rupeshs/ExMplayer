%global realname ExMplayer


Name:          exmplayer
Version:       3.8.0
Release:       1%{?dist}
Summary:       MPlayer GUI with thumbnail seeking, 3D Video support,

License:       GPLv2+
URL:           http://%{name}.sourceforge.net/
Group:         Development/Libraries
Source:	       https://launchpad.net/~%{name}-dev/+archive/%{name}/+files/%{name}_%{version}.tar.gz

BuildRequires: 	qt-devel 
BuildRequires:	ffmpeg-devel
BuildRequires:	ffmpeg

Requires:	mplayer	
Requires:	ffmpeg

%description
ExMplayer (Extended MPlayer) is a GUI front-end for MPlayer with flow view 
and tool like media cutter.It can play audio,video,dvd files(.vob),vcd 
iles(.mpg,.dat) etc and supports network streaming.It supports subtitles,
subtitle decoding is done by using ass library.It can play any media formats
without any external codecs.


%prep
%setup -n %{realname}

%build
cd ./src
qmake-qt4
make

%install

install -Dm755 src/%{name} %{buildroot}/usr/bin/%{name}
#
install -dm755 %{buildroot}/usr/share/applications
install -m644 %{name}.desktop %{name}_enqueue.desktop %{buildroot}/usr/share/applications
install -Dm644 debian/%{name}.png %{buildroot}/usr/share/pixmaps/%{name}.png
#
install -dm755 %{buildroot}/etc/%{name}
install -m644 linux_build/{sc_default.xml,fmts} %{buildroot}/etc/%{name}
#
install -dm755 %{buildroot}/usr/share/%{name}
# use native installed ffmpeg 
ln -s /usr/bin/ffmpeg  %{buildroot}/usr/share/%{name}/ffmpeg
# or bundled ffmpeg
#install -m755 linux_build/ffmpeg %{buildroot}/usr/share/%{name}


%files
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/applications/%{name}_enqueue.desktop
%{_datadir}/pixmaps/%{name}.png
%{_datadir}/%{name}/
%{_sysconfdir}/%{name}/fmts
%{_sysconfdir}/%{name}/sc_default.xml

%changelog

* Sat Feb 07 2015 David Vasquez <davidjeremias82 at gmail dot com> - 3.8.0-1
- initial build rpm
