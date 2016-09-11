# 
# 

Name:       camera-settings-plugin

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}

Summary:    Camera settings plugin
Version:    0.0.1
Release:    1
Group:      System/Libraries
License:    LICENSE
URL:        https://github.com/kimmoli/onyx-camera-settings-plugin
Source0:    %{name}-%{version}.tar.bz2
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  mce-headers
BuildRequires:  qt5-qttools-linguist

%description
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%build

%qtc_qmake5 VERSION=%{version}

%qtc_make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}

%qmake_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libcamerasettings-qt5.*
%{_libdir}/qt5/qml/com/kimmoli/camerasettings/
/usr/share/jolla-settings/entries/
/usr/share/jolla-settings/pages/camera-settings/
/usr/share/translations/
